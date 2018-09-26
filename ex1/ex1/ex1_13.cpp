#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int move_time = 0;
int spin_y = 0;
int big = 200;


void Timer(int value)
{
	if (move_time < 299)
		move_time++;
	else
		move_time = 0;

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'y':
		spin_y++;
		break;
	case 'Y':
		spin_y--;
		break;

	case 's':
		big += 10;
		break;
	case 'S':
		big -= 10;
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

	glutCreateWindow("ex1_11");
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
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	//십자가
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3i(0, 300, 0);
	glVertex3i(800, 300, 0);
	glVertex3i(400, 0, 0);
	glVertex3i(400, 600, 0);
	glEnd();

	//큰삼각형
	glPushMatrix();
	glTranslatef(400.0, 300.0, 0.0);
	glRotatef(spin_y, 0.0, 1.0, 0.0);

	glBegin(GL_LINES);
	glVertex3i(0, -big, 0);
	glVertex3i(-big, big, 0);
	glVertex3i(-big, big, 0);
	glVertex3i(big, big, 0);
	glVertex3i(big, big, 0);
	glVertex3i(0, -big, 0);
	glEnd();


	//작은삼각형
	glPushMatrix();
	if(move_time < 100)
		glTranslatef(0 - move_time * big / 100, -big + move_time * big * 2 / 100, 0.0);
	else if (move_time < 200)
		glTranslatef(-big + (move_time - 100) * big * 2 / 100, big, 0.0);
	else
		glTranslatef(big - (move_time - 200) * big / 100, big - (move_time - 200) * big * 2 / 100, 0.0);
	glRotatef(spin_y, 0.0, 1.0, 0.0);

	glBegin(GL_LINES);
	glVertex3i(0, -10, 0);
	glVertex3i(-10, 10, 0);
	glVertex3i(-10, 10, 0);
	glVertex3i(10, 10, 0);
	glVertex3i(10, 10, 0);
	glVertex3i(0, -10, 0);
	glEnd();

	glPopMatrix(); 
	glPopMatrix();


	/////////////////////////////////////////////////////////////

	//큰삼각형2
	glPushMatrix();
	glTranslatef(400.0, 300.0, 0.0);
	glRotatef(spin_y, 0.0, 1.0, 0.0);

	glBegin(GL_LINES);
	glVertex3i(0, -big, 0);
	glVertex3i(0, big, -big);
	glVertex3i(0, big, -big);
	glVertex3i(0, big, big);
	glVertex3i(0, big, big);
	glVertex3i(0, -big, 0);
	glEnd();


	//작은삼각형2
	glPushMatrix();
	if (move_time < 100)
		glTranslatef(0, -big + move_time * big * 2 / 100, 0 - move_time * big / 100);
	else if (move_time < 200)
		glTranslatef(0, big, -big + (move_time - 100) * big * 2 / 100);
	else
		glTranslatef(0, big - (move_time - 200) * big * 2 / 100, big - (move_time - 200) * big / 100);
	glRotatef(spin_y, 0.0, 1.0, 0.0);

	glBegin(GL_LINES);
	glVertex3i(0, -10, 0);
	glVertex3i(-10, 10, 0);
	glVertex3i(-10, 10, 0);
	glVertex3i(10, 10, 0);
	glVertex3i(10, 10, 0);
	glVertex3i(0, -10, 0);
	glEnd();

	glPopMatrix();
	glPopMatrix();


	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -400, 400);
}