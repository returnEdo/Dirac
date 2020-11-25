#include <GL/glut.h>
#include "Cube.h"
#include "Camera.h"
#include <vector>
#include "Vector.h"
#include "RasterizeObject.h"

using namespace std;
	
Vector theta0 = Vector();
Vector x0 = Vector(.0, .0, -10.0);
Vector xg0 = Vector(.0, .0, 0.0);


Camera cam = Camera(x0, theta0);
Cube cb = Cube(xg0);
	



void display(void){
	
	
	glClear(GL_COLOR_BUFFER_BIT);	
	glBegin(GL_POINTS);

	cb.updateCamVertices(cam);
	cb.updatePixelVertices(cam);

	rasterizeObject(cb);

	glEnd();
	glFlush();
}

void special(int key, int x, int y){
	
	cb.updateAttitude(.2);
	glutPostRedisplay();	// or even display
}




int main(int argc, char* argv[]){
	
	
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
