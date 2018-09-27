#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int times[6];

int spin = 0;

void one()
{
	glPushMatrix();
	glTranslatef(80, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 20, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();
}
void two()
{
	glPushMatrix();
	glTranslatef(40, -100, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -20, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 20, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 60, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();
}
void three()
{
	glPushMatrix();
	glTranslatef(40, -100, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -20, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 20, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 60, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();
}
void four()
{
	glPushMatrix();
	glTranslatef(0, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -20, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 20, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();
}
void five()
{
	glPushMatrix();
	glTranslatef(40, -100, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -20, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 20, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 60, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();
}
void six()
{
	glPushMatrix();
	glTranslatef(0, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -20, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 20, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 20, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 60, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();
}
void seven()
{
	glPushMatrix();
	glTranslatef(40, -100, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 20, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();
}
void eight()
{
	glPushMatrix();
	glTranslatef(40, -100, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -20, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 20, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 20, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 60, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();
}
void nine()
{
	glPushMatrix();
	glTranslatef(40, -100, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, -20, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 20, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();
}
void zero()
{
	glPushMatrix();
	glTranslatef(40, -100, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, -60, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 20, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80, 20, 0);
	glScalef(1, 3, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40, 60, 0);
	glScalef(3, 1, 1);
	glColor3f(1, 1, 1);
	glutSolidCube(20);
	glColor3f(0, 0, 0);
	glutWireCube(20);
	glPopMatrix();
}

void Timer(int value)
{
	time_t now = time(0);
	struct tm curr_time;
	localtime_s(&curr_time, &now);
	times[0] = curr_time.tm_hour / 10;
	times[1] = curr_time.tm_hour % 10;
	times[2] = curr_time.tm_min / 10;
	times[3] = curr_time.tm_min % 10;
	times[4] = curr_time.tm_sec / 10;
	times[5] = curr_time.tm_sec % 10;
	cout << times[0] << times[1] << "시" << times[2] << times[3] << "분" << times[4] << times[5] << "초" << endl;

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'y':
		spin += 5;
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
	srand(time(NULL));

	//변수초기화

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);

	glutCreateWindow("ex1_15");
	glutDisplayFunc(drawScene);
	glutTimerFunc(0, Timer, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glPushMatrix();
	glTranslatef(400, 300, 0.0);
	glRotatef(30, 1.0, 1.0, 0.0);
	glRotatef(spin, 0.0, 1.0, 0.0);

	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glTranslatef(-460, 0, 0.0);

	for (int i = 0; i < 6; i++)
	{
		glTranslatef(115, 0, 0);
		if (i == 2 || i == 4)
		{
			if (times[5] % 2 == 1)
			{
				glPushMatrix();
				glTranslatef(0, -70, 0);
				glColor3f(1, 1, 1);
				glutSolidCube(20);
				glColor3f(0, 0, 0);
				glutWireCube(20);
				glTranslatef(0, 95, 0);
				glColor3f(1, 1, 1);
				glutSolidCube(20);
				glColor3f(0, 0, 0);
				glutWireCube(20);
				glPopMatrix();
			}

			glTranslatef(35, 0, 0);
		}
		switch (times[i])
		{
		case 0:
			zero();
			break;
		case 1:
			one();
			break;
		case 2:
			two();
			break;
		case 3:
			three();
			break;
		case 4:
			four();
			break;
		case 5:
			five();
			break;
		case 6:
			six();
			break;
		case 7:
			seven();
			break;
		case 8:
			eight();
			break;
		case 9:
			nine();
			break;
		}
	}

	glPopMatrix();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -400, 400);
}