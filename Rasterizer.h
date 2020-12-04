#include <memory>
#include <assert.h>
#include <iostream>
#include "Object.h"
#include <vector>
#include <array>
#include <cmath>
#include "Vector.h"
#include "Vector2.h"
#include "Matrix2.h"
#include "Light.h"
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

	array<double, 3> getColor(const Vector& vec0, const Vector& vec1,
				  const Vector& vec2, const Vector& coord,
				  const array<double, 3>& color, shared_ptr<Light> light) const ;

	public:

	Rasterizer(void);
	BBoxRasterizer findBoundingBox(const Vector& v1, const Vector& v2, const Vector& v3);
	void rasterizeTriangle(const vector<int>& indexes, shared_ptr<Light> light);
	void paintCanvas(void);
	void rasterizeObject(shared_ptr<Object> ptr, shared_ptr<Light> light);

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


array<double, 3> Rasterizer::getColor(const Vector& vec0, const Vector& vec1,
				      const Vector& vec2, const Vector& coord,
				      const array<double, 3>& color, shared_ptr<Light> light) const{
	/* coord are the baricentric coordinates  */

	array<double, 3> newcolor;
	
	/* TODO: set ambient light in the light class  */
	
	array<double, 3> ambient = {.3, .2, .2};

	Vector Q;
	Vector L;

	Q = (vec1 - vec0) ^ (vec2 - vec0);
	L = (light -> P - vec0);
	
	L.normalize();
	Q.normalize();

	double prod = Q * L;

	if (prod >= 0){
		
		for (int i = 0; i < 3; i++){
			
			newcolor[i] = color[i] * (light -> color)[i] * prod + ambient[i];
		}

		return newcolor; 
	}
	
	return ambient;
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



void Rasterizer::rasterizeTriangle(const vector<int>& indx, shared_ptr<Light> light){

	array<double, 3> color = {.1, 1.0, .1};

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
						frameBuffer[yIndx][xIndx] = getColor(cObj -> x[indx[0]][1],
										    cObj -> x[indx[1]][1],
										    cObj -> x[indx[2]][1],
										    coord,
										    color,
										    light);
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




void Rasterizer::rasterizeObject(shared_ptr<Object> ptr, shared_ptr<Light> light){
	/* Renders all the objects on the render list  */
	
	(this -> cObj) = ptr;

	for (auto &index: cObj -> buffers.indexBuffer){
		
		this -> rasterizeTriangle(index, light);
		
	}
}










