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

int light_active[2];
int light_ro_active;
float light_ro[2];
float light1[2];
float light2[2];


void SetupRC()
{
	light1[0] = 2.5;
	light1[1] = 2.5;
	light2[0] = 0.5;
	light2[1] = 0.5;
	light_ro[1] = 180;

	srand(time(NULL));
}

void Timer(int value)
{
	if (light_ro_active == 1)
	{
		if (light_ro[0] < 350)
			light_ro[0] += 5;
		else
			light_ro[0] = 0;

		if (light_ro[1] < 350)
			light_ro[1] += 5;
		else
			light_ro[1] = 0;
	}

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		if (light_active[0] == 0)
			light_active[0] = 1;
		else
			light_active[0] = 0;
		break;

	case '2':
		if (light_active[1] == 0)
			light_active[1] = 1;
		else
			light_active[1] = 0;
		break;

	case 'y':
		if (light_ro[0] < 350)
			light_ro[0] += 10;
		else
			light_ro[0] = 0;

		if (light_ro[1] < 350)
			light_ro[1] += 10;
		else
			light_ro[1] = 0;
		break;

	case 'a':
		if (light_ro_active == 0)
			light_ro_active = 1;
		else
			light_ro_active = 0;
		break;

	case 'd':
		light1[0] += 0.2;
		light1[1] += 0.2;
		break;
	case 'D':
		light1[0] -= 0.2;
		light1[1] -= 0.2;
		break;

	case 's':
		light2[0] += 0.2;
		light2[1] += 0.2;
		break;
	case 'S':
		light2[0] -= 0.2;
		light2[1] -= 0.2;
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
			0.0, 0.0, 0.0, //EYE
			0.0, 0.0, -1.0, //AT
			0.0, 1.0, 0.0); //UP


		glPushMatrix();//공
		{
			glColor3ub(50, 50, 50);
			gluSphere(glu_fill, 50.0, 20, 20);
		}
		glPopMatrix();


		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);



		GLfloat AmbientLight[] = { 0.1f, 0.1f, 0.1f, 0.0f };//주변 조명
		GLfloat DiffuseLight[] = { light1[0], light1[0], 0.0, 0.0f };//산란 반사 조명
		GLfloat SpecularLight[] = { light2[0], light2[0], 0.0, 0.0f };//거울반사 조명
		GLfloat lightPos[] = { cos(3.14 * light_ro[0] / 180) * 150, 0, sin(3.14 * light_ro[0] / 180) * 150, 1 };
		GLfloat specref[] = { 1,1,1,1 };

		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


		GLfloat AmbientLight1[] = { 0.1f, 0.1f, 0.1f, 0.0f };//주변 조명
		GLfloat DiffuseLight1[] = { 0, light1[1], light1[1], 0.0f };//산란 반사 조명
		GLfloat SpecularLight1[] = { 0, light2[1], light2[1], 0.0f };//거울반사 조명
		GLfloat lightPos1[] = { cos(3.14 * light_ro[1] / 180) * 150, 0, sin(3.14 * light_ro[1] / 180) * 150, 0, 1 };

		glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight1);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);



		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
		glMateriali(GL_FRONT, GL_SHININESS, 64);



		if(light_active[0] == 1)
			glEnable(GL_LIGHT0);
		else
			glDisable(GL_LIGHT0);
		if (light_active[1] == 1)
			glEnable(GL_LIGHT1);
		else
			glDisable(GL_LIGHT1);
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