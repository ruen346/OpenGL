#include <GL/freeglut.h> 
#include <time.h>
#include <iostream>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int set_x[10];
int set_y[10];
int set_move[10];
int set_save[10];
int set_go[10];
int now = 0;
float times = 0;
int start = 0;
int speed = 20;
int what = 0;
int pause = 0;

void Timer(int value)
{
	if (times == 50)
		times = 0;
	else
		times++;
	for (int i = 0; i < start; i++)
	{
		if (set_save[i] == 0)
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
		else
		{
			if (set_go[i] == 0)
			{
				if (set_x[i] < 10)
					set_go[i] = 1;
				else
					set_x[i] -= 10;
			}
			else if (set_go[i] == 1)
			{
				if (set_y[i] > 590 - (times * 2))
					set_go[i] = 2;
				else
					set_y[i] += 10;
			}
			else if (set_go[i] == 2)
			{
				if (set_x[i] > 790 - (times * 2))
					set_go[i] = 3;
				else
					set_x[i] += 10;
			}
			else if (set_go[i] == 3)
			{
				if (set_y[i] < 250)
					set_go[i] = 4;
				else
					set_y[i] -= 10;
			}
			else if (set_go[i] == 4)
			{
				if (set_x[i] < 350)
				{
					set_save[i] = 0;
					set_go[i] = 0;
				}
				else
					set_x[i] -= 10;
			}
		}
	}
	glutPostRedisplay(); // 화면 재 출력 
	if(pause == 0)
		glutTimerFunc(speed, Timer, 1); // 타이머함수 재 설정
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
		speed++;
		break;
	case 's':
		if (speed > 1)
			speed--;
		break;
	case 'd':
		if (what == 0)
			what = 1;
		else
			what = 0;
		break;
	case 'z':
		pause = 1;
		break;

	case 'x':
		pause = 0;
		glutTimerFunc(speed, Timer, 1);

	case '0':
		set_save[0] = 1;
		break;
	case '1':
		set_save[1] = 1;
		break;
	case '2':
		set_save[2] = 1;
		break;
	case '3':
		set_save[3] = 1;
		break;
	case '4':
		set_save[4] = 1;
		break;
	case '5':
		set_save[5] = 1;
		break;
	case '6':
		set_save[6] = 1;
		break;
	case '7':
		set_save[7] = 1;
		break;
	case '8':
		set_save[8] = 1;
		break;
	case '9':
		set_save[9] = 1;
		break;
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
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	for (int i = 0; i < 10; i++)
	{
		set_x[i] = 0;
		set_y[i] = 0;
		set_move[i] = 0;
		set_save[i] = 0;
		set_go[i] = 0;
	}
}

// 윈도우 출력 함수 
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 

	float as = times / 50;
	glColor4f(as, as, as, 1.0f);
	for (int i = 0; i < start; i++)
	{
		if (what == 0)
			glRectf(set_x[i], set_y[i], set_x[i] + times * 2, set_y[i] + times * 2); // 사각형 그리기
		else
		{
			GLint p1[2] = { set_x[i] + times, set_y[i] };
			GLint p2[2] = { set_x[i], set_y[i] + times * 2 };
			GLint p3[2] = { set_x[i] + times * 2, set_y[i] + times * 2 };
			glBegin(GL_TRIANGLES);
			glVertex2iv(p1);
			glVertex2iv(p2);
			glVertex2iv(p3); 
			glEnd();
		}
	}

	glFlush(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}