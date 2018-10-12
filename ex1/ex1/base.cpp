#include <GL/freeglut.h>
#include <gl/glut.h> 
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *qobj;


int rotates[3];
int select = 0;//1부터 도형

void SetupRC()
{
	srand(time(NULL));

	for (int i = 0; i < 3; i++)
		rotates[i] = 0;
}

void Timer(int value)
{

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		rotates[0] += 10;
		break;

	case 'y':
		rotates[1] += 10;
		break;

	case 'z':
		rotates[2] += 10;
		break;


	case '1':
		select = 1;
		break;

	case '2':
		select = 2;
		break;

	case '3':
		select = 3;
		break;

	case '4':
		select = 4;
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
}

void Motion(int x, int y)
{

}


void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Points Drawing");

	SetupRC();

	glutDisplayFunc(drawScene);
	glutTimerFunc(0, Timer, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glRotatef(rotates[0], 1.0, 0.0, 0.0);
	glRotatef(rotates[1], 0.0, 1.0, 0.0);
	glRotatef(rotates[2], 0.0, 0.0, 1.0);


	glLineWidth(5);

	glBegin(GL_LINES);

	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(30, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 30, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 30);

	glEnd();


	glPushMatrix();

	glTranslatef(0, -100, 0);
	glScalef(300, 1, 300);
	glColor3f(1, 1, 1);
	glutSolidCube(1);

	glPopMatrix();


	qobj = gluNewQuadric();
	switch (select)
	{
	case 1:
		gluSphere(qobj, 50, 30, 30);
		break;
	}


	glPopMatrix();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 600.0);
	glTranslatef(0.0, 0.0, -300.0);

	glMatrixMode(GL_MODELVIEW);

	//gluLookAt(0.0, 0.0, 0.0,  0.0, 0.0, 1.0,  0.0, 1.0, 0.0);
}