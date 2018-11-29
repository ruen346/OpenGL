#include <GL/freeglut.h>
#include <gl/glut.h> 
#include <time.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *glu_fill;
GLUquadricObj *glu_line;

struct Barrier
{
	int x = 0;
	int z = 0;
};

struct Coster
{
	float x = 0;
	float y = -30;//2d 이상해서 그럼 거꾸로생각 ㄱㄱ
	float z = 0;
	int active = 0;
};

struct Cart
{
	int x = 0;
	int y = 0;
	int z = 0;
	int go = 0;//50으로 나눠서 몇번째 점을 지나는지
};

Barrier barrier[10];

Coster coster[20];
Coster re_coster[20];//2d 3d 인지부조화 땜시 3d용
int coster_count = 0;//몇개의 점이 찍힌지

int mod = 2;//1:2d높이 2:2d탑뷰 3:3d
int mod1_right_coster = 20;//우클릭시 지금 선택한 코스터 눌림 디폴트:20
int mod2_right_coster = 20;//우클릭시 지금 선택한 코스터 눌림 디폴트:20

Cart cart[3];

int weather_mod = 0;//0맑음 1비 2눈

int x_ro = 0;
int y_ro = 0;
int z_zoom = 0;


void SetupRC()
{
	for (int i = 0; i < 10; i++)//장애물
	{
		barrier[i].x = rand() % 800 - 400;
		barrier[i].z = rand() % 800 - 400;
	}
	srand(time(NULL));
}

