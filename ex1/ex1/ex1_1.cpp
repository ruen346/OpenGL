#include <GL/freeglut.h> 
GLvoid drawScene (GLvoid); 
GLvoid Reshape (int w, int h);

void main(int argc, char *argv[]) 
{
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition ( 100, 100 ); // �������� ��ġ���� 
	glutInitWindowSize ( 800, 600 ); // �������� ũ�� ���� 
	glutCreateWindow ( "Example2" ); // ������ ���� (������ �̸�) 
	glutDisplayFunc (drawScene); // ��� �Լ��� ���� 
	glutReshapeFunc (Reshape); glutMainLoop(); 
}

// ������ ��� �Լ� 
GLvoid drawScene ( GLvoid ) 
{ 
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �������� 'blue' �� ���� 
	glClear( GL_COLOR_BUFFER_BIT ); // ������ ������ ��ü�� ĥ�ϱ� 

	glColor4f(0.0f, 1.0f, 1.0f, 1.0f); // �׸��� ���� 'green' ���� ���� 
	glRectf (-1.0f, 1.0f, -0.5f, 0.5f); // �簢�� �׸��� 
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glRectf(1.0f, 1.0f, 0.5f, 0.5f);
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	glRectf(-1.0f, -1.0f, -0.5f, -0.5f);
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glRectf(1.0f, -1.0f, 0.5f, -0.5f);

	glLineWidth(1.0);
	glBegin(GL_LINES);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(0.0f, 0.2f);
	glVertex2f(-0.15f, -0.2f);
	glVertex2f(0.15f, -0.2f);
	glEnd();

	glFlush(); // ȭ�鿡 ����ϱ� 
} 

GLvoid Reshape (int w, int h) 
{
	glViewport(0, 0, w, h); 
}