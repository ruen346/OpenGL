#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int draw_mod = 0;
int pause = 0;
int mo_x = 400;
int mo_y = 300;
int x_big = 0;
int x_move = 0;

void Timer(int value)
{
	if (x_move == 1)
		mo_x++;
	else if(x_move == 2)
		mo_x--;

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1': 
		draw_mod = 1;
		break;
	case '2':
		draw_mod = 2;
		break;
	case '3':
		draw_mod = 3;
		break;
	case '4':
		draw_mod = 4;
		break;

	case 'x':
		mo_x -= 5;
		break;
	case 'X':
		mo_x += 5;
		break;
	case 'y':
		mo_y -= 5;
		break;
	case 'Y':
		mo_y += 5;
		break;
	case 's':
		x_big += 5;
		break;
	case 'S':
		x_big -= 5;
		break;
	case 'r':
		mo_x -= 5;
		break;
	case 'R':
		mo_x += 5;
		break;
	case 'a':
		x_move = 1;
		break;
	case 'A':
		x_move = 2;
		break;
	case 'T':
		x_move = 0;
		break;
	case 'Q':
		exit(1);
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

	switch (draw_mod)
	{
	case 1:
		for (float i = 0; i < 200; i++)
		{
			float ss = (i / 36 * 6.28);
			float xs, ys;

			xs = mo_x - 200 + i * 2 + (i * x_big / 10);
			ys = mo_y + 50 * cos(ss);

			glRectf(xs, ys, xs + 5, ys + 5);
		}
		break;
	case 2:
		for (float i = 0; i < 200; i++)
		{
			float ss = (i / 36 * 6.28);
			float xs, ys;

			xs = mo_x + (50 * cos(ss)) + i * (2 + x_big) - 200;
			ys = mo_y + 50 * sin(ss);

			glRectf(xs, ys, xs + 5, ys + 5);
		}
		break;
	case 3:
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex3i(mo_x - 200, mo_y - 150, 0);
		glVertex3i(mo_x + 200 + x_big, mo_y + 150, 0);

		glVertex3i(mo_x + 200 + x_big, mo_y + 150, 0);
		glVertex3i(mo_x + 200 + x_big, mo_y - 150, 0);

		glVertex3i(mo_x + 200 + x_big, mo_y - 150, 0);
		glVertex3i(mo_x - 200, mo_y + 150, 0);

		glVertex3i(mo_x - 200, mo_y + 150, 0);
		glVertex3i(mo_x - 200, mo_y - 150, 0);
		glEnd();
		break;
	case 4:
		glColor3f(1.0, 1.0, 1.0);
		glRectf(mo_x - 100 - x_big, mo_y - 100, mo_x + 100 + x_big, mo_y + 100);
		break;
	}

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3i(0, 300, 0);
	glVertex3i(800, 300, 0);
	glVertex3i(400, 0, 0);
	glVertex3i(400, 600, 0);
	glEnd();
	
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -400, 400);
}