#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

struct Ob
{
	float x = -100;
	float y = 20 + 25;
	int ro = 0;
	int active = 1;
};

struct Block
{
	int active[2];
};

class Any
{
public:
	float cut_x[2];
	float cut_y[2];
	int cut_active = 0;

	int shack = 0;
	int move = 0;//1왼쪽잡음 2오른쪽잡음

	int semo_you = 0;//1왼쪽에서 짜름 2오른쪽에서 짜름
	
	int star_count = 0;//몇번째 별
	int star_color[3];

	int move_x[2];
	int move_y[2];
	int move_count[2];
};

Ob up_tr[10];
Ob nemo;
Ob semo[2];
Ob star[100];
Any any;
Block block[3][16];

void Timer(int value)
{
	for (int i = 0; i < 10; i++)
	{
		up_tr[i].x += 1;
		if (up_tr[i].x > 825)
		{
			up_tr[i].x = -25;
			up_tr[i].active = 1;
		}

		if (up_tr[i].ro < 357)
			up_tr[i].ro += 2;
		else
			up_tr[i].ro = 0;
	}

	if (nemo.active == 1 && nemo.y < -50)
		nemo.y = 600;
	else
		nemo.y -= 3;

	if (semo[0].active == 1 && any.move != 1)
	{
		semo[0].x -= 5;
		semo[0].y += 5;
	}
	if (semo[1].active == 1 && any.move != 2)
	{
		semo[1].x += 5;
		semo[1].y += 5;
	}

	if (any.shack > 0)
		any.shack--;

	if (semo[0].y > 600 && semo[1].y > 600 && nemo.active == 0)
	{
		nemo.active = 1;
		nemo.y = 600;
	}

	for (int i = 0; i < 3; i++)
	{
		if (any.star_color[i] >= 255)
			any.star_color[i] = 0;
		else
			any.star_color[i] += 5;
	}

	for (int i = 0; i < 100; i++)
	{
		if (star[i].active == 1)
		{
			if (star[i].ro < 360)
				star[i].ro += 5;
			else
				star[i].ro = 0;
			
		}
	}


	glutPostRedisplay(); // 화면 재 출력 
	glutTimerFunc(20, Timer, 1); // 타이머함수 재 설정
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (nemo.active == 1)
		{
			any.cut_active = 1;
			if (any.cut_active == 1)
			{
				any.cut_x[0] = x;
				any.cut_y[0] = y;
				any.cut_x[1] = x;
				any.cut_y[1] = y;
			}
		}

		if (semo[0].active == 1 && semo[0].x - 25 < x && semo[0].x + 25 > x && semo[0].y - 25 < y && semo[0].y + 25 > y)
		{
			any.move = 1;
			semo[0].x = x;
			semo[0].y = y;
		}
		if (semo[1].active == 1 && semo[1].x - 25 < x && semo[1].x + 25 > x && semo[1].y - 25 < y && semo[1].y + 25 > y)
		{
			any.move = 2;
			semo[1].x = x;
			semo[1].y = y;
		}
	}
	else if ((button == GLUT_LEFT_BUTTON && state == GLUT_UP))
	{
		if (any.cut_active == 1)
		{
			float left_x, right_x, left_y, right_y;
			if (any.cut_x[0] < any.cut_x[1])
			{
				left_x = any.cut_x[0];
				right_x = any.cut_x[1];
			}
			else
			{
				left_x = any.cut_x[1];
				right_x = any.cut_x[0];
			}
			if (any.cut_y[0] < any.cut_y[1])
			{
				left_y = any.cut_y[0];
				right_y = any.cut_y[1];
			}
			else
			{
				left_y = any.cut_y[1];
				right_y = any.cut_y[0];
			}

			if (left_x < nemo.x && right_x > nemo.x + 50 && left_y < nemo.y && right_y > nemo.y + 50)
			{
				int a = abs((left_x - right_x) / (left_y - right_y));
				cout << abs((left_x - nemo.x) / (left_y - nemo.y)) - a << " " << abs((right_x - nemo.x + 50) / (right_y - nemo.y + 50)) - a << endl;
				if (abs((left_x - nemo.x) / (left_y - nemo.y)) - a < 0.5 && abs((right_x - nemo.x + 50) / (right_y - nemo.y + 50)) - a < 0.5)
				{//왼쪽 위 자름
					nemo.active = 0;
					semo[0].active = 1;
					semo[1].active = 1;
					semo[0].x = nemo.x;
					semo[1].x = nemo.x;
					semo[0].y = nemo.y;
					semo[1].y = nemo.y;

					any.shack = 20;
					any.semo_you = 1;
				}
				else if (abs((left_x - nemo.x + 50) / (left_y - nemo.y)) - a < 0.5 && abs((right_x - nemo.x) / (right_y - nemo.y + 50)) - a < 0.5)
				{//오른쪽 위 자름
					nemo.active = 0;
					semo[0].active = 1;
					semo[1].active = 1;
					semo[0].x = nemo.x;
					semo[1].x = nemo.x;
					semo[0].y = nemo.y;
					semo[1].y = nemo.y;

					any.shack = 20;
					any.semo_you = 2;
				}
			}
			any.cut_active = 0;
		}
		if (any.move == 1 || any.move == 2)//나뉜 삼각형 놓을때
		{
			if (any.move == 1)//왼쪽거
			{
				for (int i = 0; i < 10; i++)
				{
					if (up_tr[i].active == 1 && x > up_tr[i].x - 25 && x < up_tr[i].x + 25 && y > up_tr[i].y - 25 && y < up_tr[i].y + 25)
					{
						up_tr[i].active = 0;
						semo[0].active = 0;
						semo[0].y = 800;
						star[any.star_count].active = 1;
						star[any.star_count].x = rand() % 700 + 50;
						star[any.star_count].y = rand() % 300 + 150;
						any.star_count++;
						i = 10;
					}	
				}
			}
			if (any.move == 2)//오른쪽거
			{
				for (int i = 0; i < 10; i++)
				{
					if (up_tr[i].active == 1 && x > up_tr[i].x - 25 && x < up_tr[i].x + 25 && y > up_tr[i].y - 25 && y < up_tr[i].y + 25)
					{
						up_tr[i].active = 0;
						semo[1].active = 0;
						semo[1].y = 800;
						star[any.star_count].active = 1;
						star[any.star_count].x = rand() % 700 + 50;
						star[any.star_count].y = rand() % 300 + 150;
						any.star_count++;
						i = 10;
					}
				}
			}
			any.move = 0;
		}
	}
}

