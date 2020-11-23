#pragma once

#include <vector>
#include <algorithm>					// this is needed for the reverse method
#include "Vector.h"
#include <GL/glut.h>
#include <iostream>



namespace Rasterizer{
	
	struct rastStruct;
	void putPixel(int x, int y, const std::vector<double>& color = {.0, 1.0, .0});
	void bubbleSort(std::vector<Vector>& Vectors);
	
	
	/* Line rasterization functions */
	void computePoints(rastStruct& rast, std::vector<std::vector<int> >& buffer);
	void rasterizeLine(const Vector& v0, const Vector& v1, std::vector<std::vector<int> >& buffer);
	void drawLine(const Vector& v0, const Vector& v1, const std::vector<double>& color = {.5, .5, .0});

	/* Triangle rasterization functions */
	void computePointsForTriangles(rastStruct& rast, std::vector<std::vector<int> >& buffer, int xpos);
	void rasterizeLineForTriangles(int x0, int y0, int x1, int y1, std::vector<std::vector<int> >& buffer);
	
	
	/* Higher level routines */
	void rasterizeFlatBottom(Vector& vtop, Vector& vright, Vector& vleft);
	void rasterizeFlatTop(Vector& vbottom, Vector& vright, Vector& vleft);
	void rasterizeTriangle(std::vector<Vector>& vecs);
};

using namespace Rasterizer;



struct Rasterizer::rastStruct{
	
	int x1;
	
	int deltax;
	int deltay;
	
	int D;
};




void Rasterizer::putPixel(int x, int y, const std::vector<double>& color){
	
	glColor3d(color[0], color[1], color[2]);
	glVertex2i(x, y);
}


void Rasterizer::bubbleSort(std::vector<Vector>& Vectors){
	/* Increasing y bubble sort of the vertices */
	bool change = true;
	
	while(change){
		
		change = false;
		
		for (int i = 0; i < Vectors.size() - 1; i++){
			
			if (Vectors[i].y > Vectors[i + 1].y){
				
				Vector temp = Vectors[i];
				Vectors[i] = Vectors[i + 1];
				Vectors[i + 1] = temp;
				
				change = true;
			}
		}
	}
}




void Rasterizer::computePoints(Rasterizer::rastStruct& rast, std::vector<std::vector<int> >& buffer){
	/* line rasterazation algorithm */

	std::vector<int> BufferBack = buffer.back();
	
	if (BufferBack[0] == rast.x1){ return; }
	
	if (rast.D >= 0){
		
		rast.D -= rast.deltay;
		
		buffer.push_back({BufferBack[0] + 1, BufferBack[1]});
		
	}
	else{
		
		rast.D = rast.D - rast.deltay + rast.deltax;
		
		buffer.push_back({BufferBack[0] + 1, BufferBack[1] + 1});
	}
	
	computePoints(rast, buffer);
}



void Rasterizer::rasterizeLine(const Vector& v0, const Vector& v1, std::vector<std::vector<int> >& buffer){
	/* Line rasterazation 
	 * Buffer pixel will always start from x0, y0 */
	 
	 int x0 = int(v0.x);
	 int y0 = int(v0.y);
	 int x1 = int(v1.x);
	 int y1 = int(v1.y);
	
	
	if (x0 == x1){
		/* same x line is treated as a special case */
		
		if (y1 < y0){
			
			int temp = y0; 
			y0 = y1;
			y1 = temp;
		}
		
		for (int i = 0; i <= y1 - y0; i++){	buffer.push_back({x0, y0 + i}); }
		return;
	}
	else if (y0 == y1){
		/* same y line */
		
		if (x1 < x0){
			
			int temp = x0; 
			x0 = x1;
			x1 = temp;
		}
		
		for (int i = 0; i <= x1 - x0; i++){ buffer.push_back({x0 + i, y0}); }
		return;
	}	
	
	int tempx0 = x0;
	int tempy0 = y0;
	int tempx1 = x1;
	int tempy1 = y1;

	double m = double(tempy1 - tempy0) / double(tempx1 - tempx0);
	bool badInput = (x0 > x1);
	bool negSlope = (m < .0);
	bool highSlope = (abs(m) > 1);
	
	// negative slope check
	if (negSlope){

		tempx0 = -tempx0;
		tempx1 = -tempx1;
	}

	// fast line check
	if (highSlope){

		int temp0x = tempx0;
		int temp1x = tempx1;
		
		tempx0 = tempy0;
		tempy0 = temp0x;
		
		tempx1 = tempy1;
		tempy1 = temp1x;
	}
	
	if (tempx0 > tempx1){

		int tempx = tempx0;
		int tempy = tempy0;

		tempx0 = tempx1;
		tempy0 = tempy1;
		tempx1 = tempx;
		tempy1 = tempy;
	}	

	Rasterizer::rastStruct rast;
	
	rast.deltax = tempx1 - tempx0;
	rast.deltay = tempy1 - tempy0;

	rast.x1 = tempx1;
	
	buffer.push_back({tempx0, tempy0});

	rast.D = rast.deltax - 2 * rast.deltay;

	Rasterizer::computePoints(rast, buffer);

	if (highSlope){
		
		for (auto &Vec: buffer){ Vec = {Vec[1], Vec[0]}; }
	}
	
	if (negSlope){
		
		for (auto &Vec: buffer){ Vec = {-Vec[0], Vec[1]}; }
	}
	
	if (x0 != buffer[0][0]){
		
		reverse(buffer.begin(), buffer.end());
	}
}


