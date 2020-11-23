#include <GL/glut.h>
#include <vector>
#include "Rasterizer.h"
#include <iostream>
#include <cmath>
/* This is a simple test function for the rasterizer */

using namespace std;

#define WIDTH 1200
#define HEIGHT 800

Vector t = Vector(200.0, 100.0, .0);

Vector v1 = Vector(.0, 300.0, .0);
Vector v3 = Vector(.0, -300.0, .0);
Vector v2 = Vector(-300.0,.0, .0);
Vector v4 = Vector(300.0, .0, .0);
	
Vector v5 = Vector(-50.0, 50.0, .0);
Vector v6 = Vector(-50.0, -50.0, .0);
Vector v7 = Vector(50.0, -50.0, .0);
Vector v8 = Vector(50.0, 50.0, .0);
	
double c = 1;

void render(void){

	vector<Vector> Vectors1 = {v1*c, v8*c, v4*c};
	vector<Vector> Vectors2 = {v1*c, v2*c, v5*c};
	vector<Vector> Vectors3 = {v2*c, v3*c, v6*c};
	vector<Vector> Vectors4 = {v3*c, v4*c, v7*c};

	
	glClear(GL_COLOR_BUFFER_BIT);

	
	glColor3f(1, .0, .0);
	glBegin(GL_POINTS);
	
	Rasterizer::rasterizeTriangle(Vectors1);
	Rasterizer::rasterizeTriangle(Vectors2);
	Rasterizer::rasterizeTriangle(Vectors3);
	Rasterizer::rasterizeTriangle(Vectors4);
	
	int n = 10;
	for (int i = 0; i < n; i++){
		
		Rasterizer::drawLine(Vector(200 * cos(i * M_PI / n), 200 * sin(i * M_PI / n), .0),
								  Vector(-200 * cos(i * M_PI / n), -200 * sin(i * M_PI / n), .0));
	}

	glEnd();

	glFlush();
}




int main(int argc, char* argv[]){
	
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	
	glutInitWindowPosition(50, 50);
	glutCreateWindow("");
	
	glutDisplayFunc(render);
	gluOrtho2D(-WIDTH / 2, WIDTH / 2, -HEIGHT / 2, HEIGHT / 2);

	glutMainLoop();
}
