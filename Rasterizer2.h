#pragma once

#include "Object2.h"
#include <algorithm>
#include <vector>
#include <array>
#include <iostream>
#include <memory>
#include "Vector.h"
#include <stdlib.h>
#include <GL/glut.h>

#ifndef DEFAULT_WIDTH
#define DEFAULT_WIDTH 1200
#endif

#ifndef DEFAULT_HEIGHT
#define DEFAULT_HEIGHT 800
#endif


#define LENGTH (DEFAULT_HEIGHT * DEFAULT_WIDTH)

using namespace std;




struct rastStruct{

	int D;
	int x1;

	int deltax;
	int deltay;
};




class Rasterizer{

	private:
	
	vector<shared_ptr<Object> > objectPtrs;			// objects to be rendered
	shared_ptr<Object> cObj;				// ptr to the current obj
	array<double, static_cast<int>(LENGTH)> depthBuffer;

	vector<int> sort(const vector<int>& indexes);
	void computePoints(rastStruct& rast,  vector<vector<int> >& buffer);
	void computePointsForTriangles(rastStruct& rast, vector<vector<int> >& buffer, int xpos);

	public:

	Rasterizer(Object& obj)	{ objectPtrs.emplace_back(&obj); }
	Rasterizer(void)	{}


	void putPixel(int x, int y, const vector<double>& col);
	void rasterizeLine(const Vector& xx0, const Vector& xx1, vector<vector<int> >& buffer);

	void flatBottom(Vector vtop, Vector vright, Vector vleft,
		        Vector vtopc, Vector vrightc, Vector vleftc,	const vector<double>& color);
	void flatTop(Vector vbottom, Vector vright, Vector vleft,
		     Vector vbottomc, Vector vrightc, Vector vleftc,	const vector<double>& color);
	void rasterizeTriangle(const vector<int>& indexes, const vector<double>& color);	

	void render(void);
	void addObject(Object& obj);
};



void Rasterizer::addObject(Object& obj){
	/* Simply add an object to the render list  */

	(this -> objectPtrs).emplace_back(&obj);
}



void Rasterizer::putPixel(int x, int y, const vector<double>& col){
	/* Puts a pixel in x y  */
	
	/* TODO: add shaders  */
	glColor3d(col[0], col[1], col[2]);
	glVertex2i(x, y);
}



vector<int> Rasterizer::sort(const vector<int>& indexes){
	/* Increasing y bubble sort of the vertices */
	bool change = true;

	vector<int> sorted = indexes;
	
	while(change){
		
		change = false;
		
		for (int i = 0; i < indexes.size() - 1; i++){
			
			/* x[3] are the pixel coordinates  */	
			if (cObj -> x[sorted[i]][3].y > cObj -> x[sorted[i + 1]][3].y){
				
				int temp = sorted[i];

				sorted[i] = sorted[i + 1];
			       	sorted[i + 1] = temp;

				change = true;
			}
		}
	}

	return sorted;
}



