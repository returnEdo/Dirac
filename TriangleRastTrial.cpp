#include <GL/glut.h>
#include <vector>
#include "LineRasterizer.h"
#include "TriangleRasterizer.h"
#include <iostream>
#include <cmath>


using namespace std;

#define WIDTH 1200
#define HEIGHT 800



	
	

void render(void){

	vector<Vector> Vectors = {Vector(.0, .0, .0),
							  Vector(-300, -51, .0),
							  Vector(50, -50, .0)};
	
	glClear(GL_COLOR_BUFFER_BIT);

	
	glColor3f(1, .0, .0);
	glBegin(GL_POINTS);
	
	rasterizeTriangle(Vectors);

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
