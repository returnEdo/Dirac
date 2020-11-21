#include <GL/glut.h>
#include <cmath>
#include "Cube.h"
#include "Camera.h"
#include <vector>
#include "Vector.h"

#define pi M_PI



Vector xCam0 = Vector(.0, .0, -10);
Vector xcg0 = Vector(.0, 2, .0);
Vector theta0 = Vector(0, 0, 0);

Camera cam = Camera(xCam0, Vector(), M_PI / 4);
Cube obj = Cube(xcg0, theta0);



void putPixel(double x, double y){
	
	glColor3d(1, 0, 0);
	glVertex2d(.0, .0);
}




void display(){
	obj.updateCamVertices(cam);
	obj.updateNormalizedVertices(cam);

	vector<vector<int> > b = obj.getIndexBuffer();
	vector<Vector> vr = obj.getNormalizedVertices();

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	for (auto const& side: b){
		
		glBegin(GL_POINTS);
		glColor3d(1, 0, 0);
		glVertex2d(.0, .0);
		glEnd();
		
		glBegin(GL_LINE_LOOP);
		glColor3d(1, 1, 1);		
		
		glVertex2d(vr[side[0]].x, vr[side[0]].y);
		glVertex2d(vr[side[1]].x, vr[side[1]].y);
		glVertex2d(vr[side[2]].x, vr[side[2]].y);

		glEnd();
	}

	
	glutSwapBuffers();
 
}

void specialKeys( int key, int x, int y ) {
	
	if (key == 102){ obj.updateAttitude(M_PI / 15); }
	
	if (key == 103){ cam.changeFOV(M_PI / 15); }
	
	glutPostRedisplay();
	
}



int main(int argc, char* argv[]){
	
	
	glutInit(&argc,argv);
	
	glutInitDisplayMode(GLUT_RGB);

	glutInitWindowSize(1200, 800);
	
	glutCreateWindow("");
	
	
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	glutMainLoop();

	return 0;
 
}
