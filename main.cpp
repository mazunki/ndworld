/*
 * GL01Hello.cpp: Test OpenGL C/C++ Setup
 */
#include <iostream>
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h

class Coord {
	public:
		float x, y, z;
		Coord(float x_, float y_, float z_) {
			this->x = x_;
			this->y = y_;
			this->z = z_;
		}
};

class Vector {
	public:
		Coord *vStart, *vEnd;
		Vector(Coord vStart_, Coord vEnd_) {
			this->vStart = &vStart_;
			this->vEnd = &vEnd_;
		}

		void render() {
			glBegin(GL_LINES);
				glVertex3f(this->vStart->x, this->vStart->y, this->vStart->z);
				glVertex3f(this->vEnd->x, this->vEnd->y, this->vEnd->z);
			glEnd();
		};
};

class Cube {
	static const int sizeX=16.0, sizeY=16.0, sizeZ=16.0;
	public:
		int x,y,z; // position on map
		Coord *p0, *p1, *p2, *p3, *p4, *p5, *p6, *p7;
		Vector *v01, *v12, *v23, *v30, \
				*v45, *v56, *v67, *v74, \
				*v04, *v73, *v15, *v62;
		Cube() {
			Coord p0(0,0,0);
			Coord p1(1,0,0);
			Coord p2(1,1,0);
			Coord p3(0,1,0);
			
			Coord p4(0,0,1);
			Coord p5(1,0,1);
			Coord p6(1,1,1);
			Coord p7(0,1,1);

			Vector v01(p0, p1);
			Vector v12(p1, p2);
			Vector v23(p2, p3);
			Vector v30(p3, p0);

			Vector v45(p4, p5);
			Vector v56(p5, p6);
			Vector v67(p6, p7);
			Vector v74(p7, p4);

			Vector v04(p0, p4);
			Vector v73(p7, p3);
			Vector v15(p1, p5);
			Vector v62(p6, p2);
		}

		void render() {
			v01->render();
			v12->render();
			v23->render();
			v30->render();
			v45->render();
			v56->render();
			v67->render();
			v74->render();
			v04->render();
			v73->render();
			v15->render();
			v62->render();
		}
};

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer

	Cube c;
	c.render();
	glFlush();  // Render now
}
 
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	int monWidth=1920, monHeight=1080, winH=600, winW=400;
	int monCenterH = (monHeight-winW)/2.0 + monHeight; // moving into monitor 2
	int monCenterW = (monWidth-winH)/2.0 + monWidth; // moving into monitor 3

	glutInit(&argc, argv);
	glutInitWindowSize(winH, winW);
	glutInitWindowPosition(monCenterW, monCenterH);

	glutCreateWindow("n-Dimensional World");
	glutDisplayFunc(display);
	glutMainLoop();
	
	return 0;
}
