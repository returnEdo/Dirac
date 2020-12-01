#include <iostream>
#include <GL/glut.h>
#include "Triangle.h"
#include "Camera.h"
#include <vector>
#include "Vector.h"
#include "Rasterizer2.h"

using namespace std;
	
Vector theta0 = Vector();
Vector x0 = Vector(.0, .0, -4.0);
Vector xg0 = Vector(.0, .0, 0.0);


Camera cam = Camera(x0, theta0);
Triangle cb = Triangle(xg0);
Triangle f = Triangle(Vector(.0, .0, .0));
	
Rasterizer rast = Rasterizer(cb);


void display(void){
	
	
	glClear(GL_COLOR_BUFFER_BIT);	
	glBegin(GL_POINTS);

	cb.updateVertices(cam);
	f.updateVertices(cam);
	rast.render();

	glEnd();
	glFlush();
}

void special(int key, int x, int y){

	cb.updateAttitude(.3);
	display();
}




int main(int argc, char* argv[]){

	rast.addObject(f);
	
	glutInit(&argc,argv);
	
	glutInitDisplayMode(GLUT_RGB);

	glutInitWindowSize(1200, 800);
	
	glutCreateWindow("");
	
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	gluOrtho2D(-DEFAULT_WIDTH/2, DEFAULT_WIDTH/2, -DEFAULT_HEIGHT/2, DEFAULT_HEIGHT/2);
	glutMainLoop();

	return 0;
 
}
