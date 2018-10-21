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

float camera_rotation[3];
int moves[3];

int d[3];//하부 좌표
int d_ro[3];
int m_ro[3];
int u_ro[3];

int sw = 0;

void SetupRC()
{
	d[1] = 30;
	camera_rotation[0] = -0.3;

	srand(time(NULL));
}

void Timer(int value)
{
	if (sw == 0 && d[0] > -240)
		d[0] -= 5;
	else if (sw == 0)
		sw = 1;

	if (sw == 1 && d[0] < 240)
		d[0] += 5;
	else if (sw == 1)
		sw = 0;

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		camera_rotation[0] += 0.02;
		break;

	case 'X':
		camera_rotation[0] -= 0.02;
		break;

	case 'y':
		camera_rotation[1] += 0.02;
		break;

	case 'Y':
		camera_rotation[1] -= 0.02;
		break;

	case 'z':
		camera_rotation[2] += 0.02;
		break;

	case 'Z':
		camera_rotation[2] -= 0.02;
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
		Reshape(800, 800);
		break;

	case '-':
		moves[2] -= 5;
		Reshape(800, 800);
		break;

	case 'i':
		camera_rotation[0] = 0;
		camera_rotation[1] = 0;
		camera_rotation[2] = 0;
		moves[0] = 0;
		moves[1] = 0;
		moves[2] = 0;
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
	cos(camera_rotation[1])*cos(camera_rotation[2]),-cos(camera_rotation[1])*sin(camera_rotation[2]),sin(camera_rotation[1]),0,
	(sin(camera_rotation[0])*sin(camera_rotation[1])*cos(camera_rotation[2])) + (cos(camera_rotation[0])*sin(camera_rotation[2])),(-sin(camera_rotation[0])*sin(camera_rotation[1])*sin(camera_rotation[2])) + (cos(camera_rotation[0])*cos(camera_rotation[2])),-sin(camera_rotation[0])*cos(camera_rotation[1]),0,
	(-cos(camera_rotation[0])*sin(camera_rotation[1])*cos(camera_rotation[2])) + (sin(camera_rotation[0])*sin(camera_rotation[2])),(cos(camera_rotation[0])*sin(camera_rotation[1])*sin(camera_rotation[2])) + (sin(camera_rotation[0])*cos(camera_rotation[2])),cos(camera_rotation[0])*cos(camera_rotation[1]),0,
	0,0,0,1
	};

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

	gluLookAt(
		moves[0], moves[1], 0.0, //EYE
		0.0, 0.0, -300.0, //AT
		0.0, 1.0, 0.0); //UP
	glMultMatrixd(uu);

	glPushMatrix();
	{
		glPushMatrix();//판
		{
			glScalef(600, 1, 600);
			glColor3f(1, 1, 1);
			glutSolidCube(1);
		}
		glPopMatrix();

		glPushMatrix();//하중상부
		{
			glTranslatef(d[0], d[1], d[2]);
			glPushMatrix();//하부
			{
				glColor3f(1, 0, 0);
				glScalef(2, 1, 2);
				glutSolidCube(30);
			}
			glPushMatrix();//중부
			{
				glTranslatef(0, 35, 0);
				glColor3f(0, 1, 0);
				glScalef(1, 4, 1);
				glutSolidCube(10);
			}
		}
		glPopMatrix();
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
	gluPerspective(60.0 - moves[2], 1.0, 1.0, 600.0);
	glTranslatef(0.0, 0.0, -300.0);

	glMatrixMode(GL_MODELVIEW);

	gluLookAt(
		moves[0], moves[1], 0.0,
		0.0, 0.0, -300.0,
		0.0, 1.0, 0.0);
}