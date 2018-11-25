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

int robot[3];
int robot_go = 1;
int robot_ro = 0;
int robot_sw = 0;


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

	robot[2] = 150;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			tile_color[i][j] = 1;
		}
	}

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

	if (robot_sw == 0)
	{
		if (robot_ro < 45)
			robot_ro += 5;
		else
			robot_sw = 1;
	}
	else if (robot_sw == 1)
	{
		if (robot_ro > -45)
			robot_ro -= 5;
		else
			robot_sw = 0;
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

void special(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		robot_go = 0;
		robot[2] -= 5;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		robot_go = 1;
		robot[2] += 5;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		robot_go = 3;
		robot[0] += 5;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		robot_go = 2;
		robot[0] -= 5;
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
	glutSpecialFunc(special);
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
					glColor3ub(25 * tile_color[i][j], 25 * tile_color[i][j], 25 * tile_color[i][j]);
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
			glColor3ub(20, 20, 20);

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

		glPushMatrix();//나는야 로봇트ㅡㅡㅡㅡㅡㅡㅡㅡ
		{
			glTranslatef(robot[0], robot[1], robot[2]);
			switch (robot_go)
			{
			case 0:
				glRotatef(180, 0, 1, 0); break;
			case 1:
				glRotatef(0, 0, 1, 0); break;
			case 2:
				glRotatef(-90, 0, 1, 0); break;
			case 3:
				glRotatef(90, 0, 1, 0); break;
			}

			glPushMatrix();//다리1
			{
				glTranslatef(-20, 50, 0);
				glRotatef(robot_ro, 1, 0, 0);
				glTranslatef(20, -50, 0);

				glTranslatef(-20, 25, 0);
				glColor3ub(255, 168, 146);
				glScalef(1, 5, 1);
				glutSolidCube(10);
			}
			glPopMatrix();

			glPushMatrix();//다리2
			{
				glTranslatef(20, 50, 0);
				glRotatef(-robot_ro, 1, 0, 0);
				glTranslatef(-20, -50, 0);

				glTranslatef(20, 25, 0);
				glColor3ub(63, 204, 255);
				glScalef(1, 5, 1);
				glutSolidCube(10);
			}
			glPopMatrix();

			glPushMatrix();//몸
			{
				glTranslatef(0, 75, 0);
				glColor3ub(255, 206, 145);
				glScalef(5, 5, 1);
				glutSolidCube(10);
			}
			glPopMatrix();

			glPushMatrix();//팔1
			{
				glTranslatef(-30, 100, 0);
				glRotatef(-robot_ro, 1, 0, 0);
				glTranslatef(30, -100, 0);

				glTranslatef(-30, 75, 0);
				glColor3ub(155, 90, 61);
				glScalef(1, 5, 1);
				glutSolidCube(10);
			}
			glPopMatrix();

			glPushMatrix();//팔2
			{
				glTranslatef(30, 100, 0);
				glRotatef(robot_ro, 1, 0, 0);
				glTranslatef(-30, -100, 0);

				glTranslatef(30, 75, 0);
				glColor3ub(255, 72, 140);
				glScalef(1, 5, 1);
				glutSolidCube(10);
			}
			glPopMatrix();

			glPushMatrix();//머리
			{
				glTranslatef(0, 115, 0);
				glColor3ub(193, 193, 193);
				glScalef(3, 3, 1);
				glutSolidCube(10);
			}
			glPopMatrix();

			glPushMatrix();//코
			{
				glTranslatef(0, 115, 7.5);
				glColor3ub(158, 162, 255);
				glScalef(2, 2, 1);
				glutSolidCube(5);
			}
			glPopMatrix();

		}
		glPopMatrix();

		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);



		GLfloat AmbientLight[] = { light0[0], light0[0], light0[0], 0.0f };//주변 조명
		GLfloat DiffuseLight[] = { light1[0], light1[0], light1[0] * 2, 0.0f };//산란 반사 조명
		GLfloat SpecularLight[] = { light2[0], light2[0], 0, 0.0f };//거울반사 조명
		GLfloat lightPos[] = { cos((light_ro + 180) * 3.14 / 180) * 250, 200, sin((light_ro + 180) * 3.14 / 180) * 250, 0 };
		GLfloat specref[] = { 1,1,1,1 };

		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


		GLfloat AmbientLight1[] = { light0[1], light0[1], light0[1], 0.0f };//주변 조명
		GLfloat DiffuseLight1[] = { light1[1] * 2, light1[1], light1[1], 0.0f };//산란 반사 조명
		GLfloat SpecularLight1[] = { 0, light2[1], light2[1], 0.0f };//거울반사 조명
		GLfloat lightPos1[] = { cos(light_ro * 3.14 / 180) * 250, 200, sin(light_ro * 3.14 / 180) * 250, 0 };

		glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight1);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


		GLfloat AmbientLight2[] = { 0, 0, 0, 0.0f };//주변 조명
		GLfloat DiffuseLight2[] = { 1.0f, 1.0f,1.0f, 0.0f };//산란 반사 조명
		GLfloat SpecularLight2[] = { 0.3f, 0.3f, 0.3f, 0.0f };//거울반사 조명
		GLfloat lightPos2[] = { robot[0], 200, robot[2], 1 };
		float spotlightDirection[] = { 0.0f, -1.0f, 0.0f };              // 스포트라이트 방향
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0f);                  // 80도 원뿔
		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 90.0f);                 // 초점 설정
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotlightDirection);   // 방향 설정

		glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight2);
		glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight2);
		glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);


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

		glEnable(GL_LIGHT2);
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