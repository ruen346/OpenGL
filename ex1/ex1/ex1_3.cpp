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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Example2"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(drawScene); // 출력 함수의 지정 
	glutReshapeFunc(Reshape); glutMainLoop();
}

// 윈도우 출력 함수 
GLvoid drawScene(GLvoid)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 

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

	glFlush(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400, 400, -300, 300, -1.0, 1.0);
}