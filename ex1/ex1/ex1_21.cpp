#include <GL/freeglut.h>
#include <gl/glut.h> 
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *glu_fill;
GLUquadricObj *glu_line;

int y_ro = 0;

int tree_big = 30;
int tree_sw = 0;

int bong_ro = 0;

int hand_up = 0;
int hand_sw = 0;

int run_ro = 0;

void SetupRC()
{


	srand(time(NULL));
}

void Timer(int value)
{
	if (tree_sw == 0 && tree_big < 80)
		tree_big++;
	else if (tree_big == 80)
		tree_sw = 1;

	if (tree_sw == 1 && tree_big > 45)
		tree_big--;
	else if (tree_big == 45)
		tree_sw = 0;

	if (bong_ro < 360)
		bong_ro += 5;
	else
		bong_ro = 0;

	if (hand_sw == 0 && hand_up < 30)
		hand_up++;
	else if (hand_up == 30)
		hand_sw = 1;

	if (hand_sw == 1 && hand_up > 0)
		hand_up--;
	else if (hand_up == 0)
		hand_sw = 0;

	if (run_ro < 360)
		run_ro += 5;
	else
		run_ro = 0;


	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '[':
		y_ro += 5;
		break;

	case ']':
		y_ro -= 5;
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
}

void Motion(int x, int y)
{

}


