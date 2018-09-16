#include <GL/freeglut.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_RECTANGLE 10

GLint myRect[MAX_RECTANGLE][2];
GLint width = 800;
GLint height = 600;
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int count = 0;


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example 1");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutDisplayFunc(drawScene);


	glutMainLoop();


}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		myRect[count % 10][0] = x;
		myRect[count % 10][1] = y;

		count++;


		glutPostRedisplay();
	}

}
void TimerFunction(int value)
{

}


GLvoid drawScene()
{

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < count; i++)
	{

		glRectf(myRect[i][0] - 5, myRect[i][1] + 5, myRect[i][0] + 5, myRect[i][1] - 5);

	}






	glFlush();

}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800.0, 600.0, 0, -1.0, 1.0);
}