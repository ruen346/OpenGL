#include <GL/freeglut.h> 
#include <time.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void two(int num)
{
	int x = num % 3;
	int y = num / 3;
	float co = 800 / 3;

	glBegin(GL_LINES);
	glVertex2f(-400 + x * co + 20, -300 + y * 200 + 20);
	glVertex2f(-400 + (x + 1) * co - 20, -100 + y * 200 - 20);
	glEnd();
}

void three(int num)
{
	int x = num % 3;
	int y = num / 3;
	float co = 800 / 3;
	glBegin(GL_POLYGON);
	glVertex2f(-400 + x * co + 100, -300 + y * 200 + 20);
	glVertex2f(-400 + x * co + 20, -100 + y * 200 - 20);
	glVertex2f(-400 + (x + 1) * co - 20, -100 + y * 200 - 20);
	glEnd();

}

void four(int num)
{
	int x = num % 3;
	int y = num / 3;
	float co = 800 / 3;
	glBegin(GL_POLYGON);
	glVertex2f(-400 + x * co + 20, -300 + y * 200 + 20);
	glVertex2f(-400 + (x + 1) * co - 20, -300 + y * 200 + 20);
	glVertex2f(-400 + (x + 1) * co - 20, -300 + (y + 1) * 200 - 20);
	glVertex2f(-400 + x * co + 20, -300 + (y + 1) * 200 - 20);
	glEnd();
}

void five(int num)
{
	int x = num % 3;
	int y = num / 3;
	float co = 800 / 3;
	glBegin(GL_POLYGON);

	glVertex2f(-400 + x * co + 20, -300 + y * 200 + 60);
	glVertex2f(-400 + x * co + 100, -300 + y * 200 + 20);
	glVertex2f(-400 + (x + 1) * co - 20, -300 + y * 200 + 60);
	glVertex2f(-400 + (x + 1) * co - 20, -300 + (y + 1) * 200 - 20);
	glVertex2f(-400 + x * co + 20, -300 + (y + 1) * 200 - 20);
	glEnd();
}

void main(int argc, char *argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example2"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(drawScene); // ��� �Լ��� ���� 
	glutReshapeFunc(Reshape); glutMainLoop();
}

// ������ ��� �Լ� 
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �������� 'blue' �� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	glLineWidth(1.0);
	glBegin(GL_LINES);
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	float co = 800 / 3;
	glVertex2f(-400 + co, 300.0f);
	glVertex2f(-400 + co, -300.0f);
	glVertex2f(-400 + co + co, 300.0f);
	glVertex2f(-400 + co + co, -300.0f);

	glVertex2f(-400, -100.0f);
	glVertex2f(400, -100.0f);
	glVertex2f(-400, 100.0f);
	glVertex2f(400, 100.0f);

	glEnd();

	int num = rand() % 4 + 2;
	int rever = 0;
	for (int i = 0; i < 9; i++)
	{
		if (num == 6)
		{
			rever = 1;
			num = 4;
		}
		else if (num == 1)
		{
			rever = 0;
			num = 3;
		}

		switch (num)
		{
		case 2: two(i); break;
		case 3: three(i); break;
		case 4: four(i); break;
		case 5: five(i); break;
		}

		if (rever == 1)
			num--;
		else
			num++;
	}

	glFlush(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400, 400, -300, 300, -1.0, 1.0);
}