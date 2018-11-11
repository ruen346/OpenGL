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
	float y = 0;
	float z = 0;
	int active = 0;
};

Barrier barrier[10];

Coster coster[20];
int coster_count = 0;//몇개의 점이 찍힌지

int mod = 2;//2:2d 3:3d


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
	

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (mod == 2)
		{
			coster[coster_count].x = x;
			coster[coster_count].z = y;
			coster[coster_count].active = 1;
			coster_count++;
		}
	}
}

void Motion(int x, int y)
{

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
		glShadeModel(GL_FLAT);
		glEnable(GL_CULL_FACE);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glu_fill = gluNewQuadric();
		glu_line = gluNewQuadric();
		gluQuadricDrawStyle(glu_fill, GLU_FILL);
		gluQuadricDrawStyle(glu_line, GLU_LINE);

		glPushMatrix();
		{
			gluLookAt(
				0.0, 0.0, 300.0, //EYE
				0.0, 0.0, -1.0, //AT
				0.0, 1.0, 0.0); //UP
		}
		glPopMatrix();

		glutSwapBuffers();
	}

	else if (mod == 2)
	{
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
		gluPerspective(60.0, 1.0, 1.0, 10000.0);
	else
		glOrtho(-500, 500, 500, -500, -500, 500);

	glMatrixMode(GL_MODELVIEW);
}