void Rasterizer::computePoints(rastStruct& rast,  vector<vector<int> >& buffer){
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



void Rasterizer::computePointsForTriangles(rastStruct& rast, vector<vector<int> >& buffer, int xpos){
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




void Rasterizer::rasterizeLine(const Vector& xx0, const Vector& xx1, vector<vector<int> >& buffer){
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





void Rasterizer::flatBottom(Vector vtop, Vector vright, Vector vleft,
	       		    Vector vtopc, Vector vrightc, Vector vleftc, const vector<double>& col){
	/* Rasterizes flat bottom triangles  */
	cout << "bottom" << endl;

	// swapper
	if (vright.x < vleft.x){

		Vector vtemp = vright;
		Vector temp = vrightc;

		vright = vleft;
		vrightc = vleftc;

		vleft = vtemp;
		vleft = temp;	
	}

	vector<vector<int> > bufferRight;	// these two contains pixel coordinates 
	vector<vector<int> > bufferLeft;	

	rasterizeLine(vtop, vright, bufferRight);
	cout << vtop << "\t" << vright << endl;
	rasterizeLine(vtop, vleft, bufferLeft);

	int n = bufferRight.size();
	int x, y;
	// this is the scanning line algorithm
	
	if (bufferLeft.size() == n){
		for (int i = 0; i < n; i++){
			
			y = bufferRight[i][1];

			for (x = bufferLeft[i][0]; x <= bufferRight[i][0]; x++){

				/* TODO: z depth test  */

				putPixel(x, y, col);
		
			}
		}
	}
}



void Rasterizer::flatTop(Vector vbottom, Vector vright, Vector vleft,
	       		 Vector vbottomc, Vector vrightc, Vector vleftc, const vector<double>& col){
	/* Rasterizes flat top triangles  */
	cout << "top" << endl;	

	// swapper
	if (vright.x < vleft.x){

		Vector vtemp = vright;	
		Vector temp = vrightc;
		
		vright = vleft;
		vrightc = vleftc;
		
		vleft = vtemp;
		vleftc = temp;
	}

	vector<vector<int> > bufferRight;	// these two contains pixel coordinates 
	vector<vector<int> > bufferLeft;	

	rasterizeLine(vbottom, vright, bufferRight);
	rasterizeLine(vbottom, vleft, bufferLeft);


	int n = bufferRight.size();
	int x, y;
	
	// this is the scanning line algorithm
	if (bufferLeft.size() == n){							// Need to understand why sometimes they have different lenghts
		for (int i = 0; i < n; i++){
			
			y = bufferRight[i][1];

			for (x = bufferLeft[i][0]; x <= bufferRight[i][0]; x++){

				/* TODO: z depth test  */

				putPixel(x, y, col);
			}
		}
	}
}



void Rasterizer::rasterizeTriangle(const vector<int>& indexes, const vector<double>& col){
	/* Draws the triangle on screen  */	

	vector<int> sIndex = this -> sort(indexes);			// orders the triangles in incresing y order
	if (cObj -> x[sIndex[0]][3].y == cObj -> x[sIndex[1]][3].y){		// pixel coordinate

		flatBottom(cObj -> x[sIndex[2]][3],		// pixel coordinates
			   cObj -> x[sIndex[0]][3],
			   cObj -> x[sIndex[1]][3],
			   cObj -> x[sIndex[2]][2],		// cam coordinates
			   cObj -> x[sIndex[0]][2],
			   cObj -> x[sIndex[1]][2],
			   col);
	}
	else if (cObj -> x[sIndex[1]][3].y == cObj -> x[sIndex[2]][3].y){	// pixel coordinate

		flatTop(cObj -> x[sIndex[0]][3],		// pixel coordinates
			cObj -> x[sIndex[1]][3],
			cObj -> x[sIndex[2]][3],
			cObj -> x[sIndex[0]][2],		// cam coordinates
			cObj -> x[sIndex[1]][2],
			cObj -> x[sIndex[2]][2],
			col);
	}
	else{	

		/* Artifial vertex pixel and cam position  */
		Vector pixelv4 = cObj -> findVectorGivenY(cObj -> x[sIndex[0]][3],
							  cObj -> x[sIndex[2]][3],
							  cObj -> x[sIndex[1]][3].y);

		Vector camv4 = cObj -> findVectorGivenX(cObj -> x[sIndex[0]][2],
							cObj -> x[sIndex[2]][2],
							cObj -> x[sIndex[1]][2].x);


		flatBottom(cObj -> x[sIndex[2]][3],		// pixel coordinates
			   cObj -> x[sIndex[1]][3],
			   pixelv4,
			   cObj -> x[sIndex[2]][2],		// cam coordinates
			   cObj -> x[sIndex[1]][2],
			   camv4, col);
	
		flatTop(cObj -> x[sIndex[0]][3],		// pixel coordinates
			cObj -> x[sIndex[1]][3],
			pixelv4,
			cObj -> x[sIndex[0]][2],		// cam coordinates
			cObj -> x[sIndex[1]][2],
			camv4, col);
	}
}



void Rasterizer::render(void){
	/* Renders all the objects on the render list  */
	
	/* TODO: add friend to obj class  */

	for (auto & obj: this -> objectPtrs){

		for (auto &index: obj -> indexBuffer){
			
			cObj = obj;							// pointer to the current obj
			
			double roof = static_cast<double> (RAND_MAX);
			vector<double> color = {static_cast<double>(rand() / roof),
						static_cast<double>(rand() / roof), 
						static_cast<double>(rand() / roof)};

			this -> rasterizeTriangle(index, color);
		}
	}

}


