#include <memory>
#include <assert.h>
#include <iostream>
#include "Object.h"
#include <vector>
#include <array>
#include "Vector.h"
#include "Vector2.h"
#include "Matrix2.h"

#ifndef DEFAULT_WIDTH
#define DEFAULT_WIDTH 1200
#endif

#ifndef DEFAULT_HEIGHT
#define DEFAULT_HEIGHT 800
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
	
	vector<shared_ptr<Object> > objectPtrs;			// objects to be rendered
	shared_ptr<Object> cObj;				// ptr to the current obj
	array<array<double, static_cast<int>(DEFAULT_WIDTH)>, static_cast<int>(DEFAULT_HEIGHT)>  depthBuffer;
	array<array<array<double, 3>,  static_cast<int>(DEFAULT_WIDTH)>, static_cast<int>(DEFAULT_HEIGHT)>  frameBuffer;

	public:

	Rasterizer(Object& obj);
	void addObject(Object& obj);
	BBoxRasterizer findBoundingBox(const Vector& v1, const Vector& v2, const Vector& v3);
	void renderTriangle(const vector<int>& indexes);
	void paintCanvas(void);
	void render(void);

};


Rasterizer::Rasterizer(Object& obj){
	/* Initializes the buffers  */

	objectPtrs.emplace_back(&obj);

	for (int x = 0; x < DEFAULT_WIDTH; x++){
		for (int y = 0; y < DEFAULT_HEIGHT; y++){

			(this -> frameBuffer)[y][x] = DEFAULT_COLOR;
			(this -> depthBuffer)[y][x] = .0;
		}
	}
}




void Rasterizer::addObject(Object& obj){
	/* Simply add an object to the render list  */

	(this -> objectPtrs).emplace_back(&obj);
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




//
//void Rasterizer::renderTriangle(const vector<int>& indexes){
//	/* Adds the triangle to the buffers */	
//	
//	double roof = static_cast<double> (RAND_MAX);
//	array<double, 3> currentColor = {static_cast<double>(rand() / roof),
//				        	static_cast<double>(rand() / roof), 
//				        	static_cast<double>(rand() / roof)};
//
//
//	// Barycentric rasterizer
//	Vector2 q1 = Vector2(cObj -> x[indexes[1]][3] - cObj -> x[indexes[0]][3]);
//	Vector2 q2 = Vector2(cObj -> x[indexes[2]][3] - cObj -> x[indexes[0]][3]);
//
//	double scl = q1 * q2;
//	Matrix2 mat1 =  Matrix2(Vector2(norm2(q1), scl), Vector2(scl, norm2(q2)));
//
//	Matrix2 mat = inv(Matrix2(Vector2(norm2(q1), scl),
//				  Vector2(scl, norm2(q2))));
//
//	BBoxRasterizer bbox = this -> findBoundingBox(cObj -> x[indexes[0]][3],
//						      cObj -> x[indexes[1]][3],
//						      cObj -> x[indexes[2]][3]);
//
//	for (int x = static_cast<int>(bbox.LL.x); x < static_cast<int>(bbox.TR.x); x++){
//
//		for (int y = static_cast<int>(bbox.LL.y); x < static_cast<int>(bbox.TR.y); y++){
//
//			Vector2 currentPosition = Vector2(static_cast<double>(x) - cObj -> x[indexes[0]][3].x, static_cast<double>(y) - cObj -> x[indexes[0]][3].y);
//			cout << currentPosition << endl;	
//			/* Barycentric coordinates calculation  */
//			Vector2 coord2 = mat * Vector2(currentPosition * q1, currentPosition * q2);
//			Vector coord = Vector(1 - coord.x - coord.y, coord.x, coord.y);
//			cout << coord << endl;
//			if (coord.x >= 0 and coord.y >= 0 and coord.z >= 0){
//
//				/* Indexes of the buffers  */
//				int xIndx = static_cast<double>(DEFAULT_WIDTH / 2) - 1 + x;
//				int yIndx = static_cast<double>(DEFAULT_HEIGHT / 2) - 1 - y;
//				
//				double currentInvZ = coord.x * cObj -> x[indexes[0]][3].z + 
//						     coord.y * cObj -> x[indexes[1]][3].z + 
//						     coord.z * cObj -> x[indexes[2]][3].z;
//
//							
//				/* depth test  */
//				if (currentInvZ > (this -> depthBuffer[yIndx][xIndx])){
//
//					this -> depthBuffer[yIndx][xIndx] = currentInvZ;
//					this -> frameBuffer[yIndx][xIndx] = currentColor;
//				}
//			}
//		}
//	}
//}
//

void Rasterizer::renderTriangle(const vector<int>& indx){

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

				if (invZ >= (this -> depthBuffer[yIndx][xIndx])){
					/* depth test  */

					depthBuffer[yIndx][xIndx] = invZ;
					frameBuffer[yIndx][xIndx] = color;
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




void Rasterizer::render(void){
	/* Renders all the objects on the render list  */
	
	for (auto & obj: this -> objectPtrs){

		for (auto &index: obj -> indexBuffer){
			
			cObj = obj;							// pointer to the current obj
			
			this -> renderTriangle(index);
			
	
		}
	}
	this -> paintCanvas();
}