void Rasterizer::drawLine(const Vector& v0, const Vector& v1, const std::vector<double>& color){
	/* Draws a rasterized line */
	
	std::vector<std::vector<int> > buffer;
	
	Rasterizer::rasterizeLine(v0, v1, buffer);
	
	for (auto const& vec: buffer){
		
		glColor3d(color[0], color[1], color[2]);
		glVertex2i(vec[0], vec[1]);
	}
}



void Rasterizer::computePointsForTriangles(Rasterizer::rastStruct& rast, std::vector<std::vector<int> >& buffer, int xpos){
	/* line rasterazation algorithm */

	std::vector<int> BufferBack = buffer.back();

	if (xpos == rast.x1){ return; }
	
	if (rast.D >= 0){
		/* The line intersects below the middle point --> same pixel y */
		rast.D -= rast.deltay;
		//~ buffer.push_back({xpos, BufferBack[1]});
		
	}
	else{
		/* The line intersect above the middle point --> change pixel y */
		rast.D = rast.D - rast.deltay + rast.deltax;
		
		buffer.push_back({xpos, BufferBack[1] + 1});
	}
	
	xpos ++;
	Rasterizer::computePointsForTriangles(rast, buffer, xpos);
}




void Rasterizer::rasterizeLineForTriangles(int x0, int y0, int x1, int y1, std::vector<std::vector<int> >& buffer){
	/* Line rasterazation 
	 * Buffer pixel will always start from x0, y0 */
	
	
	if (x0 == x1){
		
		if (y1 < y0){
			
			int temp = y0; 
			y0 = y1;
			y1 = temp;
		}
		
		for (int i = 0; i <= y1 - y0; i++){	buffer.push_back({x0, y0 + i}); }
		return;
	}
	else if (y0 == y1){
			
		if (x1 < x0){
			
			int temp = x0; 
			x0 = x1;
			x1 = temp;
		}
		
		for (int i = 0; i <= x1 - x0; i++){ buffer.push_back({x0 + i, y0}); }
		return;
	}	
	
	int tempx0 = x0;
	int tempy0 = y0;
	int tempx1 = x1;
	int tempy1 = y1;

	double m = double(tempy1 - tempy0) / double(tempx1 - tempx0);
	bool badInput = (x0 > x1);
	bool negSlope = (m < .0);
	bool highSlope = (abs(m) > 1);
	
	// negative slope check
	if (negSlope){

		tempx0 = -tempx0;
		tempx1 = -tempx1;
	}

	// fast line check
	if (highSlope){

		int temp0x = tempx0;
		int temp1x = tempx1;
		
		tempx0 = tempy0;
		tempy0 = temp0x;
		
		tempx1 = tempy1;
		tempy1 = temp1x;
	}
	
	if (tempx0 > tempx1){

		int tempx = tempx0;
		int tempy = tempy0;

		tempx0 = tempx1;
		tempy0 = tempy1;
		tempx1 = tempx;
		tempy1 = tempy;
	}	

	Rasterizer::rastStruct rast;
	
	rast.deltax = tempx1 - tempx0;
	rast.deltay = tempy1 - tempy0;

	rast.x1 = tempx1;
	
	buffer.push_back({tempx0, tempy0});

	rast.D = rast.deltax - 2 * rast.deltay;
	
	if (not highSlope){	Rasterizer::computePointsForTriangles(rast, buffer, tempx0); }
	else { Rasterizer::computePoints(rast, buffer); }

	if (highSlope){
		
		for (auto &Vec: buffer){ Vec = {Vec[1], Vec[0]}; }
	}
	
	if (negSlope){
		
		for (auto &Vec: buffer){ Vec = {-Vec[0], Vec[1]}; }
	}
	
	if (x0 != buffer[0][0]){
		
		reverse(buffer.begin(), buffer.end());
	}
}



