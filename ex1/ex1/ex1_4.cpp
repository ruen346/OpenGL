#include <GL/freeglut.h> 
#include <time.h>
#include <iostream>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int set_x[10];
int set_y[10];
int now = 0;
float times = 0;

void Timer(int value)
{
	if (times == 50)
		times = 0;
	else
		times++;
	glutPostRedisplay(); // ȭ�� �� ��� 
	glutTimerFunc(20, Timer, 1); // Ÿ�̸��Լ� �� ����
}

void Mouse(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
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
	glColor4f(as, as, as, 1.0f);
	for (int i = 0; i < 10; i++)
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