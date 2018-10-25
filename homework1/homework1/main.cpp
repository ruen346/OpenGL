#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

struct Up_tr
{
	int x = -100;
	int y = 20;
	int ro = 0;
	int active = 1;
};

Up_tr up_tr[10];

void Timer(int value)
{
	for (int i = 0; i < 10; i++)
	{
		up_tr[i].x += 1;
		if (up_tr[i].x > 800)
			up_tr[i].x = -50;

		if (up_tr[i].ro < 357)
			up_tr[i].ro += 3;
		else
			up_tr[i].ro = 0;
	}

	glutPostRedisplay(); // ȭ�� �� ��� 
	glutTimerFunc(20, Timer, 1); // Ÿ�̸��Լ� �� ����
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
	}
	else if ((button == GLUT_LEFT_BUTTON && state == GLUT_UP))
	{
		
	}
}

void Motion(int x, int y)
{
	
}


void main(int argc, char *argv[])
{
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		up_tr[i].x = i * 85;
		up_tr[i].ro = i * 36;
	}


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 

	glutCreateWindow("homework1"); // ������ ���� (������ �̸�) 
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	glColor3ub(255, 255, 255);

	glPushMatrix();
	{
		glTranslatef(25, 25, 0.0);

		for (int i = 0; i < 10; i++)
		{
			glPushMatrix();
			{
				glTranslatef(up_tr[i].x, up_tr[i].y, 0.0);
				glRotatef(up_tr[i].ro, 0.0, 0.0, 1.0);

				glBegin(GL_POLYGON);
				glVertex2f(0, 0 - 25);
				glVertex2f(0 - 25, 0 + 25);
				glVertex2f(0 + 25, 0 + 25);
				glEnd();
			}
			glPopMatrix();
		}
	}glPopMatrix();

	glFlush(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}