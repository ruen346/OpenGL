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
float moves[3];
int mode = 0;

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

	case 'X':
		ro[0] -= 0.01;
		break;

	case 'y':
		ro[1] += 0.01;
		break;

	case 'Y':
		ro[1] -= 0.01;
		break;

	case 'z':
		ro[2] += 0.01;
		break;

	case 'Z':
		ro[2] -= 0.01;
		break;

	case 'w':
		moves[1] -= 5;
		break;

	case 'a':
		moves[0] -= 5;
		break;

	case 's':
		moves[1] += 5;
		break;

	case 'd':
		moves[0] += 5;
		break;

	case '+':
		moves[2] += 5;
		break;

	case '-':
		moves[2] -= 5;
		break;

	case 'i':
		ro[0] = 0;
		ro[1] = 0;
		ro[2] = 0;
		moves[0] = 0;
		moves[1] = 0;
		moves[2] = 0;
		break;

	case 'm':
		if (mode == 1)
		{
			mode = 0;
			Reshape(800, 800);
		}
		else
		{
			mode = 1;
			Reshape(800, 600);
		}
		glutReshapeFunc(Reshape);
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
	GLdouble uu[16] = {
	cos(ro[1])*cos(ro[2]),-cos(ro[1])*sin(ro[2]),sin(ro[1]),0,
	(sin(ro[0])*sin(ro[1])*cos(ro[2])) + (cos(ro[0])*sin(ro[2])),(-sin(ro[0])*sin(ro[1])*sin(ro[2])) + (cos(ro[0])*cos(ro[2])),-sin(ro[0])*cos(ro[1]),0,
	(-cos(ro[0])*sin(ro[1])*cos(ro[2])) + (sin(ro[0])*sin(ro[2])),(cos(ro[0])*sin(ro[1])*sin(ro[2])) + (sin(ro[0])*cos(ro[2])),cos(ro[0])*cos(ro[1]),0,
	0,0,0,1
	};

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glu_fill = gluNewQuadric();
	glu_line = gluNewQuadric();
	gluQuadricDrawStyle(glu_fill, GLU_FILL);
	gluQuadricDrawStyle(glu_line, GLU_LINE);

	//glTranslatef(moves[0], moves[1], moves[2]);

	glPushMatrix();	

	glLoadIdentity();
	glLoadMatrixd(uu);
	glMultMatrixd(uu);

	gluLookAt(
		moves[0], moves[1], moves[2], //EYE
		0.0, 0.0, -300.0, //AT
		0.0, 1.0, 0.0); //UP
	//glPopMatrix();



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
	gluSphere(glu_fill, 15, 30, 30);

	glBegin(GL_LINES);
	rad = 60;
	for (int i = 0; i < 359; i++)
	{
		angle = i * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
		angle = (i + 1) * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
	}
	glEnd();
	glTranslatef(rad*cos(turn[0] * 3.14 / 180), 0, rad*sin(turn[0] * 3.14 / 180));
	gluSphere(glu_fill, 8, 8, 8);

	glPopMatrix();


	glPushMatrix();

	glRotatef(45, 0.0, 0.0, 1.0);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	rad = 120;
	for (int i = 0; i < 359; i++)
	{
		angle = i * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
		angle = (i + 1) * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
	}
	glEnd();
	glTranslatef(rad*cos(turn[1] * 3.14 / 180), 0, rad*sin(turn[1] * 3.14 / 180));
	gluSphere(glu_fill, 15, 15, 15);

	glBegin(GL_LINES);
	rad = 60;
	for (int i = 0; i < 359; i++)
	{
		angle = i * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
		angle = (i + 1) * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
	}
	glEnd();
	glTranslatef(rad*cos(turn[1] * 3.14 / 180), 0, rad*sin(turn[1] * 3.14 / 180));
	gluSphere(glu_fill, 8, 8, 8);

	glPopMatrix();


	glPushMatrix();

	glRotatef(-45, 0.0, 0.0, 1.0);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	rad = 120;
	for (int i = 0; i < 359; i++)
	{
		angle = i * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
		angle = (i + 1) * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
	}
	glEnd();
	glTranslatef(rad*cos(turn[2] * 3.14 / 180), 0, rad*sin(turn[2] * 3.14 / 180));
	gluSphere(glu_fill, 15, 15, 15);

	glBegin(GL_LINES);
	rad = 60;
	for (int i = 0; i < 359; i++)
	{
		angle = i * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
		angle = (i + 1) * 3.14 / 180;
		glVertex3f(rad*cos(angle), 0, rad*sin(angle));
	}
	glEnd();
	glTranslatef(rad*cos(turn[2] * 3.14 / 180), 0, rad*sin(turn[2] * 3.14 / 180));
	gluSphere(glu_fill, 8, 8, 8);

	glPopMatrix();


	glPopMatrix();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (mode == 0)
	{
		gluPerspective(60.0, 1.0, 1.0, 1000.0);

		gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -300.0, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, -300.0);
	}
	else
	{
		glOrtho(-400, 400, -300, 300, -400, 400);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}