void Timer(int value)
{
	if (mod == 3)
	{
		for (int i = 0; i < 3; i++)
		{
			if (cart[i].go < coster_count * 50)
				cart[i].go++;
			else
				cart[i].go = 0;

			int p[4];

			//카트위치
			p[0] = cart[i].go / 50 - 1;
			p[1] = cart[i].go / 50;
			p[2] = cart[i].go / 50 + 1;
			p[3] = cart[i].go / 50 + 2;

			if (p[0] == -1)
				p[0] = coster_count - 1;
			if (p[2] >= coster_count)
				p[2] -= coster_count;
			if (p[3] >= coster_count)
				p[3] -= coster_count;

			float j = cart[i].go % 50;
			float t = j / 50.f;

			cart[i].x = ((-t * -t * -t + 2 * t * t - t)*re_coster[p[0]].x + (3 * t*t*t - 5 * t*t + 2)*re_coster[p[1]].x
				+ (-3 * t*t*t + 4 * t*t + t)*re_coster[p[2]].x + (t*t*t - t * t)*re_coster[p[3]].x) / 2;
			cart[i].y = ((-t * -t * -t + 2 * t * t - t)*re_coster[p[0]].y + (3 * t*t*t - 5 * t*t + 2)*re_coster[p[1]].y
				+ (-3 * t*t*t + 4 * t*t + t)*re_coster[p[2]].y + (t*t*t - t * t)*re_coster[p[3]].y) / 2;
			cart[i].z = ((-t * -t * -t + 2 * t * t - t)*re_coster[p[0]].z + (3 * t*t*t - 5 * t*t + 2)*re_coster[p[1]].z
				+ (-3 * t*t*t + 4 * t*t + t)*re_coster[p[2]].z + (t*t*t - t * t)*re_coster[p[3]].z) / 2;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		mod = 1;
		Reshape(1000, 1000);
		glutReshapeFunc(Reshape);
		break;

	case '2':
		mod = 2;
		Reshape(1000, 1000);
		glutReshapeFunc(Reshape);
		break;

	case '3':
		mod = 3;
		Reshape(1000,1000);
		glutReshapeFunc(Reshape);

		for (int i = 0; i < coster_count; i++)
		{
			re_coster[i].x = coster[i].x - 500;
			re_coster[i].y = -coster[i].y;
			re_coster[i].z = coster[i].z - 500;
			re_coster[i].active = coster[i].active;
		}
		
		for (int i = 0; i < 3; i++)
		{
			cart[i].x = re_coster[0].x;
			cart[i].y = re_coster[0].y;
			cart[i].z = re_coster[0].z;
		}
		cart[0].go = 10;
		cart[1].go = 5;
		cart[2].go = 0;
		break;


	case 'x':
		x_ro += 5;
		break;
	case 'X':
		x_ro -= 5;
		break;

	case 'y':
		y_ro += 5;
		break;
	case 'Y':
		y_ro -= 5;
		break;

	case 'z':
		z_zoom += 5;
		break;
	case 'Z':
		z_zoom -= 5;
		break;

	case 'i':
		weather_mod = 0;
		break;
	case 'o':
		weather_mod = 1;
		break;
	case 'p':
		weather_mod = 2;
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)//좌클릭
	{
		if (mod == 2)
		{
			coster[coster_count].x = x;
			coster[coster_count].z = y;
			coster[coster_count].active = 1;
			coster_count++;
		}
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)//우클릭
	{
		if (mod == 1)
		{
			for (int i = 0; i < coster_count; i++)
			{
				if (coster[i].x > x - 10 && coster[i].x < x + 10 && coster[i].y > y - 510 && coster[i].y < y -490)
					mod1_right_coster = i;
			}
		}

		else if (mod == 2)
		{
			for (int i = 0; i < coster_count; i++)
			{
				if (coster[i].x > x - 10 && coster[i].x < x + 10 && coster[i].z > y - 10 && coster[i].z < y + 10)
					mod2_right_coster = i;
			}
		}
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)//우클릭 떔
	{
		if (mod == 1)
			mod1_right_coster = 20;

		else if (mod == 2)
			mod2_right_coster = 20;
	}
}

void Motion(int x, int y)
{
	if (mod == 1)
	{
		if (mod1_right_coster != 20)
			coster[mod1_right_coster].y = y - 500;
	}

	else if (mod == 2)
	{
		if (mod2_right_coster != 20)
		{
			coster[mod2_right_coster].x = x;
			coster[mod2_right_coster].z = y;
		}
	}
}


void main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);

	glutCreateWindow("숙제2");

	SetupRC();

	glutDisplayFunc(drawScene);
	glutTimerFunc(0, Timer, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

void drawScene()
{
	if (mod == 3)
	{
		glEnable(GL_DEPTH_TEST);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glu_fill = gluNewQuadric();
		glu_line = gluNewQuadric();
		gluQuadricDrawStyle(glu_fill, GLU_FILL);
		gluQuadricDrawStyle(glu_line, GLU_LINE);

		glPushMatrix();
		{
			gluLookAt(
				0.0, 200.0, 500.0 - z_zoom, //EYE
				0.0, 0.0, 0.0, //AT
				0.0, 1.0, 0.0); //UP

			glRotated(x_ro, 1, 0, 0);
			glRotated(y_ro, 0, 1, 0);


			glPushMatrix();//바닥판
			{
				glScalef(1000, 1, 1000);
				glColor3ub(150, 150, 150);
				glutSolidCube(1);
			}
			glPopMatrix();

			switch (weather_mod)//날씨
			{
			case 0:
				break;

			case 1:
				break;

			case 2:
				break;
			}

			for (int i = 0; i < 3; i++)//카트
			{
				glPushMatrix();
				{
					glTranslatef(cart[i].x, cart[i].y + 15, cart[i].z);

					glColor3ub(255, 0, 0);
					glutSolidCube(30);
				}
				glPopMatrix();
			}

			for (int i = 0; i < 10; i++)//장애물
			{
				glPushMatrix();
				{
					glTranslatef(barrier[i].x, 0, barrier[i].z);

					glPushMatrix();//나무기둥
					{
						glTranslatef(0, 30, 0);

						glColor3ub(155, 90, 61);
						glScalef(1, 3, 1);
						glutSolidCube(20);
					}
					glPopMatrix();

					glPushMatrix();//나뭇잎
					{
						glTranslatef(0, 85, 0);

						glColor3ub(0, 208, 85);
						glutSolidCube(50);
					}
					glPopMatrix();
				}
				glPopMatrix();
			}

			for (int i = 0; i < 20; i++)//롤러코스터
			{
				if (re_coster[i].active == 1)
				{
					glPushMatrix();//기둥표시
					{
						glColor3ub(80, 80, 80);
						glTranslatef(re_coster[i].x, re_coster[i].y / 2.0f, re_coster[i].z);
						glScalef(1, re_coster[i].y / 10.0f, 1);
						glutSolidCube(10);
					}
					glPopMatrix();

					glPushMatrix();//선표시
					{
						int p[4];

						p[0] = i - 1;
						p[1] = i;
						p[2] = i + 1;
						p[3] = i + 2;

						if (p[0] == -1)
							p[0] = coster_count - 1;
						if (p[2] >= coster_count)
							p[2] -= coster_count;
						if (p[3] >= coster_count)
							p[3] -= coster_count;

						for (int j = 0; j < 50; j++)
						{
							float x1, x2, y1, y2, z1, z2, t = j / 50.f;

							x1 = ((-t * -t * -t + 2 * t * t - t)*re_coster[p[0]].x + (3 * t*t*t - 5 * t*t + 2)*re_coster[p[1]].x
								+ (-3 * t*t*t + 4 * t*t + t)*re_coster[p[2]].x + (t*t*t - t * t)*re_coster[p[3]].x) / 2;
							y1 = ((-t * -t * -t + 2 * t * t - t)*re_coster[p[0]].y + (3 * t*t*t - 5 * t*t + 2)*re_coster[p[1]].y
								+ (-3 * t*t*t + 4 * t*t + t)*re_coster[p[2]].y + (t*t*t - t * t)*re_coster[p[3]].y) / 2;
							z1 = ((-t * -t * -t + 2 * t * t - t)*re_coster[p[0]].z + (3 * t*t*t - 5 * t*t + 2)*re_coster[p[1]].z
								+ (-3 * t*t*t + 4 * t*t + t)*re_coster[p[2]].z + (t*t*t - t * t)*re_coster[p[3]].z) / 2;

							t = (j + 1) / 50.f;
							x2 = ((-t * -t * -t + 2 * t * t - t)*re_coster[p[0]].x + (3 * t*t*t - 5 * t*t + 2)*re_coster[p[1]].x
								+ (-3 * t*t*t + 4 * t*t + t)*re_coster[p[2]].x + (t*t*t - t * t)*re_coster[p[3]].x) / 2;
							y2 = ((-t * -t * -t + 2 * t * t - t)*re_coster[p[0]].y + (3 * t*t*t - 5 * t*t + 2)*re_coster[p[1]].y
								+ (-3 * t*t*t + 4 * t*t + t)*re_coster[p[2]].y + (t*t*t - t * t)*re_coster[p[3]].y) / 2;
							z2 = ((-t * -t * -t + 2 * t * t - t)*re_coster[p[0]].z + (3 * t*t*t - 5 * t*t + 2)*re_coster[p[1]].z
								+ (-3 * t*t*t + 4 * t*t + t)*re_coster[p[2]].z + (t*t*t - t * t)*re_coster[p[3]].z) / 2;

							glColor3ub(50, 50, 50);

							glBegin(GL_LINES);
							glVertex3f(x1, y1, z1);
							glVertex3f(x2, y2, z2);
							glEnd();
						}
					}
					glPopMatrix();
				}
			}
		}
		glPopMatrix();

		glutSwapBuffers();
	}

	else if (mod == 1)
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glClearColor(1, 1, 1, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);


		glPushMatrix();
		{
			glTranslatef(0, 0, 0);//화면 쪼끔 내리기(지하가 있는건 아니니까)

			for (int i = 0; i < 10; i++)//장애물
			{
				glPushMatrix();
				{
					glTranslatef(barrier[i].x, 0, 0);

					glColor3ub(155, 90, 61);
					glBegin(GL_QUADS);
					glVertex3f(-20, -20, 0);
					glVertex3f(20, -20, 0);
					glVertex3f(20, 20, 0);
					glVertex3f(-20, 20, 0);
					glEnd();
				}
				glPopMatrix();
			}

			for (int i = 0; i < 20; i++)//롤러코스터
			{
				if (coster[i].active == 1)
				{
					glPushMatrix();//위치표시
					{
						glTranslatef(-500, 0, 0);

						glColor3ub(255, 187, 231);
						glBegin(GL_QUADS);
						glVertex3f(coster[i].x - 10, coster[i].y - 10, 0);
						glVertex3f(coster[i].x + 10, coster[i].y - 10, 0);
						glVertex3f(coster[i].x + 10, coster[i].y + 10, 0);
						glVertex3f(coster[i].x - 10, coster[i].y + 10, 0);
						glEnd();
					}
					glPopMatrix();

					glPushMatrix();//선표시
					{

						glTranslatef(-500, 0, 0);
						int p[4];

						p[0] = i - 1;
						p[1] = i;
						p[2] = i + 1;
						p[3] = i + 2;

						if (p[0] == -1)
							p[0] = coster_count - 1;
						if (p[2] >= coster_count)
							p[2] -= coster_count;
						if (p[3] >= coster_count)
							p[3] -= coster_count;

						for (int j = 0; j < 49; j++)
						{
							float x1, x2, y1, y2, t = j / 50.f;

							x1 = ((-t * -t * -t + 2 * t * t - t)*coster[p[0]].x + (3 * t*t*t - 5 * t*t + 2)*coster[p[1]].x + (-3 * t*t*t + 4 * t*t + t)*coster[p[2]].x + (t*t*t - t * t)*coster[p[3]].x) / 2;
							y1 = ((-t * -t * -t + 2 * t * t - t)*coster[p[0]].y + (3 * t*t*t - 5 * t*t + 2)*coster[p[1]].y + (-3 * t*t*t + 4 * t*t + t)*coster[p[2]].y + (t*t*t - t * t)*coster[p[3]].y) / 2;

							t = (j + 1) / 50.f;
							x2 = ((-t * -t * -t + 2 * t * t - t)*coster[p[0]].x + (3 * t*t*t - 5 * t*t + 2)*coster[p[1]].x + (-3 * t*t*t + 4 * t*t + t)*coster[p[2]].x + (t*t*t - t * t)*coster[p[3]].x) / 2;
							y2 = ((-t * -t * -t + 2 * t * t - t)*coster[p[0]].y + (3 * t*t*t - 5 * t*t + 2)*coster[p[1]].y + (-3 * t*t*t + 4 * t*t + t)*coster[p[2]].y + (t*t*t - t * t)*coster[p[3]].y) / 2;

							glBegin(GL_LINES);
							glVertex3f(x1, y1, 0);
							glVertex3f(x2, y2, 0);
							glEnd();
						}

					}
					glPopMatrix();
				}
			}
		}
		glPopMatrix();

		glutSwapBuffers();
	}

	else if (mod == 2)
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glClearColor(1, 1, 1, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);


		glPushMatrix();
		{
			for (int i = 0; i < 10; i++)//장애물
			{
				glPushMatrix();
				{
					glTranslatef(barrier[i].x, barrier[i].z, 0);

					glColor3ub(155, 90, 61);
					glBegin(GL_QUADS);
					glVertex3f(-20, -20, 0);
					glVertex3f(20, -20, 0);
					glVertex3f(20, 20, 0);
					glVertex3f(-20, 20, 0);
					glEnd();
				}
				glPopMatrix();
			}

			for (int i = 0; i < 20; i++)//롤러코스터
			{
				if (coster[i].active == 1)
				{
					glPushMatrix();//위치표시
					{
						glColor3ub(255, 187, 231);
						glBegin(GL_QUADS);
						glVertex3f(coster[i].x - 510, coster[i].z - 510, 0);
						glVertex3f(coster[i].x - 490, coster[i].z - 510, 0);
						glVertex3f(coster[i].x - 490, coster[i].z - 490, 0);
						glVertex3f(coster[i].x - 510, coster[i].z - 490, 0);
						glEnd();
					}
					glPopMatrix();

					glPushMatrix();//선표시
					{
						glTranslatef(-500, -500, 0);

						if (coster_count == 2 && i == 0)
						{
							glLineWidth(3);
							glColor3ub(255, 191, 248);
							glBegin(GL_LINES);
							glVertex3f(coster[i].x, coster[i].z, 0);
							glVertex3f(coster[i + 1].x, coster[i + 1].z, 0);
							glEnd();
						}
						else if (coster_count >= 3)
						{
							int p[4];

							p[0] = i - 1;
							p[1] = i;
							p[2] = i + 1;
							p[3] = i + 2;

							if (p[0] == -1)
								p[0] = coster_count - 1;
							if (p[2] >= coster_count)
								p[2] -= coster_count;
							if (p[3] >= coster_count)
								p[3] -= coster_count;

							for (int j = 0; j < 49; j++)
							{
								float x1, x2, y1, y2, t = j / 50.f;

								x1 = ((-t * -t * -t + 2 * t * t - t)*coster[p[0]].x + (3 * t*t*t - 5 * t*t + 2)*coster[p[1]].x + (-3 * t*t*t + 4 * t*t + t)*coster[p[2]].x + (t*t*t - t * t)*coster[p[3]].x) / 2;
								y1 = ((-t * -t * -t + 2 * t * t - t)*coster[p[0]].z + (3 * t*t*t - 5 * t*t + 2)*coster[p[1]].z + (-3 * t*t*t + 4 * t*t + t)*coster[p[2]].z + (t*t*t - t * t)*coster[p[3]].z) / 2;

								t = (j + 1) / 50.f;
								x2 = ((-t * -t * -t + 2 * t * t - t)*coster[p[0]].x + (3 * t*t*t - 5 * t*t + 2)*coster[p[1]].x + (-3 * t*t*t + 4 * t*t + t)*coster[p[2]].x + (t*t*t - t * t)*coster[p[3]].x) / 2;
								y2 = ((-t * -t * -t + 2 * t * t - t)*coster[p[0]].z + (3 * t*t*t - 5 * t*t + 2)*coster[p[1]].z + (-3 * t*t*t + 4 * t*t + t)*coster[p[2]].z + (t*t*t - t * t)*coster[p[3]].z) / 2;

								glBegin(GL_LINES);
								glVertex3f(x1, y1, 0);
								glVertex3f(x2, y2, 0);
								glEnd();
							}
						}
					}
					glPopMatrix();
					
				}
			}
		}
		glPopMatrix();

		glutSwapBuffers();
	}
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (mod == 3)
	{
		gluPerspective(60.0, 1.0, 1.0, 10000.0);
		glTranslatef(0, 0, -500);
	}
	else
		glOrtho(-500, 500, 500, -500, -500, 500);

	glMatrixMode(GL_MODELVIEW);
}