#include <GL/glut.h>
#include "Triangle.h"
#include "Camera.h"
#include <vector>
#include "Vector.h"
#include "Rasterizer.h"

using namespace std;
	
Vector theta0 = Vector();
Vector x0 = Vector(.0, .0, -4.0);
Vector xg0 = Vector(.0, .0, 0.0);


Camera cam = Camera(x0, theta0);
Triangle cb = Triangle(xg0);
	
Rasterizer rast = Rasterizer(cb);


Vector x1 = Vector(20, 20, .0);
Vector x2 = Vector(-100, 180, .0);
Vector x3 = Vector(-100, 0, 0);


void display(void){
	
	
	glClear(GL_COLOR_BUFFER_BIT);	
	glBegin(GL_POINTS);
	

	vector<vector<int> > buffer;
	vector<vector<int> > buffer2;
	
	rast.rasterizeLine(x2, x1, buffer);
	rast.rasterizeLine(x2, x3, buffer2);

	cout << "Buffer start" << buffer[0][0] << ", " << buffer[0][1] << endl;
	cout << "Buffer start" << buffer2[0][0] << ", " << buffer2[0][1] << endl;
	for (auto const& vec: buffer2){
		glColor3d(.0, 1.0, .0);
		glVertex2i(vec[0], vec[1]);
	}
	for (auto const& vec: buffer){
		glColor3d(.0, 1.0, .0);
		glVertex2i(vec[0], vec[1]);
	}
	
		

	glEnd();
	glFlush();
}

void special(int key, int x, int y){
	
	cb.updateAttitude(.3);
	display();
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
