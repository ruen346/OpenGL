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

float ball[3];
float ball_ro[3];

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
		ball[0] = 0;
		ball[1] = 0;
		ball[2] = 0;
		ball_ro[0] = 0;
		ball_ro[1] = 0;
		ball_ro[2] = 0;
		break;


	case 'l':
		if(ball[0] > -150)
			ball[0] -= 5;
		ball_ro[0] -= 5;
		break;
	case 'L':
		if (ball[0] < 150)
			ball[0] += 5;
		ball_ro[0] += 5;
		break;

	case 'm':
		ball_ro[1] -= 5;
		break;
	case 'M':
		ball_ro[1] += 5;
		break;

	case 'n':
		if (ball[2] > -150)
			ball[2] -= 5;
		ball_ro[2] -= 5;
		break;
	case 'N':
		if (ball[2] < 150)
			ball[2] += 5;
		ball_ro[2] += 5;
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
		glPushMatrix();//ÆÇ
		{
			glTranslatef(0.0, -30.0, 0.0);
			glScalef(300, 1, 300);
			glColor3f(1, 1, 1);
			glutSolidCube(1);
		}
		glPopMatrix();

		glPushMatrix();//°ø
		{
			glTranslatef(ball[0], 0, ball[2]);
			glRotatef(ball_ro[0] * -360 / (60 * 3.141592), 0, 0, 1);
			glRotatef(ball_ro[2] * 360 / (60 * 3.141592), 1, 0, 0);
			glRotatef(ball_ro[1] * 360 / (60 * 3.141592), 0, 1, 0);
			glColor3f(0, 0, 1);
			gluSphere(glu_line, 30, 20, 20);
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