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

int ro[3];
int moves[3];

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
		if (ro[0] < 355)
			ro[0] += 5;
		else
			ro[0] = 0;
		break;

	case 'X':
		if (ro[0] > 5)
			ro[0] -= 5;
		else
			ro[0] = 360;
		break;

	case 'y':
		if (ro[1] < 355)
			ro[1] += 5;
		else
			ro[1] = 0;
		break;

	case 'Y':
		if (ro[1] > 5)
			ro[1] -= 5;
		else
			ro[1] = 360;
		break;

	case 'z':
		if (ro[2] < 355)
			ro[2] += 5;
		else
			ro[2] = 0;
		break;

	case 'Z':
		if (ro[2] > 5)
			ro[2] -= 5;
		else
			ro[2] = 360;
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
	glRotatef(ro[0], 1.0, 0.0, 0.0);
	glRotatef(ro[1], 0.0, 1.0, 0.0);
	glRotatef(ro[2], 0.0, 0.0, 1.0);
	glTranslatef(moves[0], moves[1], moves[2]);


	glPushMatrix();


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