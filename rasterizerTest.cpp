#include <iostream>
#include "RasterizeObject.h"
#include <vector>
#include <GL/glut.h>

#ifndef DEFAULT_WIDTH
#define DEFAULT_WIDTH 1200
#endif 

#ifndef DEFAUL_HEIGHT
#define DEFAULT_HEIGHT 800
#endif



using namespace std;


Vector v1 = Vector(-100,- 100, 0);
Vector v2 = Vector(100, -200, 0);
Vector v3 = Vector(30, 100, 0);

vector<double> color = {.0, 1.0, .0};
vector<Vector> Triangle = {v1, v2, v3};


void display(void){
	
	glClear(GL_COLOR_BUFFER_BIT);	
	glBegin(GL_POINTS);

	rasterizeTriangle(Triangle, color);

	glEnd();
	glFlush();
}




int main(int argc, char* argv[]){
	
	
	glutInit(&argc,argv);
	
	glutInitDisplayMode(GLUT_RGB);

	glutInitWindowSize(1200, 800);
	
	glutCreateWindow("");
	
	
	glutDisplayFunc(display);
	gluOrtho2D(-DEFAULT_WIDTH/2, DEFAULT_WIDTH/2, -DEFAULT_HEIGHT/2, DEFAULT_HEIGHT/2);
	glutMainLoop();

	return 0;
 
}
