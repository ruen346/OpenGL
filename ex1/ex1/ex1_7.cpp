#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int set_x[10];
int set_y[10];
int now = 0;
int now2 = 0;
float times = 0;
float times2[5];

void Timer(int value)
{
	if (times == 50)
		times = 0;
	else
		times++;

	for (int z = 0; z < now2 / 2; z++)
	{
		times2[z]++;
	}
	glutPostRedisplay(); // ȭ�� �� ��� 
	glutTimerFunc(20, Timer, 1); // Ÿ�̸��Լ� �� ����
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (now2 < 10)
			now2++;

		set_x[now] = x;
		set_y[now] = y;
		if (now < 10)
			now++;
		else
			now = 0;
	}
}


void main(int argc, char *argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("ex1_4"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(drawScene); // ��� �Լ��� ���� 
	glutTimerFunc(0, Timer, 1);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ� 
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �������� 'blue' �� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	float as = times / 50;
	glColor4f(as, 0, as, 1.0f);

	for (int j = 0; j < now2; j++)
	{
		for (int i = 0; i < 36; i++)
		{
			float ii = i;
			float ss = (ii / 36 * 6.28);
			float xs, ys;
			if (j % 2 == 1)
			{
				xs = set_x[j] + times2[j / 2] * cos(ss);
				ys = set_y[j] + times2[j / 2] * sin(ss);
			}
			else
			{
				xs = set_x[j] + times * cos(ss);
				ys = set_y[j] + times * sin(ss);
			}
			glRectf(xs, ys, xs + 5, ys + 5); // �簢�� �׸��� 
		}
	}
	glFlush(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}