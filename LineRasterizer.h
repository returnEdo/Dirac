#pragma once

#include <cmath>
#include <vector>


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





void rasterize(const vector<int>& x0, const vector<int>& x1, vector<vector<int> >& buffer){
	/* Line rasterazation */

	vector<int> temp0 = x0;
	vector<int> temp1 = x1;
	
	double m = (x1[1] - x0[1]) / (x1[0] - x0[0]);
	bool badInput = (x0[0] > x1[0]);
	bool negSlope = (m < .0);
	bool highSlope = (abs(m) > 1);
	
	// Bad input check
	if (badInput){
		
		vector<int> temp = temp0;
		temp0 = temp1;
		temp1 = temp;
	}
	
	// negative slope check
	if (negSlope){
		
		temp0 = {-temp0[0], temp0[1]};
		temp1 = {-temp1[0], temp1[1]};
	}
	
	// fast line check
	if (highSlope){
		
		temp0 = {temp0[1], temp0[0]};
		temp1 = {temp1[1], temp1[0]};
	}
	
	rastStruct rast;
	
	rast.deltax = temp1[0] - temp0[0];
	rast.deltay = temp1[1] - temp0[1];
	
	rast.x1 = temp1[0];
	
	buffer.push_back({temp0[0], temp0[1]});
	
	rast.D = rast.deltax - 2 * rast.deltay;

	computePoints(rast, buffer);
			
	if (highSlope){
		
		for (auto &Vec: buffer){ Vec = {Vec[1], Vec[0]}; }
	}
	
	if (negSlope){
		
		for (auto &Vec: buffer){ Vec = {-Vec[0], Vec[1]}; }
	}
}
			
