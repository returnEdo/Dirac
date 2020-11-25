#pragma once

#include "Object.h"
#include <algorithm>
#include <vector>
#include <array>
#include "Vector.h"
#include <stdlib.h>		// random color for the pixel
#include <GL/glut.h>		// to color the pixel




void putPixel(int x, int y, const vector<double>& col){
	/* Puts a pixel in x y  */
	
	/* TODO: add shaders  */
	glColor3d(col[0], col[1], col[2]);
	glVertex2i(x, y);
}



void sort(vector<Vector>& vectors){
	/* Increasing y bubble sort of the vertices */
	bool change = true;
	
	while(change){
		
		change = false;
		
		for (int i = 0; i < vectors.size() - 1; i++){
			
			if (vectors[i].y > vectors[i + 1].y){
				
				Vector temp = vectors[i];
				vectors[i] = vectors[i + 1];
				vectors[i + 1] = temp;
				
				change = true;
			}
		}
	}
}




struct rastStruct{

	int D;
	int x1;

	int deltax;
	int deltay;
};





void computePoints(rastStruct& rast,  vector<vector<int> >& buffer){
	/* line rasterazation algorithm */

	vector<int> BufferBack = buffer.back();
	
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



void computePointsForTriangles(rastStruct& rast, vector<vector<int> >& buffer, int xpos){
	/* line rasterazation algorithm corrected for triangles */

	vector<int> BufferBack = buffer.back();

	if (xpos == rast.x1){ return; }
	
	if (rast.D >= 0){
		/* The line intersects below the middle point --> same pixel y */
		rast.D -= rast.deltay;
		
	}
	else{
		/* The line intersect above the middle point --> change pixel y */
		rast.D = rast.D - rast.deltay + rast.deltax;
		
		buffer.push_back({xpos, BufferBack[1] + 1});
	}
	
	xpos ++;
	computePointsForTriangles(rast, buffer, xpos);
}




void rasterizeLine(const Vector& xx0, const Vector& xx1, vector<vector<int> >& buffer){
	/* Line rasterazation 
	 * Buffer pixel will always start from x0, y0 */
	 
	 int x0 = int(xx0.x);
	 int y0 = int(xx0.y);
	 int x1 = int(xx1.x);
	 int y1 = int(xx1.y);
	
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

	
	rastStruct rast;
	rast.deltax = tempx1 - tempx0;
	rast.deltay = tempy1 - tempy0;

	rast.x1 = tempx1;
	
	buffer.push_back({tempx0, tempy0});

	rast.D = rast.deltax - 2 * (rast.deltay);
	
	if (not highSlope){ computePointsForTriangles(rast, buffer, tempx0); }
	else { computePoints(rast, buffer); }

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





void rasterizeFlatBottom(Vector& vtop, Vector& vright, Vector& vleft, const vector<double>& col){
	/* Rasterizes flat bottom triangles  */
	

	// swapper
	if (vright.x < vleft.x){

		Vector vtemp = vright;	
		vright = vleft;
		vleft = vtemp;	
	}

	vector<vector<int> > bufferRight;	// these two contains pixel coordinates 
	vector<vector<int> > bufferLeft;	

	rasterizeLine(vtop, vright, bufferRight);
	rasterizeLine(vtop, vleft, bufferLeft);

	int n = bufferRight.size();
	int x, y;

	// this is the scanning line algorithm
	for (int i = 0; i < n; i++){
		
		y = bufferRight[i][1];

		for (x = bufferLeft[i][0]; x <= bufferRight[i][0]; x++){

			/* TODO: z depth test  */

			putPixel(x, y, col);
		}
	}
}



void rasterizeFlatTop(Vector& vbottom, Vector& vright, Vector& vleft, const vector<double>& col){
	/* Rasterizes flat top triangles  */
	

	// swapper
	if (vright.x < vleft.x){


		Vector vtemp = vright;	
		vright = vleft;
		vleft = vtemp;	
	}

	vector<vector<int> > bufferRight;	// these two contains pixel coordinates 
	vector<vector<int> > bufferLeft;	

	rasterizeLine(vbottom, vright, bufferRight);
	rasterizeLine(vbottom, vleft, bufferLeft);


	int n = bufferRight.size();
	int x, y;

	// this is the scanning line algorithm
	for (int i = 0; i < n; i++){
		
		y = bufferRight[i][1];

		for (x = bufferLeft[i][0]; x <= bufferRight[i][0]; x++){

			/* TODO: z depth test  */

			putPixel(x, y, col);
		}
	}
}




void rasterizeTriangle(vector<Vector>& vecs, const vector<double>& col){
	/* Draws the triangle on screen  */	

	sort(vecs);			// orders the triangles in incresing y order
	

	if (vecs[0].y == vecs[1].y){
		/* We have a flat bottom triangle   */

		rasterizeFlatBottom(vecs[2], vecs[0], vecs[1], col);
	}
	else if (vecs[1].y == vecs[2].y){
		/* We have a flat top triangle  */

		rasterizeFlatTop(vecs[0], vecs[1], vecs[2], col);
	}
	else{
		/* Comomn triangle  */
	
		Vector v4 = Vector(vecs[0].x + (vecs[1].y - vecs[0].y) * (vecs[2].x - vecs[0].x) / (vecs[2].y - vecs[0].y),
							 vecs[1].y,
							 vecs[0].z + (vecs[1].y - vecs[0].y) * (vecs[1].z - vecs[0].z) / (vecs[2].y - vecs[0].y));
		

		rasterizeFlatBottom(vecs[2], vecs[1], v4, col);			// v2 and v1 are the "highest" vertices
		rasterizeFlatTop(vecs[0], vecs[1], v4, col);				// v0 and v1 are the "lowest" vertices
	}
}



void rasterizeObject(const Object& obj){			// should be friend with the object
	/* Rasterizes the mesh of an object */

	for (auto &index: obj.indexBuffer){

		vector<Vector> temp = { obj.xP[index[0]],
					obj.xP[index[1]],
					obj.xP[index[2]]};
		
		double roof = static_cast<double> (RAND_MAX);
		vector<double> color = {static_cast<double>(rand() / roof),
		       			static_cast<double>(rand() / roof), 
					static_cast<double>(rand() / roof)};

		cout << temp[0] << "\t" << color[0] << endl;	

		rasterizeTriangle(temp, color);
	}
}



