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
	glutPostRedisplay(); // 화면 재 출력 
	glutTimerFunc(20, Timer, 1); // 타이머함수 재 설정
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("ex1_4"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정 
	glutTimerFunc(0, Timer, 1);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// 윈도우 출력 함수 
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 

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

			glRectf(xs, ys, xs + 5, ys + 5); // 사각형 그리기 
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

				glRectf(xs, ys, xs + 5, ys + 5); // 사각형 그리기 
			}
		}
	}
	glFlush(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}