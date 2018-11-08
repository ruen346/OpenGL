#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int point_x[19];
int point_y[19];
int point = 0;

int moves = 0;
int rights = 0;

void Timer(int value)
{

	glutPostRedisplay(); // ȭ�� �� ��� 
	glutTimerFunc(20, Timer, 1); // Ÿ�̸��Լ� �� ����
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = point; i < 19; i++)
		{
			point_x[i] = x;
			point_y[i] = y;
		}
		point++;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		for (int i = 0; i < 19; i++)
		{
			if (abs(x - point_x[i]) > 5 && abs(y - point_y[i]) > 5)
				moves = i;
		}
		point++;
		rights = 1;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		rights = 0;
	}
}

void Motion(int x, int y)
{
	if (rights == 1)
	{
		point_x[moves] = x;
		point_y[moves] = y;
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		for (int i = 0; i < 19; i++)
		{
			point_x[i] = 0;
			point_y[i] = 0;
			point = 0;
		}
	}
}


void main(int argc, char *argv[])
{
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 

	glutCreateWindow("ex1_28"); // ������ ���� (������ �̸�) 
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


	/////////////
	for (int r = 0; r < 6; r++)
	{
		GLfloat ctrlpoints[4][3] = { {point_x[r * 3], point_y[r * 3]}, {point_x[r * 3 + 1], point_y[r * 3 + 1]}, {point_x[r * 3 + 2], point_y[r * 3 + 2]} , {point_x[r * 3 + 3], point_y[r * 3 + 3]} };
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
		glEnable(GL_MAP1_VERTEX_3);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 10; i++)
			glEvalCoord1f((GLfloat)i / 10.0);
		glEnd();

		glDisable(GL_MAP1_VERTEX_3);
		glPointSize(5.0);
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < 4; i++)
			glVertex3fv(&ctrlpoints[i][0]);
		glEnd();
	}
	////////////////


	glFlush(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}