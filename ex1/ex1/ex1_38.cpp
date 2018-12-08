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

float alpha[9];
float select = 0;

void SetupRC()
{
	for (int i = 0; i < 9; i++)
	{
		alpha[i] = (rand() % 9 + 1) / 10.f;
		cout << alpha[i] << endl;
	}

	cout << "glBlendFunc(GL_ONE, GL_ZERO); break;" << endl;
	cout << "glBlendFunc(GL_ONE, GL_ONE); break; " << endl;
	cout << " glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_SRC_COLOR); break;" << endl;
	cout << " glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA); break;" << endl;
	cout << " glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR); break;" << endl;
	cout << "glBlendFunc(GL_ONE, GL_DST_ALPHA); break; " << endl;
	cout << "glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO); break; " << endl;
	cout << " glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;" << endl;
	cout << "glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ZERO); break; " << endl;

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
	case '1':
		select = 0;
		break;
	case '2':
		select = 1;
		break;
	case '3':
		select = 2;
		break;
	case '4':
		select = 3;
		break;
	case '5':
		select = 4;
		break;
	case '6':
		select = 5;
		break;
	case '7':
		select = 6;
		break;
	case '8':
		select = 7;
		break;
	case '9':
		select = 8;
		break;

	case 'a':
		alpha[int(select)] += 0.1;
		break;
	case 's':
		alpha[int(select)] -= 0.1;
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

	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glu_fill = gluNewQuadric();
	glu_line = gluNewQuadric();
	gluQuadricDrawStyle(glu_fill, GLU_FILL);
	gluQuadricDrawStyle(glu_line, GLU_LINE);

	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < 9; i++)
	{
		switch (i)
		{
		case 0:
			glBlendFunc(GL_ONE, GL_ZERO); break;
		case 1:
			glBlendFunc(GL_ONE, GL_ONE); break;
		case 2:
			glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_SRC_COLOR); break;
		case 3:
			glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA); break;
		case 4:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR); break;
		case 5:
			glBlendFunc(GL_ONE, GL_DST_ALPHA); break;
		case 6:
			glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO); break;
		case 7:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
		case 8:
			glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ZERO); break;
		}
		glPushMatrix();
		{
			
			glTranslatef((i % 3 - 1) * 300, (i / 3 - 1) * 300, 0);

			glColor4f(1, 0, 0, alpha[i]);
			glutSolidTeapot(50);

			glColor4f(0, 1, 0, alpha[i]);
			glTranslatef(-20, -20, -50);
			glutSolidCube(50);

			glColor4f(0, 0, 1, alpha[i]);
			glTranslatef(40, 40, -50);
			glutSolidSphere(50, 50, 50);
		}
		glPopMatrix();
	}

	glPushMatrix();
	{
		glTranslatef((int(select) % 3 - 1) * 300, (int(select / 3) - 1) * 300, 0);
		glColor3f(1, 1, 1);
		glBegin(GL_LINES);  
		glVertex3f(100.0, -100.0, 0.0);
		glVertex3f(100.0, 100.0, 0.0); 
		glVertex3f(100.0, 100.0, 0.0);
		glVertex3f(-100.0, 100.0, 0.0); 
		glVertex3f(-100.0, 100.0, 0.0);
		glVertex3f(-100.0, -100.0, 0.0);
		glVertex3f(-100.0, -100.0, 0.0);
		glVertex3f(100.0, -100.0, 0.0);
		glEnd();

		glRectf(-100, -100, 100, 100);
	}
	glPopMatrix();

	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500, 500, 500, -500, -500, 500);

	glMatrixMode(GL_MODELVIEW);
}