#include <GL/freeglut.h> 
#include <time.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);


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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int j = 0; j < 4; j++)
	{
		float color3 = rand() % 10;
		color3 /= 10;
		int z = rand() % 10 + 1;
		int z2 = rand() % 5 + 3;
		for (int i = 0; i <= 10; i++)
		{
			float color = 0.1*i;
			float color2 = 0.25 * j;
			glColor4f(color, color2, color3, color);
			glRectf((-400.0f) + (600 / z2) * j, (-300.0f) + (i - 1) * 600 / z, (-400.0f) + (600 / z2) * (j + 1), (-300.0f) + i * 600 / z);
		}
	}

	glFlush(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400, 400, -300, 300, -1.0, 1.0);
}