#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

struct Nemo
{
	int x;
	int y;
	float color[3];
	int big = 0;
	int choose = 0;
};

Nemo nemo[20];
int counts = 0;
int turn = 0;
int mod = 0;

void Timer(int value)
{
	for (int i = 0; i < 20; i++)
	{
		if(nemo[i].big > 0)
			nemo[i].big--;
	}

	if (mod == 0)
	{
		if (turn < 359)
			turn++;
		else
			turn = 0;
	}
	else
	{
		if (turn > 0)
			turn--;
		else
			turn = 359;
	}

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'm': 
		if (mod == 0)
			mod = 1;
		else
			mod = 0;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (counts == 20)
			counts = 0;

		nemo[counts].x = x;
		nemo[counts].y = y;
		nemo[counts].color[0] = rand() % 10;
		nemo[counts].color[1] = rand() % 10;
		nemo[counts].color[2] = rand() % 10;
		nemo[counts].color[0] /= 10;
		nemo[counts].color[1] /= 10;
		nemo[counts].color[2] /= 10;
		nemo[counts].big = rand() % 50 + 50;
		nemo[counts].choose = rand() % 4;

		counts++;
	}
}

void Motion(int x, int y)
{

}


void main(int argc, char *argv[])
{
	srand(time(NULL));

	//변수초기화

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);

	glutCreateWindow("ex1_11");
	glutDisplayFunc(drawScene);
	glutTimerFunc(0, Timer, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	for (int i = 0; i < 20; i++)
	{
		glPushMatrix();
		glTranslatef(nemo[i].x, nemo[i].y, 0.0);
		glRotatef(turn, 1.0, 1.0, 0.0);

		glColor3f(nemo[i].color[0], nemo[i].color[1], nemo[i].color[2]);

		if (nemo[i].big > 1)
		{
			switch (nemo[i].choose)
			{
			case 0:
				glutWireCube(nemo[i].big); break;
			case 1:
				glutWireSphere(nemo[i].big, 10, 10); break;
			case 2:
				glutWireTorus(nemo[i].big, nemo[i].big + 20, 10, 10); break;
			case 3:
				glutWireTeapot(nemo[i].big); break;
			}
		}

		glPopMatrix();
	}

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -400, 400);
}