void Rasterizer::rasterizeFlatBottom(Vector& vtop, Vector& vright, Vector& vleft){
	/* Rasterizer for flat bottom triangles */
	if (vright.x < vleft.x){
		
		Vector temp = vright;
		vright = vleft;
		vleft = temp;
	}
	
	std::vector<std::vector<int> > bufferRight;
	std::vector<std::vector<int> > bufferLeft;
	
	/* line rasterization algorithm */
	Rasterizer::rasterizeLineForTriangles(int(floor(vtop.x)), int(floor(vtop.y)), int(floor(vright.x)), 
							  int(floor(vright.y)), bufferRight);
	
	Rasterizer::rasterizeLineForTriangles(int(floor(vtop.x)), int(floor(vtop.y)), int(floor(vleft.x)),
							  int(floor(vleft.y)), bufferLeft);
	int len = bufferRight.size();
	
	int xpos = vtop.x;
	for(int i = 0; i < len; i++){

		for (int xpos = bufferLeft[i][0]; xpos <= bufferRight[i][0]; xpos++){

			Rasterizer::putPixel(xpos, vtop.y - i);
		}
	}
}


	
void Rasterizer::rasterizeFlatTop(Vector& vbottom, Vector& vright, Vector& vleft){
	/* Rasterizer for flat top triangles */
	if (vright.x < vleft.x){
		
		Vector temp = vright;
		vright = vleft;
		vleft = temp;
	}
	
	std::vector<std::vector<int> > bufferRight;
	std::vector<std::vector<int> > bufferLeft;
	
	/* line rasterization algorithm */
	Rasterizer::rasterizeLineForTriangles(int(floor(vbottom.x)), int(floor(vbottom.y)), int(floor(vright.x)), 
							  int(floor(vright.y)), bufferRight);
	
	Rasterizer::rasterizeLineForTriangles(int(floor(vbottom.x)), int(floor(vbottom.y)), int(floor(vleft.x)),
							  int(floor(vleft.y)), bufferLeft);
	
	int len = bufferRight.size();
	
	int xpos = vbottom.x;
	for(int i = 0; i < len; i++){
		
		for (int xpos = bufferLeft[i][0]; xpos <= bufferRight[i][0]; xpos++){
			
			Rasterizer::putPixel(xpos, i + vbottom.y, {1.0, .0, .0});
		}
	}
}



void Rasterizer::rasterizeTriangle(std::vector<Vector>& vecs){
	
	Rasterizer::bubbleSort(vecs);
	
	
	if (vecs[1].y == vecs[2].y){ 
		/* Flat top case */

		Rasterizer::rasterizeFlatTop(vecs[0], vecs[1], vecs[2]);
	}
	else if (vecs[0].y == vecs[1].y){
		/* Flat bottom case */

		Rasterizer::rasterizeFlatBottom(vecs[2], vecs[0], vecs[1]);
	}

	else{
		Vector vec4 = Vector(vecs[0].x + (vecs[1].y - vecs[0].y) * (vecs[2].x - vecs[0].x) / (vecs[2].y - vecs[0].y),
							 vecs[1].y,
							 vecs[0].z + (vecs[1].y - vecs[0].y) * (vecs[1].z - vecs[0].z) / (vecs[2].y - vecs[0].y));
		
		Rasterizer::rasterizeFlatBottom(vecs[2], vecs[1], vec4);
		Rasterizer::rasterizeFlatTop(vecs[0], vecs[1], vec4);
	}
}	

