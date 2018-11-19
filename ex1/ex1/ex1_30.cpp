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

int x_ro = 0;
int y_ro = 0;

float ball[3];
float ball_r = 200;
float ii = 0;

int a = 0;
int mod = 0;

void SetupRC()
{
	ball[1] = 200;

	srand(time(NULL));
}

void Timer(int value)
{
	if (a == 0)
	{
		if (ball_r > 0)
			ball_r--;

		if (ii > 35)
			ii = 0;
		else
			ii++;

		if (ball_r == 0 && ball[1] > 60)
			ball[1] -= 2;
	}

	if (ball_r == 0 && ball[1] <= 60 && a == 0)
		a = 1;

	if (a == 1 && ball[1] < 130)
		ball[1] += 2;

	if (a == 1 && ball[1] >= 130)
		a = 2;

	if (a == 2)
	{
		ball[0] += 5;
		if (ball[1] > 50)
			ball[1] -= 2;
		else if (ball[1] > 0)
			ball[1] -= 3;
	}
		

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		x_ro += 5;
		break;

	case 'y':
		y_ro += 5;
		break;

	case 'r':
		a = 0;
		ball[0] = 0;
		ball[1] = 200;
		ball[2] = 0;
		x_ro = 0;
		y_ro = 0;
		ii = 0;
		break;

	case 'c':
		if (mod == 1)
			mod = 0;
		else
			mod = 1;
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
			0.0, 0.0, -100.0, //EYE
			0.0, -100.0, -1.0, //AT
			0.0, 1.0, 0.0); //UP

		glTranslated(0, -100, 0);
		glRotatef(x_ro, 1, 0, 0);
		glRotatef(y_ro, 0, 1, 0);

		glPushMatrix();//공
		{
			if (a == 0)
			{
				ball[0] = cos(6.28 * ii / 36) * ball_r;
				ball[2] = sin(6.28 * ii / 36) * ball_r;
			}

			glScalef(1, 1, 1);
			glColor3f(1, 0, 0);
			glTranslatef(ball[0], ball[1], ball[2]);
			gluSphere(glu_fill, 20.0, 20, 20);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glScalef(400, 1, 400);
			glColor3f(1, 1, 0);
			glutSolidCube(1);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(-200, 0, -200);
			glColor3f(1, 1, 1);

			glBegin(GL_POLYGON);
			glVertex3f(-10, 0, -10);
			glVertex3f(10, 0, -10);
			glVertex3f(10, 0, 10);
			glVertex3f(-10, 0, 10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(-10, 0, -10);
			glVertex3f(10, 0, -10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(10, 0, -10);
			glVertex3f(10, 0, 10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(-10, 0, -10);
			glVertex3f(-10, 0, 10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(-10, 0, 10);
			glVertex3f(10, 0, 10);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(200, 0, -200);
			glColor3f(1, 1, 1);

			glBegin(GL_POLYGON);
			glVertex3f(-10, 0, -10);
			glVertex3f(10, 0, -10);
			glVertex3f(10, 0, 10);
			glVertex3f(-10, 0, 10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(-10, 0, -10);
			glVertex3f(10, 0, -10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(10, 0, -10);
			glVertex3f(10, 0, 10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(-10, 0, -10);
			glVertex3f(-10, 0, 10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(-10, 0, 10);
			glVertex3f(10, 0, 10);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(200, 0, 200);
			glColor3f(1, 1, 1);

			glBegin(GL_POLYGON);
			glVertex3f(-10, 0, -10);
			glVertex3f(10, 0, -10);
			glVertex3f(10, 0, 10);
			glVertex3f(-10, 0, 10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(-10, 0, -10);
			glVertex3f(10, 0, -10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(10, 0, -10);
			glVertex3f(10, 0, 10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(-10, 0, -10);
			glVertex3f(-10, 0, 10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(-10, 0, 10);
			glVertex3f(10, 0, 10);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(-200, 0, 200);
			glColor3f(1, 1, 1);

			glBegin(GL_POLYGON);
			glVertex3f(-10, 0, -10);
			glVertex3f(10, 0, -10);
			glVertex3f(10, 0, 10);
			glVertex3f(-10, 0, 10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(-10, 0, -10);
			glVertex3f(10, 0, -10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(10, 0, -10);
			glVertex3f(10, 0, 10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(-10, 0, -10);
			glVertex3f(-10, 0, 10);
			glEnd();

			glBegin(GL_POLYGON);
			glVertex3f(0, 40, 0);
			glVertex3f(-10, 0, 10);
			glVertex3f(10, 0, 10);
			glEnd();
		}
		glPopMatrix();


		glColor3f(1, 1, 0);

		int gy = 200;
		if (ball[1] < 130 && a < 2)
			gy = 200 - (200 - ball[1]) * 2 + 10;
		
		GLfloat ctrlpoints[3][3][3] = {
			{{-200.0, 0.0, 200.0},{0.0, 200, 200.0},{200.0, 0.0, 200.0}}, 
			{{-200.0, 0.0, 0.0}, {0.0, gy, 0.0}, {200.0, 0.0, 0.0}}, 
			{{-200.0, 0.0, -200.0}, {0.0, 200, -200.0}, {200.0, 0.0, -200.0}} };

		// 곡면 제어점 설정 
		glMap2f (GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[0][0][0]); glEnable (GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉 
		glMapGrid2f (10, 0.0, 1.0, 10, 0.0, 1.0);
		// 선을 이용하여 그리드 연결 
		if (mod == 0)
			glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		else
			glEvalMesh2(GL_FILL, 0, 10, 0, 10);
		
		glPointSize(2.0); 
		glColor3f(1.0, 1.0, 0.0); 
		glBegin(GL_POINTS); 
		for (int i = 0; i < 3; i++) 
			for (int j = 0; j < 3; j++) 
				glVertex3fv(ctrlpoints[i][j]); 
		glEnd();
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