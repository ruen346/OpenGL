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
int z_ro = 0;

int ball_x[5];
int ball_y[5];
int ball_z[5];
int ball_go[5];

int cube_x[3];
int cube_y[3];
int cube_z[3];
int cube_ro[3];//아래0 왼쪽1 위2 오른쪽3


void SetupRC()
{
	for (int i = 0; i < 5; i++)
	{
		ball_x[i] = (rand() % 100) - 50;
		ball_y[i] = (rand() % 100) - 50;
		ball_z[i] = (rand() % 100) - 50;
		ball_go[i] = rand() % 4;
	}

	cube_y[0] = -100 + 15;
	cube_y[1] = -100 + 10;
	cube_y[2] = -100 + 5;
	cube_z[0] = -15;
	cube_z[1] = 10;
	cube_z[2] = 25;

	srand(time(NULL));
}

void Timer(int value)
{
	if (z_ro < 0)
		z_ro += 360;
	else if (z_ro > 360)
		z_ro -= 360;

	for (int i = 0; i < 5; i++)
	{
		switch (ball_go[i])
		{
		case 0:
			if (ball_x[i] < 90)
			{
				ball_x[i] += 5;
				ball_y[i] -= 5;
			}
			else
				ball_go[i] = 1;
			break;

		case 1:
			if (ball_y[i] > -90)
			{
				ball_x[i] -= 5;
				ball_y[i] -= 5;
			}
			else
				ball_go[i] = 2;
			break;

		case 2:
			if (ball_x[i] > -90)
			{
				ball_x[i] -= 5;
				ball_y[i] += 5;
			}
			else
				ball_go[i] = 3;
			break;

		case 3:
			if (ball_y[i] < 90)
			{
				ball_x[i] += 5;
				ball_y[i] += 5;
			}
			else
				ball_go[i] = 0;
			break;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (cube_ro[i] == 0)
		{
			if (z_ro <= 90 && z_ro >= 45)
			{
				switch (i)
				{
				case 0:
					if (cube_x[i] > -85)
						cube_x[i] -= 5;
					break;
				case 1:
					if (cube_x[i] > -90)
						cube_x[i] -= 5;
					break;
				case 2:
					if (cube_x[i] > -95)
						cube_x[i] -= 5;
					break;
				}	
			}
			else if (z_ro >= 270 && z_ro <= 315)
			{
				switch (i)
				{
				case 0:
					if (cube_x[i] < 85)
						cube_x[i] += 5;
					break;
				case 1:
					if (cube_x[i] < 90)
						cube_x[i] += 5;
					break;
				case 2:
					if (cube_x[i] < 95)
						cube_x[i] += 5;
					break;
				}
			}
			else if (z_ro > 90 && z_ro <= 135)
				cube_ro[i] = 1;
			else if (z_ro < 270 && z_ro >= 225)
				cube_ro[i] = 3;
			else if(z_ro > 135 && z_ro < 225)
				cube_ro[i] = 2;


			//수직낙ㄱㄱㄱ하
			switch (i)
			{
			case 0:
				if (cube_y[i] > -85)
					cube_y[i] -= 5;
				break;
			case 1:
				if (cube_y[i] > -90)
					cube_y[i] -= 5;
				break;
			case 2:
				if (cube_y[i] > -95)
					cube_y[i] -= 5;
				break;
			}
		}

		if (cube_ro[i] == 1)
		{
			if (z_ro >= 0 && z_ro <= 45)
			{
				switch (i)
				{
				case 0:
					if (cube_y[i] > -85)
						cube_y[i] -= 5;
					break;
				case 1:
					if (cube_y[i] > -90)
						cube_y[i] -= 5;
					break;
				case 2:
					if (cube_y[i] > -95)
						cube_y[i] -= 5;
					break;
				}
			}
			else if (z_ro <= 180 && z_ro >= 135)
			{
				switch (i)
				{
				case 0:
					if (cube_y[i] < 85)
						cube_y[i] += 5;
					break;
				case 1:
					if (cube_y[i] < 90)
						cube_y[i] += 5;
					break;
				case 2:
					if (cube_y[i] < 95)
						cube_y[i] += 5;
					break;
				}
			}
			else if (z_ro > 180 && z_ro <= 225)
				cube_ro[i] = 2;
			else if (z_ro < 360 && z_ro >= 315)
				cube_ro[i] = 0;
			else if (z_ro > 225 && z_ro < 315)
				cube_ro[i] = 3;


			//수직낙ㄱㄱㄱ하
			switch (i)
			{
			case 0:
				if (cube_x[i] > -85)
					cube_x[i] -= 5;
				break;
			case 1:
				if (cube_x[i] > -90)
					cube_x[i] -= 5;
				break;
			case 2:
				if (cube_x[i] > -95)
					cube_x[i] -= 5;
				break;
			}
		}

		if (cube_ro[i] == 2)
		{
			if (z_ro <= 270 && z_ro >= 225)
			{
				switch (i)
				{
				case 0:
					if (cube_x[i] < 85)
						cube_x[i] += 5;
					break;
				case 1:
					if (cube_x[i] < 90)
						cube_x[i] += 5;
					break;
				case 2:
					if (cube_x[i] < 95)
						cube_x[i] += 5;
					break;
				}
			}
			else if (z_ro >= 90 && z_ro <= 125)
			{
				switch (i)
				{
				case 0:
					if (cube_x[i] > -85)
						cube_x[i] -= 5;
					break;
				case 1:
					if (cube_x[i] > -90)
						cube_x[i] -= 5;
					break;
				case 2:
					if (cube_x[i] > -95)
						cube_x[i] -= 5;
					break;
				}
			}
			
			else if (z_ro > 270 && z_ro <= 315)
				cube_ro[i] = 3;
			else if (z_ro < 90 && z_ro >= 45)
				cube_ro[i] = 1;
			else if (z_ro < 45 || z_ro > 315)
				cube_ro[i] = 2;
		

			//수직낙ㄱㄱㄱ하
			switch (i)
			{
			case 0:
				if (cube_y[i] < 85)
					cube_y[i] += 5;
				break;
			case 1:
				if (cube_y[i] < 90)
					cube_y[i] += 5;
				break;
			case 2:
				if (cube_y[i] < 95)
					cube_y[i] += 5;
				break;
			}
		}

		if (cube_ro[i] == 3)
		{
			if (z_ro >= 180 && z_ro <= 225)
			{
				switch (i)
				{
				case 0:
					if (cube_y[i] < 85)
						cube_y[i] += 5;
					break;
				case 1:
					if (cube_y[i] < 90)
						cube_y[i] += 5;
					break;
				case 2:
					if (cube_y[i] < 95)
						cube_y[i] += 5;
					break;
				}
			}
			else if (z_ro <= 360 && z_ro >= 315)
			{
				switch (i)
				{
				case 0:
					if (cube_y[i] > -85)
						cube_y[i] -= 5;
					break;
				case 1:
					if (cube_y[i] > -90)
						cube_y[i] -= 5;
					break;
				case 2:
					if (cube_y[i] > -95)
						cube_y[i] -= 5;
					break;
				}
			}
			else if (z_ro > 0 && z_ro <= 45)
				cube_ro[i] = 0;
			else if (z_ro < 180 && z_ro >= 135)
				cube_ro[i] = 2;
			else if (z_ro > 45 && z_ro < 135)
				cube_ro[i] = 1;


			//수직낙ㄱㄱㄱ하
			switch (i)
			{
			case 0:
				if (cube_x[i] < 85)
					cube_x[i] += 5;
				break;
			case 1:
				if (cube_x[i] < 90)
					cube_x[i] += 5;
				break;
			case 2:
				if (cube_x[i] < 95)
					cube_x[i] += 5;
				break;
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'y':
		y_ro += 5;
		break;

	case 'Y':
		y_ro -= 5;
		break;

	case 'z':
		z_ro += 5;
		break;

	case 'Z':
		z_ro -= 5;
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
	if (x < 350)
		z_ro ++;
	if (x > 450)
		z_ro --;
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

	glEnable(GL_CULL_FACE);

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

		glRotatef(y_ro, 0, 1, 0);
		glRotatef(z_ro, 0, 0, 1);
		
		glPushMatrix();
		{
			glBegin(GL_QUADS);//윗면
			glColor3ub(30, 30, 30);
			glVertex3f(-100, 100, -100);
			glVertex3f(100, 100, -100);
			glVertex3f(100, 100, 100);
			glVertex3f(-100, 100, 100);
			glEnd();

			glBegin(GL_QUADS);//아래면
			glColor3ub(100, 100, 100);
			glVertex3f(-100, -100, 100);
			glVertex3f(100, -100, 100);
			glVertex3f(100, -100, -100);
			glVertex3f(-100, -100, -100);
			glEnd();

			glBegin(GL_QUADS);//앞면
			glColor3ub(70, 70, 70);
			glVertex3f(-100, 100, 100);
			glVertex3f(100, 100, 100);
			glVertex3f(100, -100, 100);
			glVertex3f(-100, -100, 100);
			glEnd();

			glBegin(GL_QUADS);//뒷면
			glColor3ub(50, 50, 50);
			glVertex3f(-100, 100, -100);
			glVertex3f(-100, -100, -100);
			glVertex3f(100, -100, -100);
			glVertex3f(100, 100, -100);
			glEnd();

			glBegin(GL_QUADS);//왼면
			glColor3ub(150, 150, 150);
			glVertex3f(-100, -100, -100);
			glVertex3f(-100, 100, -100);
			glVertex3f(-100, 100, 100);
			glVertex3f(-100, -100, 100);
			glEnd();

			glBegin(GL_QUADS);//오른면
			glColor3ub(120, 120, 120);
			glVertex3f(100, -100, -100);
			glVertex3f(100, -100, 100);
			glVertex3f(100, 100, 100);
			glVertex3f(100, 100, -100);
			glEnd();

			for (int i = 0; i < 5; i++)//공들
			{
				glPushMatrix();
				{
					glTranslatef(ball_x[i], ball_y[i], ball_z[i]);
					glColor3ub(255, 191, 248);
					gluSphere(glu_fill, 10, 10, 10);
				}
				glPopMatrix();
			}

			for (int i = 0; i < 3; i++)//사각형들
			{
				glPushMatrix();
				{
					glTranslatef(cube_x[i], cube_y[i], cube_z[i]);
					if (i == 0)
					{
						glColor3ub(155, 90, 61);
						glutSolidCube(30);
					}
					else if (i == 1)
					{
						glColor3ub(142, 246, 238);
						glutSolidCube(20);
					}
					else if (i == 2)
					{
						glColor3ub(158, 162, 255);
						glutSolidCube(10);
					}
				}
				glPopMatrix();
			}
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
	glTranslatef(0.0, 0.0, -300.0);

	glMatrixMode(GL_MODELVIEW);
}