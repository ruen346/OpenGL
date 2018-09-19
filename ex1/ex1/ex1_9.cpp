#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

struct nemo
{
	int x;
	int y;
	float color1;
	float color2;
	float color3;
	float active = 1;
};

nemo nemos[100];
nemo ch;


void Timer(int value)
{

	glutPostRedisplay(); // ȭ�� �� ��� 
	glutTimerFunc(20, Timer, 1); // Ÿ�̸��Լ� �� ����
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		ch.active = 1;
	}
	else if ((button == GLUT_LEFT_BUTTON && state == GLUT_UP))
	{
		ch.active = 0;
	}
}

void Motion(int x, int y)
{
	ch.x = x;
	ch.y = y;
	for (int i = 0; i < 100; i++)
	{
		if (ch.x < nemos[i].x + 15 && ch.x + 30 > nemos[i].x && ch.y < nemos[i].y + 15 && ch.y + 30 > nemos[i].y && ch.active)
		{
			nemos[i].active = 0;
		}
	}
}


void main(int argc, char *argv[])
{
	srand(time(NULL));

	for (int i = 0; i < 100; i++)
	{
		nemos[i].x = rand() % 800;
		nemos[i].y = rand() % 600;
		nemos[i].color1 = rand() % 10;
		nemos[i].color1 /= 10;
		nemos[i].color2 = rand() % 10;
		nemos[i].color2 /= 10;
		nemos[i].color3 = rand() % 10;
		nemos[i].color3 /= 10;

		ch.x = 0;
		ch.y = 0;
		ch.active = 0;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 

	glutCreateWindow("ex1_9"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(drawScene); // ��� �Լ��� ���� 
	glutTimerFunc(0, Timer, 1);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ� 
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �������� 'blue' �� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 



	for (int i = 0; i < 100; i++)
	{
		if (nemos[i].active == 1)
		{
			glColor4f(nemos[i].color1, nemos[i].color2, nemos[i].color3, 1.0f);
			glRectf(nemos[i].x, nemos[i].y, nemos[i].x + 15, nemos[i].y + 15);
		}
		if (ch.active == 1)
		{
			glColor4f(0, 0, 0, 1.0f);
			glRectf(ch.x, ch.y, ch.x + 30, ch.y + 30);
		}
	}


	glFlush(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}