void Motion(int x, int y)
{
	if (any.cut_active == 1)
	{
		any.cut_x[1] = x;
		any.cut_y[1] = y;
	}

	if (any.move == 1)
	{
		semo[0].x = x;
		semo[0].y = y;
	}
	if (any.move == 2)
	{
		semo[1].x = x;
		semo[1].y = y;
	}
}

void main(int argc, char *argv[])
{
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		up_tr[i].x = i * 85;
		up_tr[i].ro = i * 36;
	}
	nemo.x = 400;
	nemo.y = 600;
	semo[0].active = 0;
	semo[1].active = 0;
	for (int i = 0; i < 100; i++)
		star[i].active = 0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 

	glutCreateWindow("homework1"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정 
	glutTimerFunc(0, Timer, 1);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// 윈도우 출력 함수 
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 

	glPushMatrix();
	{
		if (any.shack != 0)
		{
			if(any.shack > 10)
				glTranslatef((any.shack - 20) * 2, (any.shack - 20) * 2, 0.0);
			else
				glTranslatef((any.shack) * -2, (any.shack) * -2, 0.0);
		}

		glColor3ub(255, 255, 255);
		glBegin(GL_LINES);
		glVertex2f(0, 90);
		glVertex2f(800, 90);
		for (int i = 0; i <= 800; i += 50)
		{
			glVertex2f(i, 450);
			glVertex2f(i, 600);
		}
		for (int i = 450; i <= 600; i += 50)
		{
			glVertex2f(0, i);
			glVertex2f(800, i);
		}
		glEnd();

		for (int i = 0; i < 100; i++)//별그리기
		{
			glPushMatrix();
			{
				if (star[i].active == 1)
				{
					glTranslatef(star[i].x,star[i].y,0);
					glRotatef(star[i].ro, 0, 0, 1);

					glShadeModel(GL_SMOOTH);

					glBegin(GL_POLYGON);
					glColor3ub(any.star_color[0], any.star_color[1], 255);
					glVertex2f(0, - 25);
					glColor3ub(any.star_color[1], 255, any.star_color[2]);
					glVertex2f(- 25, 25);
					glColor3ub(255, any.star_color[2], any.star_color[0]);
					glVertex2f(25, 25);
					glEnd();
					glBegin(GL_POLYGON);
					glColor3ub(any.star_color[0], any.star_color[1], 255);
					glVertex2f(25, 10);
					glColor3ub(any.star_color[1], 255, any.star_color[2]);
					glVertex2f(0, 40);
					glColor3ub(255, any.star_color[2], any.star_color[0]);
					glVertex2f(- 25, - 10);
					glEnd();

					glShadeModel(GL_FLAT);
				}
			}
			glPopMatrix();
		}

		glColor3ub(255, 255, 255);
		for (int i = 0; i < 10; i++)
		{
			if (up_tr[i].active == 1)
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
		}

		glPushMatrix();
		{
			if (nemo.active == 1)
			{
				glTranslatef(nemo.x, nemo.y, 0.0);
				glBegin(GL_POLYGON);
				glVertex2f(-25, -25);
				glVertex2f(-25, +25);
				glVertex2f(+25, +25);
				glVertex2f(+25, -25);
				glEnd();
			}
		}
		glPopMatrix();

		if (nemo.active == 0)//새세모그리기!!
		{
			if (any.semo_you == 1)//왼쪽 위 자름
			{
				glPushMatrix();
				{
					glTranslatef(semo[0].x, semo[0].y, 0.0);
					glBegin(GL_POLYGON);
					glVertex2f(-25, -25);
					glVertex2f(25, 25);
					glVertex2f(-25, 25);
					glEnd();
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(semo[1].x, semo[1].y, 0.0);
					glBegin(GL_POLYGON);
					glVertex2f(25, -25);
					glVertex2f(-25, -25);
					glVertex2f(25, 25);
					glEnd();
				}
				glPopMatrix();
			}
			else if (any.semo_you == 2)//오른쪽 위 자름
			{
				glPushMatrix();
				{
					glTranslatef(semo[0].x, semo[0].y, 0.0);
					glBegin(GL_POLYGON);
					glVertex2f(-25, -25);
					glVertex2f(25, -25);
					glVertex2f(-25, 25);
					glEnd();
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(semo[1].x, semo[1].y, 0.0);
					glBegin(GL_POLYGON);
					glVertex2f(25, -25);
					glVertex2f(-25, 25);
					glVertex2f(25, 25);
					glEnd();
				}
				glPopMatrix();
			}
		}

		if (any.cut_active == 1)
		{
			glColor3ub(255, 255, 0);
			glBegin(GL_LINES);
			glVertex2f(any.cut_x[0], any.cut_y[0]);
			glVertex2f(any.cut_x[1], any.cut_y[1]);
			glEnd();
		}

	}glPopMatrix();

	glFlush(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1.0, 1.0);
}