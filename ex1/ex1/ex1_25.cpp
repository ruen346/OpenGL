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

int y_ro = 0;

void SetupRC()
{

	srand(time(NULL));
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
	case '[':
		y_ro += 5;
		break;

	case ']':
		y_ro -= 5;
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
	{
		gluLookAt(
			0.0, 0.0, 0.0, //EYE
			0.0, 0.0, -1.0, //AT
			0.0, 1.0, 0.0); //UP

		glTranslatef(0, -100, 0);
		glRotatef(y_ro, 0, 1, 0);

		glPushMatrix();//판
		{
			glColor3ub(255, 100, 100);
			glBegin(GL_POLYGON);
			glVertex3f(-300, 0, -300);
			glVertex3f(0, 0, -300);
			glVertex3f(-300, 0, 0);
			glEnd();

			glColor3ub(100, 255, 100);
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, -300);
			glVertex3f(300, 0, -300);
			glVertex3f(300, 0, 0);
			glEnd();

			glColor3ub(100, 100, 255);
			glBegin(GL_POLYGON);
			glVertex3f(-300, 0, 0);
			glVertex3f(-300, 0, 300);
			glVertex3f(0, 0, 300);
			glEnd();

			glColor3ub(100, 100, 100);
			glBegin(GL_POLYGON);
			glVertex3f(300, 0, 0);
			glVertex3f(300, 0, 300);
			glVertex3f(0, 0, 300);
			glEnd();

			glColor3ub(255, 255, 255);
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, -300);
			glVertex3f(-300, 0, 0);
			glVertex3f(0, 0, 300);
			glVertex3f(300, 0, 0);
			glEnd();
		}
		glPopMatrix();
			
		glPushMatrix();
		{
			glTranslatef(0, 50, 0);
			glRotatef(30, 1, 0, 0);
			glRotatef(45, 0, 1, 0);
			glShadeModel(GL_SMOOTH);

			glBegin(GL_QUADS);//위
			glColor3ub(0, 255, 255);
			glVertex3f(-50, 100, -50);
			glColor3ub(255, 0, 255);
			glVertex3f(-50, 100, 50);
			glColor3ub(255, 255, 255);
			glVertex3f(50, 100, 50);
			glColor3ub(255, 255, 0);
			glVertex3f(50, 100, -50);
			
			glColor3ub(255, 0, 0);//아래
			glVertex3f(-50, 0, -50);
			glColor3ub(0, 255, 0);
			glVertex3f(-50, 0, 50);
			glColor3ub(0, 0, 255);
			glVertex3f(50, 0, 50);
			glColor3ub(0, 0, 0);
			glVertex3f(50, 0, -50);

			glColor3ub(255, 0, 0);//왼쪽
			glVertex3f(-50, 0, -50);
			glColor3ub(0, 255, 0);
			glVertex3f(-50, 0, 50);
			glColor3ub(255, 0, 255);
			glVertex3f(-50, 100, 50);
			glColor3ub(0, 255, 255);
			glVertex3f(-50, 100, -50);
			
			glColor3ub(255, 255, 255);//오른쪽
			glVertex3f(50, 100, 50);
			glColor3ub(255, 255, 0);
			glVertex3f(50, 100, -50);
			glColor3ub(0, 0, 0);
			glVertex3f(50, 0, -50);
			glColor3ub(0, 0, 255);
			glVertex3f(50, 0, 50);

			glColor3ub(0, 255, 255);//뒤
			glVertex3f(-50, 100, -50);
			glColor3ub(255, 255, 0);
			glVertex3f(50, 100, -50);
			glColor3ub(0, 0, 0);
			glVertex3f(50, 0, -50);
			glColor3ub(255, 0, 0);
			glVertex3f(-50, 0, -50);

			glColor3ub(255, 0, 255);//앞
			glVertex3f(-50, 100, 50);
			glColor3ub(255, 255, 255);
			glVertex3f(50, 100, 50);
			glColor3ub(0, 0, 255);
			glVertex3f(50, 0, 50);
			glColor3ub(0, 255, 0);
			glVertex3f(-50, 0, 50);
			
			glEnd();

			glShadeModel(GL_FLAT);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -500.0);

	glMatrixMode(GL_MODELVIEW);
}