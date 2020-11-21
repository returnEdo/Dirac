#include <iostream>
#include <vector>
#include "LineRasterizer.h"

using namespace std;

int main(){
	
	
	for (int i = 0; i < 1000; i++){
		vector<vector<int> > buffer;
		vector<int> x0 = {0, 0};
		vector<int> x1 = {1000, 1000};
		
		rasterize(x0, x1, buffer);
	}
	
	return 0;
}
