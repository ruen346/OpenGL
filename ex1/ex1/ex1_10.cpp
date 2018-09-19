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
	int big = 15;
	int timer = 500;
	float active = 1;

	int move_x = 0;
	int move_y = 0;
};

nemo nemos[30];
nemo ch;


void Timer(int value)
{
	glutPostRedisplay(); // ȭ�� �� ��� 
	glutTimerFunc(20, Timer, 1); // Ÿ�̸��Լ� �� ����
	
	for (int i = 0; i < 30; i++)
	{
		if (nemos[i].active == 0)
		{
			if (nemos[i].x < 0 || nemos[i].x > 800)
			{
				if (nemos[i].move_x == 0)
					nemos[i].move_x = 1;
				else
					nemos[i].move_x = 0;
			}
			if (nemos[i].y < 0 || nemos[i].y > 600)
			{
				if (nemos[i].move_y == 0)
					nemos[i].move_y = 1;
				else
					nemos[i].move_y = 0;
			}

			if (nemos[i].move_x == 0)
				nemos[i].x -= 5;
			else
				nemos[i].x += 5;


			if (nemos[i].move_y == 0)
				nemos[i].y -= 5;
			else
				nemos[i].y += 5;

			if (nemos[i].timer > 0)
				nemos[i].timer--;
			else
			{
				nemos[i].timer = 500;
				nemos[i].active = 1;
				nemos[i].big = 15;
			}
		}
	}
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
	for (int i = 0; i < 30; i++)
	{
		if (ch.x < nemos[i].x + nemos[i].big && ch.x + 30 > nemos[i].x && ch.y < nemos[i].y + nemos[i].big && ch.y + 30 > nemos[i].y && ch.active == 1 && nemos[i].active == 1)
		{
			nemos[i].active = 0;
			nemos[i].color1 = rand() % 10;
			nemos[i].color1 /= 10;
			nemos[i].color2 = rand() % 10;
			nemos[i].color2 /= 10;
			nemos[i].color3 = rand() % 10;
			nemos[i].color3 /= 10;
			nemos[i].big = 60;
		}
	}
}


void main(int argc, char *argv[])
{
	srand(time(NULL));

	for (int i = 0; i < 30; i++)
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


	for (int i = 0; i < 30; i++)
	{
		glColor4f(nemos[i].color1, nemos[i].color2, nemos[i].color3, 1.0f);

		if(nemos[i].active == 1)
			glRectf(nemos[i].x, nemos[i].y, nemos[i].x + nemos[i].big, nemos[i].y + nemos[i].big);
		else
		{
			if (nemos[i].timer > 440)
			{
				glBegin(GL_POLYGON);
				glVertex2f(nemos[i].x, nemos[i].y);
				glVertex2f(nemos[i].x + nemos[i].big - 500 + nemos[i].timer , nemos[i].y);
				glVertex2f(nemos[i].x + nemos[i].big, nemos[i].y + nemos[i].big);
				glVertex2f(nemos[i].x, nemos[i].y + nemos[i].big);
				glEnd();
			}
			else
			{
				glBegin(GL_POLYGON);
				glVertex2f(nemos[i].x, nemos[i].y);
				glVertex2f(nemos[i].x + nemos[i].big, nemos[i].y + nemos[i].big);
				glVertex2f(nemos[i].x, nemos[i].y + nemos[i].big);
				glEnd();
			}
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