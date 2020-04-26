/*
 * GL01Hello.cpp: Test OpenGL C/C++ Setup
 */
#include <iostream>
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h

class Coord {
	public:
		float x, y, z;
		Coord(float x_, float y_, float z_) {
			this->x = x_/4.0f;
			this->y = y_/4.0f;
			this->z = z_/4.0f;
		}
};

class Vector {
	public:
		Coord *vStart, *vEnd;
		Vector(Coord *vStart_, Coord *vEnd_) {
			this->vStart = vStart_;
			this->vEnd = vEnd_;
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
		Vector *v71, *v60;
		Cube() {
			p0 = new Coord(-0.5f, -0.5f, -0.5f);
			p1 = new Coord(0.5f, -0.5f, -0.5f);
			p2 = new Coord(0.5f, 0.5f, -0.5f);
			p3 = new Coord(-0.5f, 0.5f, -0.5f);
			
			p4 = new Coord(-0.5f, -0.5f, 0.5f);
			p5 = new Coord(0.5f, -0.5f, 0.5f);
			p6 = new Coord(0.5f, 0.5f, 0.5f);
			p7 = new Coord(-0.5f, 0.5f, 0.5f);

			v01 = new Vector(p0, p1);
			v12 = new Vector(p1, p2);
			v23 = new Vector(p2, p3);
			v30 = new Vector(p3, p0);
			v45 = new Vector(p4, p5);
			v56 = new Vector(p5, p6);
			v67 = new Vector(p6, p7);
			v74 = new Vector(p7, p4);
			v04 = new Vector(p0, p4);
			v73 = new Vector(p7, p3);
			v15 = new Vector(p1, p5);
			v62 = new Vector(p6, p2);

			v71 = new Vector(p7, p1);
			v60 = new Vector(p6, p0);
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

			v71->render();
			v60->render();
		}
};

Cube c;
float viewX=0.0f, viewY=0.0f, viewZ=0.0f;

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
    glMatrixMode(GL_MODELVIEW);
	
	glRotatef(-30.0, 0.1f, 0.2f, 0.0f);

	c.render();
	glFlush();  // Render now
}
 
void keyPressed (unsigned char key, int x, int y) {  
	if (key == 'q') {
		exit(0);
	}

	if (key == 'w') {
		viewY -= 0.03f;
	} else if (key == 's') {
		viewY += 0.03f;
	} 

	if (key == 'a') {
		viewX -= 0.03f;
	} else if (key == 'd') {
		viewX += 0.03f;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(viewX, viewY, viewZ);
	viewX=0.0f;
	viewY=0.0f;
	viewZ=0.0f;
	c.render();
	glFlush();
}  

void mouseClick(int button, int state, int x, int y) {
	if (state==GLUT_DOWN) {
		if (button==3) {
			viewZ=0.03f;
			glTranslatef(viewX, viewY, viewZ);
			viewZ=0.0f;
			glClear(GL_COLOR_BUFFER_BIT);
			c.render();
			glFlush();
		}
		if (button==4) {
			viewZ=-0.03f;
			glTranslatef(viewX, viewY, viewZ);
			viewZ=0.0f;
			glClear(GL_COLOR_BUFFER_BIT);
			c.render();
			glFlush();
		}
	}
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
	glutKeyboardFunc(keyPressed);
	glutMouseFunc(mouseClick);


	glutMainLoop();
	
	return 0;
}
