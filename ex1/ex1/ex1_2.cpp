#include <GL/freeglut.h> 
#include <time.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);


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

	glFlush(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400, 400, -300, 300, -1.0, 1.0);
}