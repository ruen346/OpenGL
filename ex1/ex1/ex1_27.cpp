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

int option1 = 0;//은면 off/on
int option2 = 0;//컬링 off/on

int robot_ro = 0;//45까지
int robot_sw = 0;
float robot[3];
int robot_go = 0;//0부터 상하좌우
int robot_gravity = 0;//음수면 상승

int tree_big = 30;
int tree_sw = 0;

int bong_ro = 0;

int hand_up = 0;
int hand_sw = 0;

int run_ro = 0;

int leg_ro[2];
int leg_sw[2];

int air_ro;
int pro_ro;


float ball[3];
float ball_ro[3];
int ball_go = 0;//0부터 상하좌우


int d[3];//하부 좌표
int d_ro[3];
int m_ro[3];
int u_ro[3];
int d_go = 2;//0부터 상하좌우

int open2 = 0;//1이면 앞뚜껑염
int open2_ro = 0;


void SetupRC()
{
	ball[2] = -100;
	d[2] = 100;

	srand(time(NULL));
}

void Timer(int value)
{
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

	if (robot[1] > 0)
		robot_gravity ++;
	else if (robot[1] < 0)
	{
		robot[1] = 0;
		robot_gravity = 0;
	}
	robot[1] -= robot_gravity;

	switch (robot_go)//로봇 자동이동
	{
	case 0:
		if (robot[2] >= -300)
		{
			if ((robot[0] < -120 || robot[0] > 120) && robot[2] <= -120)
			{
				if (robot[1] == 0)
					robot_gravity = -10;
			}
			else
				robot[2] -= 5;
		}
		break;

	case 1:
		if (robot[2] <= 300)
		{
			if ((robot[0] < -120 || robot[0] > 120) && robot[2] >= 120)
			{
				if (robot[1] == 0)
					robot_gravity = -10;
			}
			else
				robot[2] += 5;
		}
		break;

	case 2:
		if (robot[0] >= -300)
		{
			if ((robot[2] < -120 || robot[2] > 120) && robot[0] <= -120)
			{
				if (robot[1] == 0)
					robot_gravity = -10;
			}
			else
				robot[0] -= 5;
		}
		break;

	case 3:
		if (robot[0] <= 300)
		{
			if ((robot[2] < -120 || robot[2] > 120) && robot[0] >= 120)
			{
				if (robot[1] == 0)
					robot_gravity = -10;
			}
			else
				robot[0] += 5;
		}
		break;
	}

	if (open2 == 1 && open2_ro < 90)
		open2_ro += 2;

	else if (open2 == 0 && open2_ro > 0)
		open2_ro -= 2;



	if (abs(ball[0] - d[0]) < 65 && abs(ball[2] - d[2]) < 65)
	{
		switch (ball_go)
		{
		case 0:
			ball_go = 1;
			break;
		case 1:
			ball_go = 0;
			break;
		case 2:
			ball_go = 3;
			break;
		case 3:
			ball_go = 2;
			break;
		}

		switch (d_go)
		{
		case 0:
			d_go = 1;
			break;
		case 1:
			d_go = 0;
			break;
		case 2:
			d_go = 3;
			break;
		case 3:
			d_go = 2;
			break;
		}
	}

	//자동이동
	/*
	switch (ball_go)
	{
	case 0:
		if (ball[2] >= -300)
		{
			if (((ball[0] < -120 || ball[0] > 120) && ball[2] <= -120))
				ball_go = rand() % 4;
			else
			{
				ball[2] -= 5;
				ball_ro[0] -= 5;
			}
		}
		else
			ball_go = rand() % 4;
		break;

	case 1:
		if (ball[2] <= 300)
		{
			if ((ball[0] < -120 || ball[0] > 120) && ball[2] >= 120)
				ball_go = rand() % 4;
			else
			{
				ball[2] += 5;
				ball_ro[0] += 5;
			}
		}
		else
			ball_go = rand() % 4;
		break;

	case 2:
		if (ball[0] >= -300)
		{
			if ((ball[2] < -120 || ball[2] > 120) && ball[0] <= -120)
				ball_go = rand() % 4;
			else
			{
				ball[0] -= 5;
				ball_ro[2] -= 5;
			}
		}
		else
			ball_go = rand() % 4;
		break;

	case 3:
		if (ball[0] <= 300)
		{
			if ((ball[2] < -120 || ball[2] > 120) && ball[0] >= 120)
				ball_go = rand() % 4;
			else
			{
				ball[0] += 5;
				ball_ro[2] += 5;
			}
		}
		else
			ball_go = rand() % 4;
		break;
	}

	switch (d_go)
	{
	case 0:
		if (d[2] >= -300)
		{
			if ((d[0] < -120 || d[0] > 120) && d[2] <= -120)
				d_go = rand() % 4;
			else
				d[2] -= 5;
		}
		else
			d_go = rand() % 4;
		break;

	case 1:
		if (d[2] <= 300)
		{
			if ((d[0] < -120 || d[0] > 120) && d[2] >= 120)
				d_go = rand() % 4;
			else
				d[2] += 5;
		}
		else
			d_go = rand() % 4;
		break;

	case 2:
		if (d[0] >= -300)
		{
			if ((d[2] < -120 || d[2] > 120) && d[0] <= -120)
				d_go = rand() % 4;
			else
				d[0] -= 5;
		}
		else
			d_go = rand() % 4;
		break;

	case 3:
		if (d[0] <= 300)
		{
			if ((d[2] < -120 || d[2] > 120) && d[0] >= 120)
				d_go = rand() % 4;
			else
				d[0] += 5;
		}
		else
			d_go = rand() % 4;
		break;
	}
	*/


	if (tree_sw == 0 && tree_big < 80)
		tree_big++;
	else if (tree_big == 80)
		tree_sw = 1;

	if (tree_sw == 1 && tree_big > 45)
		tree_big--;
	else if (tree_big == 45)
		tree_sw = 0;

	if (bong_ro < 360)
		bong_ro += 5;
	else
		bong_ro = 0;

	if (hand_sw == 0 && hand_up < 30)
		hand_up++;
	else if (hand_up == 30)
		hand_sw = 1;

	if (hand_sw == 1 && hand_up > 0)
		hand_up--;
	else if (hand_up == 0)
		hand_sw = 0;

	if (run_ro < 360)
		run_ro += 5;
	else
		run_ro = 0;

	if (hand_sw == 0 && hand_up < 30)
		hand_up++;
	else if (hand_up == 30)
		hand_sw = 1;

	if (hand_sw == 1 && hand_up > 0)
		hand_up--;
	else if (hand_up == 0)
		hand_sw = 0;


	if (leg_sw[0] == 0 && leg_ro[0] < 45)
		leg_ro[0] += 5;
	else if (leg_ro[0] == 45)
		leg_sw[0] = 1;

	if (leg_sw[0] == 1 && leg_ro[0] > -45)
		leg_ro[0] -= 5;
	else if (leg_ro[0] == -45)
		leg_sw[0] = 0;

	if (leg_sw[1] == 1 && leg_ro[1] < 45)
		leg_ro[1] += 5;
	else if (leg_ro[1] == 45)
		leg_sw[1] = 0;

	if (leg_sw[1] == 0 && leg_ro[1] > -45)
		leg_ro[1] -= 5;
	else if (leg_ro[1] == -45)
		leg_sw[1] = 1;


	if (air_ro < 360)
		air_ro += 2;
	else
		air_ro = 0;

	if (pro_ro < 360)
		pro_ro += 20;
	else
		pro_ro = 0;

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i':
		y_ro = 0;

		option1 = 0;//은면 off/on
		option2 = 0;//컬링 off/on

		robot_ro = 0;//45까지
		robot_sw = 0;
		robot[0] = 0;
		robot[1] = 0;
		robot[2] = 0;
		robot_go = 0;//0부터 상하좌우
		robot_gravity = 0;//음수면 상승

		tree_big = 30;
		tree_sw = 0;

		bong_ro = 0;

		hand_up = 0;
		hand_sw = 0;

		run_ro = 0;

		leg_ro[0] = 0;
		leg_ro[1] = 0;
		leg_ro[2] = 0;
		leg_sw[0] = 0;
		leg_sw[1] = 0;
		leg_sw[2] = 0;

		air_ro = 0;
		pro_ro = 0;

		open2 = 0;//1이면 앞뚜껑염
		open2_ro = 0;
		break;

	case 'j':
		if (robot[1] == 0)
			robot_gravity = -10;
		break;

	case 'o':
		if (open2 == 0)
			open2 = 1;
		else
			open2 = 0;
		break;

	case 'a':
		ball_go = 2;
		robot_go = 2;
		break;
	case 'd':
		ball_go = 3;
		robot_go = 3;
		break;
	case 'w':
		ball_go = 0;
		robot_go = 0;
		break;
	case 's':
		ball_go = 1;
		robot_go = 1;
		break;


	case 'f':
		d_go = 2;
		break;
	case 'h':
		d_go = 3;
		break;
	case 't':
		d_go = 0;
		break;
	case 'g':
		d_go = 1;
		break;

	case 'z':
		d_ro[1] += 10;
		break;
	case 'Z':
		d_ro[1] -= 10;
		break;

	case 'x':
		m_ro[0] += 10;
		break;
	case 'X':
		m_ro[0] -= 10;
		break;

	case 'c':
		m_ro[2] += 10;
		break;
	case 'C':
		m_ro[2] -= 10;
		break;

	case 'v':
		u_ro[0] += 10;
		break;
	case 'V':
		u_ro[0] -= 10;
		break;

	case 'b':
		u_ro[2] += 10;
		break;
	case 'B':
		u_ro[2] -= 10;
		break;


	case '[':
		y_ro += 5;
		break;

	case ']':
		y_ro -= 5;
		break;

	case '1':
		if (option1 == 0)
			option1 = 1;
		else
			option1 = 0;
		break;

	case '2':
		if (option2 == 0)
			option2 = 1;
		else
			option2 = 0;
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
	if (option1 == 1)
		glEnable(GL_DEPTH_TEST);
	else if (option1 == 0)
		glDisable(GL_DEPTH_TEST);

	if (option2 == 1)
		glEnable(GL_CULL_FACE);
	else if (option2 == 0)
		glDisable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glu_fill = gluNewQuadric();
	glu_line = gluNewQuadric();
	gluQuadricDrawStyle(glu_fill, GLU_FILL);
	gluQuadricDrawStyle(glu_line, GLU_LINE);

	glPushMatrix();
	{
		gluLookAt(
			0.0, 20.0, 150.0, //EYE
			0.0, 0.0, 0.0, //AT
			0.0, 1.0, 0.0); //UP

		glTranslatef(0, -100, 0);
		glRotatef(y_ro, 0, 1, 0);

		glPushMatrix();//판
		{
			glColor3ub(255, 100, 100);
			glBegin(GL_POLYGON);
			glVertex3f(-300, 0, -300);
			glVertex3f(0, 0, -300);
			glVertex3f(-300, 0, 0);
			glEnd();

			glColor3ub(100, 255, 100);
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, -300);
			glVertex3f(300, 0, -300);
			glVertex3f(300, 0, 0);
			glEnd();

			glColor3ub(100, 100, 255);
			glBegin(GL_POLYGON);
			glVertex3f(-300, 0, 0);
			glVertex3f(-300, 0, 300);
			glVertex3f(0, 0, 300);
			glEnd();

			glColor3ub(100, 100, 100);
			glBegin(GL_POLYGON);
			glVertex3f(300, 0, 0);
			glVertex3f(300, 0, 300);
			glVertex3f(0, 0, 300);
			glEnd();

			glColor3ub(255, 255, 255);
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, -300);
			glVertex3f(-300, 0, 0);
			glVertex3f(0, 0, 300);
			glVertex3f(300, 0, 0);
			glEnd();
		}
		glPopMatrix();

		/*
		glPushMatrix();//공
		{
			glTranslatef(ball[0], 30, ball[2]);
			glRotatef(ball_ro[0] * -360 / (60 * 3.141592), 0, 0, 1);
			glRotatef(ball_ro[2] * 360 / (60 * 3.141592), 1, 0, 0);
			glRotatef(ball_ro[1] * 360 / (60 * 3.141592), 0, 1, 0);
			glColor3f(0, 0, 1);
			gluSphere(glu_line, 30, 20, 20);
		}
		glPopMatrix();

		glPushMatrix();//하중상부
		{
			glTranslatef(d[0], d[1] + 15, d[2]);
			glRotatef(d_ro[1], 0, 1, 0);
			glPushMatrix();//하부
			{
				glColor3f(1, 0, 0);
				glScalef(2, 1, 2);
				glutSolidCube(30);
			}
			glPopMatrix();

			glTranslatef(0, 15, 0);
			glRotatef(m_ro[0], 1, 0, 0);
			glRotatef(m_ro[2], 0, 1, 0);
			glTranslatef(0, -15, 0);

			glPushMatrix();//중부
			{
				glTranslatef(0, 25, 0);
				glColor3f(0, 1, 0);
				glScalef(1, 2, 1);
				glutSolidCube(10);
			}
			glPopMatrix();

			glTranslatef(0, 30, 0);
			glRotatef(u_ro[0], 1, 0, 0);
			glRotatef(u_ro[2], 0, 1, 0);
			glTranslatef(0, -30, 0);

			glPushMatrix();//상부
			{
				glTranslatef(0, 40, 0);
				glColor3f(0, 0, 1);
				glScalef(1, 2, 1);
				glutSolidCube(5);
			}
			glPopMatrix();
		}
		glPopMatrix();
		*/

		glPushMatrix();//나무
		{
			glTranslatef(200, 0, 200);

			glPushMatrix();//기둥
			{
				glTranslatef(0, 75, 0);
				glColor3ub(120, 55, 18);
				glScalef(1, 3, 1);
				glutSolidCube(50);
			}
			glPopMatrix();

			glPushMatrix();//잎
			{
				glTranslatef(0, 150, 0);
				glColor3ub(34, 116, 28);
				gluSphere(glu_fill, tree_big, 30, 30);
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//철봉
		{
			glTranslatef(200, 0, -200);

			glPushMatrix();//봉
			{
				glPushMatrix();
				{
					glTranslatef(-50, 50, 0);
					glColor3ub(0, 0, 255);
					glScalef(1, 10, 1);
					glutSolidCube(10);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(50, 50, 0);
					glColor3ub(0, 0, 255);
					glScalef(1, 10, 1);
					glutSolidCube(10);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, 100, 0);
					glColor3ub(0, 0, 255);
					glScalef(10, 1, 1);
					glutSolidCube(10);
				}
				glPopMatrix();
			}
			glPopMatrix();

			glPushMatrix();//사람
			{
				glTranslatef(0, 100, 0);
				glRotatef(bong_ro, 1, 0, 0);

				glPushMatrix();
				{
					glTranslatef(-15, -15, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 5, 1);
					glutSolidCube(6);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(15, -15, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 5, 1);
					glutSolidCube(6);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, -45, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 1, 0.5);
					glutSolidCube(30);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, -20, 0);
					glColor3ub(0, 0, 200);
					gluSphere(glu_fill, 10, 10, 10);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//런닝머신
		{
			glTranslatef(-200, 0, 200);

			glPushMatrix();//기기
			{
				glTranslatef(0, 0, -30);

				glPushMatrix();
				{
					glTranslatef(-25, 30, 0);
					glColor3ub(255, 255, 0);
					glScalef(1, 12, 1);
					glutSolidCube(5);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(25, 30, 0);
					glColor3ub(255, 255, 0);
					glScalef(1, 12, 1);
					glutSolidCube(5);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, 60, 0);
					glColor3ub(255, 255, 0);
					glScalef(10, 1, 1);
					glutSolidCube(5);
				}
				glPopMatrix();

				glPushMatrix();//마와레
				{
					glTranslatef(0, +15, 40);
					glRotatef(90, 0, 1, 0);
					glScalef(2, 0.5, 40);
					glRotatef(run_ro, 0, 0, 1);
					glColor3ub(255, 0, 0);
					glutWireTorus(1, 20, 30, 15);
				}
				glPopMatrix();
			}
			glPopMatrix();

			glPushMatrix();//사람
			{
				glTranslatef(0, 100, 0);

				glPushMatrix();
				{
					glTranslatef(-15, -30, -15);
					glColor3ub(0, 0, 200);
					glScalef(1, 1, 5);
					glutSolidCube(6);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(15, -30, -15);
					glColor3ub(0, 0, 200);
					glScalef(1, 1, 5);
					glutSolidCube(6);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, -45, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 1, 0.5);
					glutSolidCube(30);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, -20, 0);
					glColor3ub(0, 0, 200);
					gluSphere(glu_fill, 10, 10, 10);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, -60, 0);
					glRotatef(leg_ro[0], 1, 0, 0);

					glTranslatef(-15, -15, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 5, 1);
					glutSolidCube(6);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, -60, 0);
					glRotatef(leg_ro[1], 1, 0, 0);

					glTranslatef(15, -15, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 5, 1);
					glutSolidCube(6);
				}
				glPopMatrix();

			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//벤치 프레스
		{
			glTranslatef(-200, 0, -200);

			glPushMatrix();//역기
			{
				glPushMatrix();
				{
					glTranslatef(-40, 25, 0);
					glColor3ub(20, 20, 20);
					glScalef(1, 5, 1);
					glutSolidCube(10);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(40, 25, 0);
					glColor3ub(20, 20, 20);
					glScalef(1, 5, 1);
					glutSolidCube(10);
				}
				glPopMatrix();

				glPushMatrix();//역기들게
				{
					glTranslatef(0, hand_up, 0);

					glPushMatrix();
					{
						glTranslatef(0, 50, 0);
						glColor3ub(100, 100, 100);
						glScalef(10, 0.5, 0.5);
						glutSolidCube(10);
					}
					glPopMatrix();

					glPushMatrix();
					{
						glTranslatef(-55, 50, 0);
						glRotatef(90, 0, 1, 0);
						glScalef(1, 1, 0.5);
						glColor3ub(255, 0, 0);
						glutSolidTorus(15, 15, 10, 10);
					}
					glPopMatrix();

					glPushMatrix();
					{
						glTranslatef(55, 50, 0);
						glRotatef(90, 0, 1, 0);
						glScalef(1, 1, 0.5);
						glColor3ub(255, 0, 0);
						glutSolidTorus(15, 15, 10, 10);
					}
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();

			glPushMatrix();//인간
			{
				glPushMatrix();
				{
					glTranslatef(0, 10, -10);
					glColor3ub(0, 0, 200);
					gluSphere(glu_fill, 10, 10, 10);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(0, 7.5, 15);
					glColor3ub(0, 0, 200);
					glScalef(1, 0.5, 1);
					glutSolidCube(30);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(-15, 25, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 5 + (hand_up / 5), 1);
					glutSolidCube(10);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glTranslatef(15, 25, 0);
					glColor3ub(0, 0, 200);
					glScalef(1, 5 + (hand_up / 5), 1);
					glutSolidCube(10);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//날아낫ㅅㅅㅅㅅ비행기
		{
			glTranslatef(0, 200, 0);
			glRotatef(air_ro, 0, 1, 0);
			glTranslatef(200, 0, 0);

			glPushMatrix();
			{
				glTranslatef(0, 0, 0);
				glColor3ub(230, 230, 230);
				glScalef(1, 0.5, 2);
				glutSolidCube(40);
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(-40, 0, 0);
				glColor3ub(150, 150, 150);
				glScalef(2, 0.3, 0.6);
				glutSolidCube(40);
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(40, 0, 0);
				glColor3ub(150, 150, 150);
				glScalef(2, 0.3, 0.6);
				glutSolidCube(40);
			}
			glPopMatrix();

			glPushMatrix();//프로펠러
			{
				glTranslatef(0, 0, -45);
				glRotatef(pro_ro, 0, 0, 1);
				glPushMatrix();
				{
					glColor3ub(50, 50, 50);
					glScalef(10, 1, 1);
					glutSolidCube(10);
				}
				glPopMatrix();

				glPushMatrix();
				{
					glColor3ub(50, 50, 50);
					glScalef(1, 10, 1);
					glutSolidCube(10);
				}
				glPopMatrix();
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(0, 0, 70);
				glColor3ub(100, 100, 100);
				glScalef(1, 1, 1);
				gluSphere(glu_fill, 15, 10, 10);

				glTranslatef(-8, 0, 30);
				glColor3ub(100, 100, 100);
				glScalef(1, 1, 1);
				gluSphere(glu_fill, 10, 10, 10);

				glTranslatef(-8, 0, 20);
				glColor3ub(100, 100, 100);
				glScalef(1, 1, 1);
				gluSphere(glu_fill, 5, 10, 10);
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//박스
		{
			glTranslatef(0, -5, 0);
			glPushMatrix();
			{
				glBegin(GL_QUADS);
				glColor3ub(0, 255, 255);//위
				glVertex3f(-300, 300, -300);
				glColor3ub(255, 0, 255);
				glVertex3f(-300, 300, 300);
				glColor3ub(255, 255, 255);
				glVertex3f(300, 300, 300);
				glColor3ub(255, 255, 0);
				glVertex3f(300, 300, -300);
				glEnd();
			}
			glPopMatrix();
			glBegin(GL_QUADS);
			glColor3ub(0, 0, 0);//아래
			glVertex3f(300, 0, -300);
			glColor3ub(0, 0, 255);
			glVertex3f(300, 0, 300);
			glColor3ub(0, 255, 0);
			glVertex3f(-300, 0, 300);
			glColor3ub(255, 0, 0);
			glVertex3f(-300, 0, -300);

			glColor3ub(0, 255, 255);//왼쪽
			glVertex3f(-300, 300, -300);
			glColor3ub(255, 0, 0);
			glVertex3f(-300, 0, -300);
			glColor3ub(0, 255, 0);
			glVertex3f(-300, 0, 300);
			glColor3ub(255, 0, 255);
			glVertex3f(-300, 300, 300);

			glColor3ub(255, 255, 255);//오른쪽
			glVertex3f(300, 300, 300);
			glColor3ub(0, 0, 255);
			glVertex3f(300, 0, 300);
			glColor3ub(0, 0, 0);
			glVertex3f(300, 0, -300);
			glColor3ub(255, 255, 0);
			glVertex3f(300, 300, -300);

			glColor3ub(255, 0, 0);//뒤
			glVertex3f(300, 300, -300);
			glColor3ub(0, 0, 0);
			glVertex3f(300, 0, -300);
			glColor3ub(255, 255, 0);
			glVertex3f(-300, 0, -300);
			glColor3ub(0, 255, 255);
			glVertex3f(-300, 300, -300);
			glEnd();
			glPushMatrix();
			{
				glTranslatef(0, 300, 300);
				glRotatef(-open2_ro, 1, 0, 0);

				glBegin(GL_QUADS);

				glColor3ub(255, 0, 255);//앞
				glVertex3f(-300, 0, 0);
				glColor3ub(0, 255, 0);
				glVertex3f(-300, -300, 0);
				glColor3ub(0, 0, 255);
				glVertex3f(300, -300, 0);
				glColor3ub(255, 255, 255);
				glVertex3f(300, 0, 0);
				glEnd();
			}
			glPopMatrix();
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
	}
	glPopMatrix();
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 1500.0);
	glTranslatef(0.0, 0.0, -500.0);

	glMatrixMode(GL_MODELVIEW);
}