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
	float active = 0;
};

nemo nemos[100];


void Timer(int value)
{

	glutPostRedisplay(); // ȭ�� �� ��� 
	glutTimerFunc(20, Timer, 1); // Ÿ�̸��Լ� �� ����
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
}


void main(int argc, char *argv[])
{
	srand(time(NULL));

	for (int i = 0; i < 100; i++)
	{
		nemos[i].x = rand() % 800;
		nemos[i].y = rand() % 600;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 

	glutCreateWindow("ex1_9"); // ������ ���� (������ �̸�) 
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

	glRectf(0, 0, 5, 5); // �簢�� �׸��� 

	glFlush(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}