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

int turn[3];
float ro[3];

void SetupRC()
{
	srand(time(NULL));

}

void Timer(int value)
{
	if (turn[0] < 359 * 3)
		turn[0]++;
	else
		turn[0] = 0;

	turn[1] = turn[0] * 2 / 3;
	turn[2] = turn[0] / 3;

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		ro[0] += 0.01;
		break;

	case 'y':
		ro[1] += 0.01;
		break;

	case 'z':
		ro[2] += 0.01;
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
	GLdouble xx[16] = {
	1,0,0,0,
	0,cos(ro[0]),-sin(ro[0]),0,
	0,sin(ro[0]),cos(ro[0]),0,
	0,0,0,1
	};
	GLdouble yy[16] = {
	cos(ro[1]),0,sin(ro[1]),0,
	0,1,0,0,
	-sin(ro[1]),0,cos(ro[1]),0,
	0,0,0,1
	};
	GLdouble zz[16] = {
	cos(ro[2]),-sin(ro[2]),0,0,
	sin(ro[2]),cos(ro[2]),0,0,
	0,0,1,0,
	0,0,0,1
	};

	GLdouble uu[16];
	for (int i = 0; i < 16; i++)
		uu[i] = xx[i] + yy[i] + zz[i];


	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glu_fill = gluNewQuadric();
	glu_line = gluNewQuadric();
	gluQuadricDrawStyle(glu_fill, GLU_FILL);
	gluQuadricDrawStyle(glu_line, GLU_LINE);

	glPushMatrix();
	glLoadIdentity();
	glLoadMatrixd(uu);
	//glLoadMatrixd(yy);
	//glLoadMatrixd(zz);

	glPushMatrix();
	gluLookAt(
		1.0, 1.0, 1.0, //EYE
		0.0, 0.0, 0.0, //AT
		0.0, 1.0, 0.0); //UP
	glMultMatrixd(uu);
	//glMultMatrixd(yy);
	//glMultMatrixd(zz);
	glPopMatrix();

	//glRotatef(10, 1.0, 0.0, 0.0);
	glColor3f(0, 0, 1);
	gluSphere(glu_fill, 30, 30, 30);


	glPushMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	float rad = 120;
	float angle;
	for (int i = 0; i < 359; i++)
	{
		angle = i * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
		angle = (i + 1) * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
	}
	glEnd();
	glTranslatef(rad*cos(turn[0] * 3.14 / 180), 0, rad*sin(turn[0] * 3.14 / 180));
	gluSphere(glu_fill, 15, 15, 15);

	glPopMatrix();


	glPushMatrix();

	glRotatef(45, 0.0, 0.0, 1.0);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (int i = 0; i < 359; i++)
	{
		float rad = 120;
		float angle;
		angle = i * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
		angle = (i + 1) * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
	}
	glEnd();
	glTranslatef(rad*cos(turn[1] * 3.14 / 180), 0, rad*sin(turn[1] * 3.14 / 180));
	gluSphere(glu_fill, 15, 15, 15);

	glPopMatrix();


	glPushMatrix();

	glRotatef(-45, 0.0, 0.0, 1.0);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (int i = 0; i < 359; i++)
	{
		float rad = 120;
		float angle;
		angle = i * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
		angle = (i + 1) * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
	}
	glEnd();
	glTranslatef(rad*cos(turn[2] * 3.14 / 180), 0, rad*sin(turn[2] * 3.14 / 180));
	gluSphere(glu_fill, 15, 15, 15);

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

	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
}