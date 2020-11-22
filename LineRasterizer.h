#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


struct rastStruct{
	
	int x1;
	
	int deltax;
	int deltay;
	
	int D;
};
	
using namespace std;




void computePoints(rastStruct& rast, vector<vector<int> >& buffer){
	/* line rasterazation algorithm */

	vector<int> BufferBack = buffer.back();
	
	//~ cout << BufferBack[0] << endl;
	
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



void rasterize(int x0, int y0, int x1, int y1, vector<vector<int> >& buffer){
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

	rastStruct rast;
	
	rast.deltax = tempx1 - tempx0;
	rast.deltay = tempy1 - tempy0;

	rast.x1 = tempx1;
	
	buffer.push_back({tempx0, tempy0});

	rast.D = rast.deltax - 2 * rast.deltay;

	computePoints(rast, buffer);

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




/*----------------------------------------------------------------------
 * Modified version for triangle rasterization */

void computePointsForTriangles(rastStruct& rast, vector<vector<int> >& buffer, int xpos){
	/* line rasterazation algorithm */

	vector<int> BufferBack = buffer.back();

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
	computePointsForTriangles(rast, buffer, xpos);
}




void rasterizeLineForTriangles(int x0, int y0, int x1, int y1, vector<vector<int> >& buffer){
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

	rastStruct rast;
	
	rast.deltax = tempx1 - tempx0;
	rast.deltay = tempy1 - tempy0;

	rast.x1 = tempx1;
	
	buffer.push_back({tempx0, tempy0});

	rast.D = rast.deltax - 2 * rast.deltay;
	
	if (not highSlope){	computePointsForTriangles(rast, buffer, tempx0); }
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


