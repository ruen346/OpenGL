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
float times2[10];

void Timer(int value)
{
	for (int z = 0; z < now; z++)
	{
		if (times2[z] < 216)
			times2[z]++;
		else
			times2[z] = 0;
	}
	glutPostRedisplay(); // ȭ�� �� ��� 
	glutTimerFunc(20, Timer, 1); // Ÿ�̸��Լ� �� ����
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		set_x[now] = x;
		set_y[now] = y;
		if (now < 9)
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

	glColor4f(1, 0, 0, 1.0f);

	for (int j = 0; j < now; j++)
	{
		int times3 = 0;
		if (times2[j] < 108)
			times3 = times2[j];
		else
			times3 = 108;

		for (int i = 0; i < times3; i++)
		{
			float ii = i;
			float ss = (ii / 36 * 6.28);
			float xs, ys;

			xs = set_x[j] + i * cos(ss);
			ys = set_y[j] + i * sin(ss);

			glRectf(xs, ys, xs + 5, ys + 5); // �簢�� �׸��� 
		}

		if (times2[j] >= 108)
		{
			for (int i = 108; i < times2[j]; i++)
			{
				float ii = i;
				float ss = (ii / 36 * 6.28);
				float xs, ys;

				xs = set_x[j] + (216 - i) * -cos(ss) + 220;
				ys = set_y[j] + (216 - i) * sin(ss);

				glRectf(xs, ys, xs + 5, ys + 5); // �簢�� �׸��� 
			}
		}
	}
	glFlush(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}