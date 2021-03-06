#include <GL/freeglut.h>
#include <gl/glut.h> 
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *glu_fill;
GLUquadricObj *glu_line;


int rotates[3];
int rotates_select[2];
int select = 0;//1���� ����

void SetupRC()
{
	srand(time(NULL));

	for (int i = 0; i < 3; i++)
		rotates[i] = 0;

	rotates_select[0] = 0;
	rotates_select[1] = 0;
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


	case 'l':
		rotates_select[0] += 10;
		break;

	case 'r':
		rotates_select[1] += 10;
		break;

	case 'o':
		rotates_select[0] += 10;
		rotates_select[1] += 10;
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
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glu_fill = gluNewQuadric();
	glu_line = gluNewQuadric();
	gluQuadricDrawStyle(glu_fill, GLU_FILL);
	gluQuadricDrawStyle(glu_line, GLU_LINE);
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
	glLineWidth(1);


	glPushMatrix();

	glTranslatef(0, -100, 0);
	glScalef(300, 1, 300);
	glColor3f(1, 1, 1);
	glutSolidCube(1);

	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, -50, 0);
	switch (select)
	{
	case 1:
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslatef(-50, 0, 0);
		glRotatef(rotates_select[0], 0.0, 1.0, 0.0);
		gluSphere(glu_fill, 30, 30, 30);
		glPopMatrix();

		glColor3f(1, 0, 1);
		glPushMatrix();
		glTranslatef(50, 0, 0);
		glRotatef(rotates_select[1], 0.0, 1.0, 0.0);
		gluSphere(glu_line, 30, 30, 30);
		glPopMatrix();
		break;

	case 2:
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslatef(-50, 0, 0);
		glRotatef(rotates_select[0], 0.0, 1.0, 0.0);
		glutSolidCube(30);
		glPopMatrix();

		glColor3f(1, 0, 1);
		glPushMatrix();
		glTranslatef(50, 0, 0);
		glRotatef(rotates_select[1], 0.0, 1.0, 0.0);
		glutWireCube(30);
		glPopMatrix();
		break;

	case 3:
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslatef(-50, 0, 0);
		glRotatef(-90, 1, 0.0, 0);
		glRotatef(rotates_select[0], 0.0, 1.0, 0.0);
		gluCylinder(glu_fill, 30, 0.0, 30, 20, 8);
		glPopMatrix();

		glColor3f(1, 0, 1);
		glPushMatrix();
		glTranslatef(50, 0, 0);
		glRotatef(-90, 1, 0.0, 0);
		glRotatef(rotates_select[1], 0.0, 1.0, 0.0);
		gluCylinder(glu_line, 30, 0.0, 30, 20, 10);
		glPopMatrix();
		break;

	case 4:
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslatef(-50, 0, 0);
		glRotatef(rotates_select[0], 0.0, 1.0, 0.0);
		glutSolidTeapot(30);
		glPopMatrix();

		glColor3f(1, 0, 1);
		glPushMatrix();
		glTranslatef(50, 0, 0);
		glRotatef(rotates_select[1], 0.0, 1.0, 0.0);
		glutWireTeapot(30);
		glPopMatrix();
		break;
	}
	glPopMatrix();


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