#include <GL/freeglut.h> 
#include <time.h>
#include <iostream>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int set_x[10];
int set_y[10];
int set_move[10];
int now = 0;
float times = 0;
int start = 0;
int speed = 20;

void Timer(int value)
{
	if (times == 50)
		times = 0;
	else
		times++;
	for (int i = 0; i < start; i++)
	{
		if (set_move[i] == 0)
		{
			if (set_y[i] < 10)
				set_move[i] = 2;
			else
			{
				set_x[i] -= 10;
				set_y[i] -= 10;
			}
			if (set_x[i] < 10)
				set_move[i] = 3;
		}
		if (set_move[i] == 1)
		{
			if (set_y[i] > 590 - (times * 2))
				set_move[i] = 3;
			else
			{
				set_x[i] += 10;
				set_y[i] += 10;
			}
			if (set_x[i] > 790 - (times * 2))
				set_move[i] = 2;
		}
		if (set_move[i] == 2)
		{
			if (set_x[i] < 10)
				set_move[i] = 1;
			else
			{
				set_x[i] -= 10;
				set_y[i] += 8;
			}
			if (set_y[i] > 590 - (times * 2))
				set_move[i] = 0;
		}
		if (set_move[i] == 3)
		{
			if (set_x[i] > 790 - (times * 2))
				set_move[i] = 0;
			else
			{
				set_x[i] += 10;
				set_y[i] -= 10;
			}
			if (set_y[i] < 10)
				set_move[i] = 1;
		}
	}
	glutPostRedisplay(); // ȭ�� �� ��� 
	glutTimerFunc(speed, Timer, 1); // Ÿ�̸��Լ� �� ����
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (start < 10)
			start++;
		set_x[now] = x;
		set_y[now] = y;
		if (now < 9)
			now++;
		else
			now = 0;
		cout << x << endl << y << endl;
	}
}

void Keyboard(unsigned char key, int x, int y) 
{
	switch (key) 
	{ 
	case 'a': 
		speed ++; 
		break;
	case 's':
		if(speed > 1)
			speed--; 
		break;
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
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	for (int i = 0; i < 10; i++)
	{
		set_x[i] = 0;
		set_y[i] = 0;
		set_move[i] = 0;
	}
}

// ������ ��� �Լ� 
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �������� 'blue' �� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	float as = times / 50;
	glColor4f(as, as, as, 1.0f);
	for (int i = 0; i < start; i++)
	{
		glRectf(set_x[i], set_y[i], set_x[i] + times * 2, set_y[i] + times * 2); // �簢�� �׸��� 
	}

	glFlush(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}