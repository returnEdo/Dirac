#pragma once

#include <iostream>
#include "LineRasterizer.h"
#include "Vector.h"
#include <GL/glut.h>


void putPixel(int x, int y, const vector<double>& color = {.0, 1.0, .0}){
	
	glColor3d(color[0], color[1], color[2]);
	glVertex2i(x, y);
}
	


void rasterizeFlatBottom(Vector& vtop, Vector& vright, Vector& vleft){
	/* Rasterizer for flat bottom triangles */
	if (vright.x < vleft.x){
		
		Vector temp = vright;
		vright = vleft;
		vleft = temp;
	}
	
	vector<vector<int> > bufferRight;
	vector<vector<int> > bufferLeft;
	
	/* line rasterization algorithm */
	rasterizeLineForTriangles(int(floor(vtop.x)), int(floor(vtop.y)), int(floor(vright.x)), 
							  int(floor(vright.y)), bufferRight);
	
	rasterizeLineForTriangles(int(floor(vtop.x)), int(floor(vtop.y)), int(floor(vleft.x)),
							  int(floor(vleft.y)), bufferLeft);
	
	int len = bufferRight.size();
	
	int xpos = vtop.x;
	for(int i = 0; i < len; i++){
		
		for (int xpos = bufferLeft[i][0]; xpos <= bufferRight[i][0]; xpos++){
			
			putPixel(xpos, vtop.y - i);
		}
	}
}


	
void rasterizeFlatTop(Vector& vbottom, Vector& vright, Vector& vleft){
	/* Rasterizer for flat top triangles */
	if (vright.x < vleft.x){
		
		Vector temp = vright;
		vright = vleft;
		vleft = temp;
	}
	
	vector<vector<int> > bufferRight;
	vector<vector<int> > bufferLeft;
	
	/* line rasterization algorithm */
	rasterizeLineForTriangles(int(floor(vbottom.x)), int(floor(vbottom.y)), int(floor(vright.x)), 
							  int(floor(vright.y)), bufferRight);
	
	rasterizeLineForTriangles(int(floor(vbottom.x)), int(floor(vbottom.y)), int(floor(vleft.x)),
							  int(floor(vleft.y)), bufferLeft);
	
	int len = bufferRight.size();
	
	int xpos = vbottom.x;
	for(int i = 0; i < len; i++){
		
		for (int xpos = bufferLeft[i][0]; xpos <= bufferRight[i][0]; xpos++){
			
			putPixel(xpos, i + vbottom.y);
		}
	}
}
	



void sort(vector<Vector>& Vectors){
	/* Sort in ascending y order */
	
	vector<int> ord = {0, 1, 2};
	
	if (Vectors[ord[0]].y > Vectors[ord[1]].y){
		
		int temp = ord[0];
		ord[0] = ord[1];
		ord[1] = temp;
	}
	
	if (Vectors[ord[1]].y > Vectors[ord[2]].y){
		
		int temp = ord[1];
		ord[1] = ord[2];
		ord[2] = temp;
	}
	
	if (Vectors[ord[0]].y > Vectors[ord[2]].y){
		
		int temp = ord[0];
		ord[0] = ord[2];
		ord[2] = temp;
	}
	
	vector<Vector> cp = {Vectors[ord[0]], Vectors[ord[1]], Vectors[ord[2]]};
	
	Vectors[0] = cp[0];
	Vectors[1] = cp[1];
	Vectors[2] = cp[2];
}




void rasterizeTriangle(vector<Vector>& vecs){
	
	sort(vecs);
	
	
	if (vecs[1].y == vecs[2].y){ 
		
		/* Flat top case */
		
		rasterizeFlatTop(vecs[0], vecs[1], vecs[2]);
	}
	else if (vecs[0].y == vecs[1].y){
		
		/* Flat bottom case */
		rasterizeFlatBottom(vecs[2], vecs[0], vecs[1]);
	}

	else{
		
		Vector vec4 = {vecs[1].y,
					   vecs[0].y + (vecs[2].y - vecs[0].y) * (vecs[1].x - vecs[0].x) / (vecs[2].x - vecs[0].x),
					   vecs[0].z + (vecs[2].z - vecs[0].z) * (vecs[1].x - vecs[0].x) / (vecs[2].x - vecs[0].x)};
		
		rasterizeFlatBottom(vecs[2], vecs[1], vec4);
		rasterizeFlatTop(vecs[0], vecs[1], vec4);
	}
}	


