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

int light_active[2];
float light0[2];
float light1[2];
float light2[2];
float light_ro = 0;

int ball_turn = 0;

int on = 0;

int snow_x[100];
int snow_y[100];
int snow_z[100];
float snow_speed[100];
int snow_active = 0;

int tile_color[100][100];


void SetupRC()
{
	for (int i = 0; i < 100; i++)
	{
		snow_x[i] = rand() % 400 - 200;
		snow_y[i] = 400;
		snow_z[i] = rand() % 400 - 200;
		snow_speed[i] = rand() % 10 / 2 + 3;
	}

	light0[0] = 0.1;
	light0[1] = 0.1;
	light1[0] = 0.5;
	light1[1] = 0.5;
	light2[0] = 0.2;
	light2[1] = 0.2;

	srand(time(NULL));
}

void Timer(int value)
{
	if (ball_turn < 355)
		ball_turn += 5;
	else
		ball_turn = 0;

	if (snow_active == 1)
	{
		for (int i = 0; i < 100; i++)
		{
			if (snow_y[i] <= 0)
			{
				tile_color[snow_x[i] / 4 + 50][snow_z[i] / 4 + 50]++;

				snow_x[i] = rand() % 400 - 200;
				snow_y[i] = 400;
				snow_z[i] = rand() % 400 - 200;
				snow_speed[i] = rand() % 10 / 2 + 3;
			}
			else
				snow_y[i] -= snow_speed[i];
		}
	}

	if (light_ro < 358)
		light_ro += 2;
	else
		light_ro = 0;

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

	case 'a':
		light0[0] += 0.1;
		light0[1] += 0.1;
		break;
	case 'A':
		light0[0] -= 0.1;
		light0[1] -= 0.1;
		break;
	case 'd':
		light1[0] += 0.1;
		light1[1] += 0.1;
		break;
	case 'D':
		light1[0] -= 0.1;
		light1[1] -= 0.1;
		break;
	case 's':
		light2[0] += 0.1;
		light2[1] += 0.1;
		break;
	case 'S':
		light2[0] -= 0.1;
		light2[1] -= 0.1;
		break;

	case 'o':
		if (on == 1)
			on = 0;
		else
			on = 1;
		break;

	case 'p':
		if (snow_active == 0)
			snow_active = 1;
		else
			snow_active = 0;
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
			0.0, 100.0, 100.0, //EYE
			0.0, 0.0, 0.0, //AT
			0.0, 1.0, 0.0); //UP

		glRotatef(y_ro, 0, 1, 0);


		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				glPushMatrix();//타일
				{
					glTranslatef((i - 50) * 4, 0, (j - 50) * 4);
					glColor3ub(25*tile_color[i][j], 25 * tile_color[i][j], 25 * tile_color[i][j]);
					glutSolidCube(4);
				}
				glPopMatrix();
			}
		}

		if (snow_active == 1)
		{
			for (int i = 0; i < 100; i++)
			{
				glPushMatrix();//snow
				{
					glTranslatef(snow_x[i], snow_y[i], snow_z[i]);
					glColor3ub(255, 255, 255);
					gluSphere(glu_fill, 2, 5, 5);
				}
				glPopMatrix();
			}
		}

		glPushMatrix();//공
		{
			glTranslatef(cos(ball_turn * 3.14 / 180) * 200, 180, sin(ball_turn * 3.14 / 180) * 200);
			glColor3ub(255, 255, 30);
			gluSphere(glu_fill, 20.0, 20, 20);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(-200, 0, -200);
			glColor3ub(50, 50, 50);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(glu_fill, 20, 0, 20, 4, 10);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(200, 0, -200);
			glColor3ub(50, 50, 50);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(glu_fill, 20, 0, 20, 4, 10);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(200, 0, 200);
			glColor3ub(50, 50, 50);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(glu_fill, 20, 0, 20, 4, 10);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslated(-200, 0, 200);
			glColor3ub(50, 50, 50);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(glu_fill, 20, 0, 20, 4, 10);
		}
		glPopMatrix();


		glPushMatrix();//중앙기둥
		{
			glColor3ub(0, 100, 0);

			if (on == 1)
			{
				glEnable(GL_AUTO_NORMAL);
				glNormal3f(0.0, 150.0, 0.0);
			}
			else
				glDisable(GL_AUTO_NORMAL);

			glBegin(GL_QUADS);
			glVertex3f(0, 200, 0);//시작
			glVertex3f(100, 0, 100);
			glVertex3f(-100, 0, 100);
			glVertex3f(0, 200, 0);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(0, 200, 0);//시작
			glVertex3f(100, 0, -100);
			glVertex3f(100, 0, 100);
			glVertex3f(0, 200, 0);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(0, 200, 0);//시작
			glVertex3f(-100, 0, -100);
			glVertex3f(100, 0, -100);
			glVertex3f(0, 200, 0);
			glEnd();

			glBegin(GL_QUADS);
			glVertex3f(0, 200, 0);//시작
			glVertex3f(-100, 0, 100);
			glVertex3f(-100, 0, -100);
			glVertex3f(0, 200, 0);
			glEnd();
		}
		glPopMatrix();

		glPushMatrix();//좌측빛
		{
			glTranslatef(cos((light_ro + 180) * 3.14 / 180) * 250, 200, sin((light_ro + 180) * 3.14 / 180) * 250);
			glColor3ub(150, 150, 255);
			glRotatef(-90, 0, 1, 0);
			gluCylinder(glu_fill, 10, 0.0, 20, 20, 8);
		}
		glPopMatrix();

		glPushMatrix();//우측빛
		{
			glTranslatef(cos(light_ro * 3.14 / 180) * 250, 200, sin(light_ro * 3.14 / 180) * 250);
			glColor3ub(255, 150, 150);
			glRotatef(90, 0, 1, 0);
			gluCylinder(glu_fill, 10, 0.0, 20, 20, 8);
		}
		glPopMatrix();

		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);



		GLfloat AmbientLight[] = { light0[0], light0[0], light0[0], 0.0f };//주변 조명
		GLfloat DiffuseLight[] = { light1[0], light1[0], 1.0, 0.0f };//산란 반사 조명
		GLfloat SpecularLight[] = { light2[0], light2[0], 1.0, 0.0f };//거울반사 조명
		GLfloat lightPos[] = { cos((light_ro + 180) * 3.14 / 180) * 250, 200, sin((light_ro + 180) * 3.14 / 180) * 250, 1 };
		GLfloat specref[] = { 1,1,1,1 };

		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


		GLfloat AmbientLight1[] = { light0[1], light0[1], light0[1], 0.0f };//주변 조명
		GLfloat DiffuseLight1[] = { 1, light1[1], light1[1], 0.0f };//산란 반사 조명
		GLfloat SpecularLight1[] = { 1, light2[1], light2[1], 0.0f };//거울반사 조명
		GLfloat lightPos1[] = { cos(light_ro * 3.14 / 180) * 250, 200, sin(light_ro * 3.14 / 180) * 250, 1 };

		glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight1);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		/*스포트
		
		glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
		glMateriali(GL_FRONT, GL_SHININESS, 62);
		*/


		if (light_active[0] == 1)
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