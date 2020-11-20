#include <GL/glut.h>
#include <cmath>
#include "Cube.h"
#include "Camera.h"
#include <vector>
#include "Vector.h"

#define pi M_PI



Vector xCam0 = Vector(.0, .0, -10);
Vector xcg0 = Vector(.0, .0, .0);
Vector theta0 = Vector(0, 0, 0);

Camera cam = Camera(xCam0, Vector(), M_PI / 4);
Cube obj = Cube(xcg0, theta0);





void display(){
	obj.updateCamVertices(cam);
	obj.updateNormalizedVertices(cam);

	vector<vector<int> > b = obj.getIndexBuffer();
	vector<Vector> vr = obj.getNormalizedVertices();

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	for (auto const& side: b){
		
		glBegin(GL_LINE_LOOP);
		glColor3d(1, 1, 1);		
		
		glVertex3d(vr[side[0]].x, vr[side[0]].y, 0);
		glVertex3d(vr[side[1]].x, vr[side[1]].y, 0);
		glVertex3d(vr[side[2]].x, vr[side[2]].y, 0);

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
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(1200, 800);
	
	glutCreateWindow("");
	
	glEnable(GL_DEPTH_TEST);
	
	
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);

	glutMainLoop();

	return 0;
 
}
