#include <memory>
#include <assert.h>
#include <iostream>
#include "Object.h"
#include <vector>
#include <array>
#include "Vector.h"
#include "Vector2.h"
#include "Matrix2.h"
#include <GL/glut.h>

#ifndef DEFAULT_WIDTH
#define DEFAULT_WIDTH 1920
#endif

#ifndef DEFAULT_HEIGHT
#define DEFAULT_HEIGHT 1080
#endif


#ifndef DEFAULT_COLOR
#define DEFAULT_COLOR {.0, .0, .0}
#endif


struct BBoxRasterizer{

	Vector TR;			// top right
	Vector LL;			// low left
};






class Rasterizer{

	protected:
	
	shared_ptr<Object> cObj;				// ptr to the current obj
	array<array<double, static_cast<int>(DEFAULT_WIDTH)>, static_cast<int>(DEFAULT_HEIGHT)>  depthBuffer;
	array<array<array<double, 3>,  static_cast<int>(DEFAULT_WIDTH)>, static_cast<int>(DEFAULT_HEIGHT)>  frameBuffer;

	public:

	Rasterizer(void);
	BBoxRasterizer findBoundingBox(const Vector& v1, const Vector& v2, const Vector& v3);
	void rasterizeTriangle(const vector<int>& indexes);
	void paintCanvas(void);
	void rasterizeObject(shared_ptr<Object> ptr);

};


Rasterizer::Rasterizer(void){
	/* Initializes the buffers  */

	for (int x = 0; x < DEFAULT_WIDTH; x++){
		for (int y = 0; y < DEFAULT_HEIGHT; y++){

			(this -> frameBuffer)[y][x] = DEFAULT_COLOR;
			(this -> depthBuffer)[y][x] = .0;
		}
	}
}



BBoxRasterizer Rasterizer::findBoundingBox(const Vector& v1, const Vector& v2, const Vector& v3){
	
	BBoxRasterizer bbox;

	bbox.TR = Vector(v1.x, v1.y, .0);
	bbox.LL = Vector(v1.x, v1.y, .0);

	for (auto const& vec: {v2, v3}){

		if (vec.y > bbox.TR.y){	bbox.TR.y = vec.y; }
		if (vec.y < bbox.LL.y){	bbox.LL.y = vec.y; }
		if (vec.x > bbox.TR.x){	bbox.TR.x = vec.x; }
		if (vec.x < bbox.LL.x){	bbox.LL.x = vec.x; }
	}

	return bbox;
}



void Rasterizer::rasterizeTriangle(const vector<int>& indx){
	double roof = static_cast<double>(RAND_MAX);
	array<double, 3> color = {static_cast<double>(rand()) / roof,
		   		  static_cast<double>(rand()) / roof,
				  static_cast<double>(rand()) / roof};

	Vector vec0 = cObj -> x[indx[0]][3];
	Vector vec1 = cObj -> x[indx[1]][3];
	Vector vec2 = cObj -> x[indx[2]][3];

	Vector2 q1 = Vector2(vec1 - vec0);
	Vector2 q2 = Vector2(vec2 - vec0);

	double scl = q1 * q2;
	
	Matrix2 mat = inv(Matrix2(Vector2(q1 * q1, scl), Vector2(scl, q2 * q2)));

	BBoxRasterizer bbox = this -> findBoundingBox(vec0, vec1, vec2);

	int startX = static_cast<int>(bbox.LL.x);
	int endX = static_cast<int>(bbox.TR.x);
	int startY = static_cast<int>(bbox.LL.y);
	int endY = static_cast<int>(bbox.TR.y);

	for (int x = startX; x <= endX; x++){

		for (int y = startY; y <= endY; y++){

			Vector2 q = Vector2(static_cast<double>(x) - vec0.x,
					    static_cast<double>(y) - vec0.y);
						
			Vector2 coord2 = mat * Vector2(q * q1, q * q2);
			Vector coord = Vector(1.0 - coord2.x - coord2.y, coord2.x, coord2.y);

			if (nonNegative(coord)){
				/* for all the points of the triangle  */
				
				double invZ = coord.x * vec0.z + coord.y * vec1.z + coord.z * vec2.z;
				
				int xIndx = static_cast<int>(DEFAULT_WIDTH / 2) - 1 + x;
                                int yIndx = static_cast<int>(DEFAULT_HEIGHT / 2) - 1 - y;
				if (yIndx >= 0 & yIndx <= static_cast<int>(DEFAULT_HEIGHT) -1 and xIndx >= 0 and xIndx <= static_cast<int>(DEFAULT_WIDTH) - 1){
					if (invZ >= (this -> depthBuffer[yIndx][xIndx])){
						/* depth test  */

						depthBuffer[yIndx][xIndx] = invZ;
						frameBuffer[yIndx][xIndx] = color;
					}
				}
			
			}
		}
	}
}



void Rasterizer::paintCanvas(void){
	/* Renders all to screen  */

	for (int x = 0; x < DEFAULT_WIDTH; x++){

		for (int y = 0; y < DEFAULT_HEIGHT; y++){

			if (depthBuffer[y][x] != .0){ 
				
				glColor3d(frameBuffer[y][x][0], frameBuffer[y][x][1], frameBuffer[y][x][2]);
				glVertex2i(x - DEFAULT_WIDTH / 2 + 1, DEFAULT_HEIGHT / 2 - 1 -y);
				
				(this -> frameBuffer[y][x]) = DEFAULT_COLOR;
				(this -> depthBuffer[y][x]) = .0; 
			}

		}
	}
}




void Rasterizer::rasterizeObject(shared_ptr<Object> ptr){
	/* Renders all the objects on the render list  */
	
	(this -> cObj) = ptr;

	for (auto &index: cObj -> indexBuffer){
		
		this -> rasterizeTriangle(index);
		
	}
}