void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Points Drawing");

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
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glu_fill = gluNewQuadric();
	glu_line = gluNewQuadric();
	gluQuadricDrawStyle(glu_fill, GLU_FILL);
	gluQuadricDrawStyle(glu_line, GLU_LINE);

	glPushMatrix();
	{
		gluLookAt(
			0.0, 20.0, 30.0, //EYE
			0.0, 0.0, 0.0, //AT
			0.0, 1.0, 0.0); //UP

		glTranslatef(0, -100, 0);
		glRotatef(y_ro, 0, 1, 0);

		glPushMatrix();//��
		{
			glColor3ub(255, 100, 100);
			glBegin(GL_POLYGON);
			glVertex3f(-300, 0, -300);
			glVertex3f(0, 0, -300);
			glVertex3f(-300, 0, 0);
			glEnd();

			glColor3ub(100, 255, 100);
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, -300);
			glVertex3f(300, 0, -300);
			glVertex3f(300, 0, 0);
			glEnd();

			glColor3ub(100, 100, 255);
			glBegin(GL_POLYGON);
			glVertex3f(-300, 0, 0);
			glVertex3f(-300, 0, 300);
			glVertex3f(0, 0, 300);
			glEnd();

			glColor3ub(100, 100, 100);
			glBegin(GL_POLYGON);
			glVertex3f(300, 0, 0);
			glVertex3f(300, 0, 300);
			glVertex3f(0, 0, 300);
			glEnd();

			glColor3ub(255, 255, 255);
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, -300);
			glVertex3f(-300, 0, 0);
			glVertex3f(0, 0, 300);
			glVertex3f(300, 0, 0);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();//����
		{
			glTranslatef(200, 0, 200);

			glPushMatrix();//���
			{
				glTranslatef(0, 75, 0);
				glColor3ub(120, 55, 18);
				glScalef(1, 3, 1);
				glutSolidCube(50);
			}
			glPopMatrix();

			glPushMatrix();//��
			{
				glTranslatef(0, 150, 0);
				glColor3ub(34, 116, 28);
				gluSphere(glu_fill, tree_big, 30, 30);
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//ö��
		{
			glTranslatef(200, 0, -200);

			glPushMatrix();//��
			{
				glPushMatrix();
				{
					glTranslatef(-50, 50, 0);
					glColor3ub(0, 0, 255);
					glScalef(1, 10, 1);
					glutSolidCube(10);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(50, 50, 0);
					glColor3ub(0, 0, 255);
					glScalef(1, 10, 1);
					glutSolidCube(10);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, 100, 0);
					glColor3ub(0, 0, 255);
					glScalef(10, 1, 1);
					glutSolidCube(10);
				}
				glPopMatrix();
			}
			glPopMatrix();

			glPushMatrix();//���
			{
				glTranslatef(0, 100, 0);
				glRotatef(bong_ro, 1, 0, 0);

				glPushMatrix();
				{
					glTranslatef(-15, -15, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 5, 1);
					glutSolidCube(6);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(15, -15, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 5, 1);
					glutSolidCube(6);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, -45, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 1, 0.5);
					glutSolidCube(30);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, -20, 0);
					glColor3ub(0, 0, 200);
					gluSphere(glu_fill, 10, 10, 10);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//���׸ӽ�
		{
			glTranslatef(-200, 0, 200);

			glPushMatrix();//���
			{
				glTranslatef(0, 0, -30);

				glPushMatrix();
				{
					glTranslatef(-25, 30, 0);
					glColor3ub(255, 255, 0);
					glScalef(1, 12, 1);
					glutSolidCube(5);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(25, 30, 0);
					glColor3ub(255, 255, 0);
					glScalef(1, 12, 1);
					glutSolidCube(5);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, 60, 0);
					glColor3ub(255, 255, 0);
					glScalef(10, 1, 1);
					glutSolidCube(5);
				}
				glPopMatrix();

				glPushMatrix();//���ͷ�
				{
					glTranslatef(0, 10, 40);
					glRotatef(90, 0, 1, 0);
					glRotatef(run_ro, 0, 0, 1);
					//glScalef(2, 0.5, 2);
					glColor3ub(255, 0, 0);
					glutWireTorus(20, 20, 30, 15);
				}
				glPopMatrix();
			}
			glPopMatrix();

			glPushMatrix();//���
			{
				glTranslatef(0, 100, 0);

				glPushMatrix();
				{
					glTranslatef(-15, -30, -15);
					glColor3ub(0, 0, 200);
					glScalef(1, 1, 5);
					glutSolidCube(6);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(15, -30, -15);
					glColor3ub(0, 0, 200);
					glScalef(1, 1, 5);
					glutSolidCube(6);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, -45, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 1, 0.5);
					glutSolidCube(30);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, -20, 0);
					glColor3ub(0, 0, 200);
					gluSphere(glu_fill, 10, 10, 10);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//��ġ ������
		{
			glTranslatef(-200, 0, -200);

			glPushMatrix();//����
			{
				glPushMatrix();
				{
					glTranslatef(-40, 25, 0);
					glColor3ub(20, 20, 20);
					glScalef(1, 5, 1);
					glutSolidCube(10);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(40, 25, 0);
					glColor3ub(20, 20, 20);
					glScalef(1, 5, 1);
					glutSolidCube(10);
				}
				glPopMatrix();

				glPushMatrix();//������
				{
					glTranslatef(0, hand_up, 0);

					glPushMatrix();
					{
						glTranslatef(0, 50, 0);
						glColor3ub(100, 100, 100);
						glScalef(10, 0.5, 0.5);
						glutSolidCube(10);
					}
					glPopMatrix();

					glPushMatrix();
					{
						glTranslatef(-55, 50, 0);
						glRotatef(90, 0, 1, 0);
						glScalef(1, 1, 0.5);
						glColor3ub(255, 0, 0);
						glutSolidTorus(15, 15, 10, 10);
					}
					glPopMatrix();

					glPushMatrix();
					{
						glTranslatef(55, 50, 0);
						glRotatef(90, 0, 1, 0);
						glScalef(1, 1, 0.5);
						glColor3ub(255, 0, 0);
						glutSolidTorus(15, 15, 10, 10);
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();

			glPushMatrix();//�ΰ�
			{
				glPushMatrix();
				{
					glTranslatef(0, 10, -10);
					glColor3ub(0, 0, 200);
					gluSphere(glu_fill, 10, 10, 10);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, 7.5, 15);
					glColor3ub(0, 0, 200);
					glScalef(1, 0.5, 1);
					glutSolidCube(30);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(-15, 25, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 5 + (hand_up / 5), 1);
					glutSolidCube(10);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(15, 25, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 5 + (hand_up / 5), 1);
					glutSolidCube(10);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -500.0);

	glMatrixMode(GL_MODELVIEW);
}