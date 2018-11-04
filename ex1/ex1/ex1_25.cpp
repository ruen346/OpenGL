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

int option1 = 0;//Àº¸é off/on
int option2 = 0;//ÄÃ¸µ off/on
int option3 = 0;//½¦ÀÌµù flat/smooth

int open1 = 0;//1ÀÌ¸é À§¶Ñ²±¿°
int open2 = 0;//1ÀÌ¸é ¾Õ¶Ñ²±¿°
int open1_ro = 0;
int open2_ro = 0;
float open1_up = 1;
float open2_up = 0;

void SetupRC()
{

	srand(time(NULL));
}

void Timer(int value)
{
	if (open1 == 1 && open1_ro < 90)
		open1_ro+=2;
	else if (open1 == 1 && open1_ro == 90 && open1_up < 6)
		open1_up += 0.25;

	if (open1 == 0 && open1_ro == 90 && open1_up > 1)
		open1_up -= 0.25;
	else if (open1 == 0 && open1_ro > 0)
		open1_ro-=2;


	if (open2 == 1 && open2_ro < 90)
		open2_ro += 2;
	else if (open2 == 1 && open2_ro == 90 && open2_up < 6)
		open2_up += 0.25;

	if (open2 == 0 && open2_ro == 90 && open2_up > 0)
		open2_up -= 0.25;
	else if (open2 == 0 && open2_ro > 0)
		open2_ro -= 2;
	
		

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

	case '1':
		if (option1 == 0)
			option1 = 1;
		else
			option1 = 0;
		break;

	case '2':
		if (option2 == 0)
			option2 = 1;
		else
			option2 = 0;
		break;

	case '3':
		if (option3 == 0)
			option3 = 1;
		else
			option3 = 0;
		break;

	case 'q':
		if (open1 == 0)
			open1 = 1;
		else
			open1 = 0;
		break;

	case 'w':
		if (open2 == 0)
			open2 = 1;
		else
			open2 = 0;
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
	if (option1 == 1)
		glEnable(GL_DEPTH_TEST);
	else if (option1 == 0)
		glDisable(GL_DEPTH_TEST);

	if (option2 == 1)
		glEnable(GL_CULL_FACE);
	else if (option2 == 0)
		glDisable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glu_fill = gluNewQuadric();
	glu_line = gluNewQuadric();
	gluQuadricDrawStyle(glu_fill, GLU_FILL);
	gluQuadricDrawStyle(glu_line, GLU_LINE);

	glPushMatrix();
	{
		gluLookAt(
			0.0, 0.0, 0.0, //EYE
			0.0, 0.0, -1.0, //AT
			0.0, 1.0, 0.0); //UP

		glTranslatef(0, -100, 0);
		glRotatef(y_ro, 0, 1, 0);

		/*
		glPushMatrix();//ÆÇ
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
		*/
			
		glPushMatrix();
		{
			glTranslatef(0, 50, 0);
			glRotatef(30, 1, 0, 0);
			glRotatef(45, 0, 1, 0);

			if (option3 == 0)
				glShadeModel(GL_FLAT);
			else if (option3 == 1)
				glShadeModel(GL_SMOOTH);

			glPushMatrix();
			{
				glTranslatef(0, 100, -50);
				glRotatef(-open1_ro, 1, 0, 0);
				
				glBegin(GL_QUADS);
				glColor3ub(0, 255, 255);//À§
				glVertex3f(-50, 0, 0);
				glColor3ub(255, 0, 255);
				glVertex3f(-50, 0, 100);
				glColor3ub(255, 255, 255);
				glVertex3f(50, 0, 100);
				glColor3ub(255, 255, 0);
				glVertex3f(50, 0, 0);
				glEnd();
			}
			glPopMatrix();

			glBegin(GL_QUADS);
			
			glColor3ub(0, 0, 0);//¾Æ·¡
			glVertex3f(50, 0, -50);
			glColor3ub(0, 0, 255);
			glVertex3f(50, 0, 50);
			glColor3ub(0, 255, 0);
			glVertex3f(-50, 0, 50);
			glColor3ub(255, 0, 0);
			glVertex3f(-50, 0, -50);

			glColor3ub(0, 255, 255);//¿ÞÂÊ
			glVertex3f(-50, 100, -50);
			glColor3ub(255, 0, 0);
			glVertex3f(-50, 0, -50);
			glColor3ub(0, 255, 0);
			glVertex3f(-50, 0, 50);
			glColor3ub(255, 0, 255);
			glVertex3f(-50, 100, 50);
			
			glColor3ub(255, 255, 255);//¿À¸¥ÂÊ
			glVertex3f(50, 100, 50);
			glColor3ub(0, 0, 255);
			glVertex3f(50, 0, 50);
			glColor3ub(0, 0, 0);
			glVertex3f(50, 0, -50);
			glColor3ub(255, 255, 0);
			glVertex3f(50, 100, -50);

			glColor3ub(255, 0, 0);//µÚ
			glVertex3f(50, 100, -50);
			glColor3ub(0, 0, 0);
			glVertex3f(50, 0, -50);
			glVertex3f(-50, 0, -50);
			glColor3ub(255, 255, 0);
			glColor3ub(0, 255, 255);
			glVertex3f(-50, 100, -50);

			glEnd();

			glPushMatrix();
			{
				glTranslatef(0, 100, 50);
				glRotatef(-open2_ro, 1, 0, 0);

				glBegin(GL_QUADS);

				glColor3ub(255, 0, 255);//¾Õ
				glVertex3f(-50, 0, 0);
				glColor3ub(0, 255, 0);
				glVertex3f(-50, -100, 0);
				glColor3ub(0, 0, 255);
				glVertex3f(50, -100, 0);
				glColor3ub(255, 255, 255);
				glVertex3f(50, 0, 0);
				glEnd();
			}
			glPopMatrix();
			

			glColor3ub(255, 255, 255);
			float rad = 45;
			glBegin(GL_LINES);
			for (float i = 0; i < 359; i++)
			{
				float angle = i * 6.28 / 30;	
				glVertex3f(rad*cos(angle), i / 8 * open1_up, rad*sin(angle));
				angle = (i + 1) * 6.28 / 30;
				glVertex3f(rad*cos(angle), (i + 1) / 8 * open1_up, rad*sin(angle));
			}
			glEnd();

			glPushMatrix();
			{
				glTranslatef(0, 360 / 8 * open1_up, 50 * open2_up);
				glColor3ub(200, 200, 200);
				gluSphere(glu_fill, 40, 30, 30);
			}
			glPopMatrix();

			glShadeModel(GL_FLAT);
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