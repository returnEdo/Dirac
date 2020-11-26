#include <GL/glut.h>
#include <vector>
#include "LineRasterizer.h"
#include <iostream>
#include <cmath>


using namespace std;

#define WIDTH 1200
#define HEIGHT 800





//~ void render(void){

	//~ vector<int> x0 = {0, 0};
	
	//~ glClear(GL_COLOR_BUFFER_BIT);

	//~ int n = 12;
	//~ for (int i = 0; i < n; i++){ ~ vector<int> x1 = {int(floor(200 *
	//cos(2 * M_PI / n * i))), int(floor(200 * sin(2 * M_PI / n * i)))}; ~
	//vector<vector<int> > buffer;
		
		//~ rasterizeLineForTriangles(0, 0, x1[0], x1[1], buffer);
		
		//~ glColor3f(1, .0, .0); ~ glBegin(GL_POINTS);
		
		//~ cout << buffer.size() << endl;

		//~ for (auto const& Vec: buffer){ ~ glVertex2i(Vec[0],
		//Vec[1]); ~ }

		//~ glEnd(); ~ }

	//~ glFlush(); ~ }

void render(void){

	vector<int> x0 = {0, 0};
	
	glClear(GL_COLOR_BUFFER_BIT);

	vector<int> x1 = {300, 20}; vector<int> x2 = {20, 300};
	vector<vector<int> > buffer1; vector<vector<int> > buffer2;
	
	rasterizeLineForTriangles(.0, .0, -30, -50, buffer2);
	rasterizeLineForTriangles(-200,.0, -30, -50, buffer1);
	
	glColor3f(1, .0, .0);
	glBegin(GL_POINTS);
	
	cout << buffer1.size() << endl;
	cout << buffer2.size() << endl;

	for (auto const& Vec: buffer1){
		glVertex2i(Vec[0], Vec[1]);
	}
	for (auto const& Vec: buffer2){
		glVertex2i(Vec[0], Vec[1]);
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
