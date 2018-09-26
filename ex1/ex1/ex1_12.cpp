#include <GL/freeglut.h>
#include <time.h>
#include <iostream>
#include <math.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int draw_mod = 0;
int circle_mod = 0;
int draw_select = 0;
int timers = 0;
int timers2 = 0;
int rotate_y = 0;

int click_x[5];
int click_y[5];
int click_num = 0; // 며번 점을 찍었는지
int click_num2 = 0; // 몇번째 점으로 이동하는지
int click_on = 0;

int big = 10;
int big_mod = 0;

void Timer(int value)
{
	if (timers < 359)
		timers++;
	else
		timers = 0;

	if (timers2 < 99)
		timers2++;
	else
	{
		timers2 = 0;
		if (click_num2 == click_num - 2)
			click_num2 = 0;
		else
			click_num2++;
	}

	if (big > 19)
		big_mod = 1;
	else if (big < 5)
		big_mod = 0;
	if (big_mod == 0)
		big++;
	else if(big_mod == 1)
		big--;

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '0':
		draw_mod = 0;
		break;
	case '1':
		draw_mod = 1;
		break;
	case '2':
		draw_mod = 2;
		break;
	case '3':
		draw_mod = 3;
		break;
	case '4':
		draw_mod = 4;
		break;

	case 'Y':
		rotate_y += 1;
		break;
	case 'y':
		rotate_y -= 1;
		break;

	case 'm':
		if (circle_mod == 0)
			circle_mod = 1;
		else
			circle_mod = 0;
		break;
	case 'd':
		if (draw_select == 0)
			draw_select = 1;
		else
			draw_select = 0;
		break;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (click_on == 1)
		{
			click_num = 0;
			click_on = 0;
		}
		click_x[click_num] = x;
		click_y[click_num] = y;
		click_num++;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		click_on = 1;
		click_num2 = 0;
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

	glutCreateWindow("ex1_12");
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

	glPushMatrix();
	glTranslatef(400.0, 300.0, 0.0);
	glRotatef(rotate_y, 0.0, 1, 0.0);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3i(-400, 0, 0);
	glVertex3i(400, 0, 0);
	glVertex3i(0, -300, 0);
	glVertex3i(0, 300, 0);
	glEnd();

	float rad = 150;
	float angle;

	switch (draw_mod)
	{
	case 0:
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for (int i = 0; i < 359; i++)
		{
			float angle;
			angle = i * 3.14 / 180;
			glVertex2f(rad*cos(angle), rad*sin(angle));
			angle = (i + 1) * 3.14 / 180;
			glVertex2f(rad*cos(angle), rad*sin(angle));
		}
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		rad = 150;
		
		angle = timers * 3.14 / 180;
		if (circle_mod == 1)
		{
			glPushMatrix();
			glTranslatef(rad*cos(angle), rad*sin(angle), 0.0);
			glRotatef(timers, 0.0, 0.0, 1.0);
			if(draw_select == 0)
				glRecti(-big, -big, big, big);
			else
			{
				glBegin(GL_POLYGON);
				glVertex2f(0, -big);
				glVertex2f(-big, big);
				glVertex2f(big, big);
				glEnd();
			}
			glPopMatrix();
		}
		else
		{
			if(draw_select == 0)
				glRecti(rad*cos(angle) - big, rad*sin(angle) - big, rad*cos(angle) + big, rad*sin(angle) + big);
			else
			{
				glBegin(GL_POLYGON);
				glVertex2f(rad*cos(angle), rad*sin(angle) - big);
				glVertex2f(rad*cos(angle) - big, rad*sin(angle) + big);
				glVertex2f(rad*cos(angle) + big, rad*sin(angle) + big);
				glEnd();
			}
		}	
		break;

	case 1:
		glPushMatrix();
		glTranslatef(-180, 0, 0.0);

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for (int i = 0; i < 359; i++)
		{
			angle = i * 3.14 / 180;
			glVertex2f(i, rad*sin(angle));
			angle = (i + 1) * 3.14 / 180;
			glVertex2f(i + 1, rad*sin(angle));
		}
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		rad = 150;

		angle = timers * 3.14 / 180;
		if (draw_select == 0)
			glRecti(timers - big, rad*sin(angle) - big, timers + big, rad*sin(angle) + big);
		else
		{
			glBegin(GL_POLYGON);
			glVertex2f(timers, rad*sin(angle) - big);
			glVertex2f(timers - big, rad*sin(angle) + big);
			glVertex2f(timers + big, rad*sin(angle) + big);
			glEnd();
		}
		glPopMatrix();
		break;

	case 2:
		glPushMatrix();
		glTranslatef(-180, 0, 0.0);

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for (int i = 0; i < 359; i++)
		{
			angle = i * 6.28 / 180;
			glVertex2f(rad*cos(angle) + i / 2, rad*sin(angle));
			angle = (i + 1) * 6.28 / 180;
			glVertex2f(rad*cos(angle) + (i + 1) / 2, rad*sin(angle));
		}
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		rad = 150;

		angle = timers * 6.28 / 180;
		if (draw_select == 0)
			glRecti(rad*cos(angle) + timers / 2 - big, rad*sin(angle) - big, rad*cos(angle) + timers / 2 + big, rad*sin(angle) + big);
		else
		{
			glBegin(GL_POLYGON);
			glVertex2f(rad*cos(angle) + timers / 2, rad*sin(angle) - big);
			glVertex2f(rad*cos(angle) + timers / 2 - big, rad*sin(angle) + big);
			glVertex2f(rad*cos(angle) + timers / 2 + big, rad*sin(angle) + big);
			glEnd();
		}
		glPopMatrix();
		break;

	case 3:
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(-400, 200);
		glVertex2f(0, -200);
		glVertex2f(0, -200);
		glVertex2f(400, 200);
		glEnd();

		if (draw_select == 0)
		{
			if(timers < 180)
				glRecti(timers * 400 / 180 - 400 - big, - timers * 400 / 180 + 200 - big, timers * 400 / 180 - 400 + big, - timers * 400 / 180 + 200 + big);
			else
				glRecti(timers * 400 / 180 - 400 - big, timers * 400 / 180 + 200 - big - 800, timers * 400 / 180 - 400 + big, timers * 400 / 180 + 200 + big - 800);
		}
		else
		{
			if (timers < 180)
			{
				glBegin(GL_POLYGON);
				glVertex2f(timers * 400 / 180 - 400, -timers * 400 / 180 + 200 - big);
				glVertex2f(timers * 400 / 180 - 400 + big, -timers * 400 / 180 + 200 + big);
				glVertex2f(timers * 400 / 180 - 400 - big, -timers * 400 / 180 + 200 + big);
				glEnd();
			}
			else
			{
				glBegin(GL_POLYGON);
				glVertex2f(timers * 400 / 180 - 400, timers * 400 / 180 + 200 - big - 800);
				glVertex2f(timers * 400 / 180 - 400 + big, timers * 400 / 180 + 200 - big - 800);
				glVertex2f(timers * 400 / 180 - 400 - big, timers * 400 / 180 + 200 - big - 800);
				glEnd();
			}
		}
		break;

	case 4:
		glPushMatrix();
		glTranslatef(-400, -300, 0.0);
		if (click_on == 1)
		{
			glColor3f(1.0, 0.0, 0.0);
			for (int i = 0; i < click_num - 1; i++)
			{
				glBegin(GL_LINES);
				glVertex2f(click_x[i], click_y[i]);
				glVertex2f(click_x[i + 1], click_y[i + 1]);
				glEnd();
			}

			if (draw_select == 0)
			{
				int first1 = timers2 * (click_x[click_num2 + 1] - click_x[click_num2]) / 100 + click_x[click_num2];
				int first2 = timers2 * (click_y[click_num2 + 1] - click_y[click_num2]) / 100 + click_y[click_num2];
				glRecti(first1 - big, first2 - big, first1 + big, first2 + big);
			}
			else
			{
				int first1 = timers2 * (click_x[click_num2 + 1] - click_x[click_num2]) / 100 + click_x[click_num2];
				int first2 = timers2 * (click_y[click_num2 + 1] - click_y[click_num2]) / 100 + click_y[click_num2];
				glBegin(GL_POLYGON);
				glVertex2f(first1, first2 - big);
				glVertex2f(first1 - big, first2 + big);
				glVertex2f(first1 + big, first2 + big);
				glEnd();
			}
		}
		glPopMatrix();
		break;
	}

	glPopMatrix();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -400, 400);
}