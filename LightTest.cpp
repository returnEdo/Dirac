#include <iostream>
#include <GL/glut.h>
#include "Camera.h"
#include <vector>
#include <string>
#include "WorldSpace.h"
#include "Controller.h"
#include "Object.h"
#include "Light.h"
#ifndef DEFAULT_WIDTH
#define DEFAULT_WIDTH 1920.0
#endif

#ifndef DEFAULT_HEIGHT
#define DEFAULT_HEIGHT 1080.0
#endif


using namespace std;
	
Vector xg0 = Vector(.0, .0, 0.0);
Vector theta0 = Vector(.2, .2, .2);
string address = "monkey.obj";
	
Object cb = Object(address, xg0, theta0);
Light light = Light(Vector(3.0, 3.0, -3.0));
WorldSpace wspace = WorldSpace();
Controller ctrl = Controller(wspace);

void display(void){
	
	
	glClear(GL_COLOR_BUFFER_BIT);	
	glBegin(GL_POINTS);

	wspace.updateVertices();
	wspace.render();

	glEnd();
	glFlush();
}

void special(int key, int x, int y){
	
	ctrl.specialKeyFunction(key, x, y);
	display();
}

void keyboard(unsigned char key, int x, int y){

	ctrl.specialKeyboardFunction(key, x, y);
	display();
}



int main(int argc, char* argv[]){
	
	wspace.addObject(cb);
	wspace.addLight(light);
	glutInit(&argc,argv);
	
	glutInitDisplayMode(GLUT_RGB);

	glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	
	glutCreateWindow("");
	
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	gluOrtho2D(-DEFAULT_WIDTH/2, DEFAULT_WIDTH/2, -DEFAULT_HEIGHT/2, DEFAULT_HEIGHT/2);
	glutMainLoop();

	return 0;
 
}
