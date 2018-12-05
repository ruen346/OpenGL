#include <GL/freeglut.h>
#include <gl/glut.h> 
#include <time.h>
#include <iostream>
#include <math.h>
#include <windows.h>
using namespace std;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLUquadricObj *glu_fill;
GLUquadricObj *glu_line;

int x_ro = 30;
int y_ro = 30;

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info) 
{
	FILE *fp;
	GLubyte *bits; 
	int bitsize, infosize; 
	BITMAPFILEHEADER header;

	// 바이너리 읽기 모드로 파일을 연다 
	if ( (fp = fopen (filename, "rb")) == NULL ) 
		return NULL;
	// 비트맵 파일 헤더를 읽는다. 
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
	{
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다. 
	if ( header.bfType != 'MB' ) 
	{ 
		fclose(fp); 
		return NULL; 
	}
	// BITMAPINFOHEADER 위치로 간다. 
	infosize = header.bfOffBits - sizeof (BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다. 
	if ( (*info = (BITMAPINFO *)malloc(infosize)) == NULL ) 
	{ 
		fclose(fp); 
		exit (0); 
		return NULL; 
	}
	// 비트맵 인포 헤더를 읽는다. 
	if ( fread (*info, 1, infosize, fp) < (unsigned int)infosize ) 
	{
		free (*info); 
		fclose(fp); 
		return NULL; 
	}
	// 비트맵의 크기 설정 
	if ( (bitsize = (*info)->bmiHeader.biSizeImage) == 0 ) 
		bitsize = (  (*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount+7) / 8.0 *  abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다. 
	if ( (bits = (unsigned char *)malloc(bitsize) ) == NULL ) 
	{
		free (*info); 
		fclose(fp); 
		return NULL; 
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다. 
	if ( fread(bits, 1, bitsize, fp) < (unsigned int)bitsize ) 
	{ 
		free (*info); 
		free (bits); 
		fclose(fp); 
		return NULL; 
	}
	fclose(fp); 
	return bits;
}

GLubyte *TexBits; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLuint texture_object[6];
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);


void SetupRC()
{
	glGenTextures(6, texture_object);

	// 1
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	TexBits = LoadDIBitmap("ex1_35_image\\1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 200, 200, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 2
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	TexBits = LoadDIBitmap("ex1_35_image\\2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 200, 200, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 3
	glBindTexture(GL_TEXTURE_2D, texture_object[2]);
	TexBits = LoadDIBitmap("ex1_35_image\\3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 200, 200, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 4
	glBindTexture(GL_TEXTURE_2D, texture_object[3]);
	TexBits = LoadDIBitmap("ex1_35_image\\4.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 200, 200, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 5
	glBindTexture(GL_TEXTURE_2D, texture_object[4]);
	TexBits = LoadDIBitmap("ex1_35_image\\5.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 200, 200, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 6
	glBindTexture(GL_TEXTURE_2D, texture_object[5]);
	TexBits = LoadDIBitmap("ex1_35_image\\6.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 200, 200, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// 텍스처 매핑 활성화
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void Timer(int value)
{
	if (y_ro < 355)
		y_ro += 5;
	else
		y_ro = 0;

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '[':
		y_ro += 5;
		break;

	case ']':
		y_ro -= 5;
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

	glEnable(GL_CULL_FACE);

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

		glRotatef(x_ro, 1, 0, 0);
		glRotatef(y_ro, 0, 1, 0);

		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, texture_object[0]);
			glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 1.0f);
			glVertex3f(-100.0, 100.0, 100.0); 
			glTexCoord2d(0.0f, 0.0f);
			glVertex3f(-100.0, -100.0, 100.0);
			glTexCoord2d(1.0f, 0.0f);
			glVertex3f(100.0, -100.0, 100.0);
			glTexCoord2d(1.0f, 1.0f);
			glVertex3f(100.0, 100.0, 100.0);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, texture_object[1]);
			glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 1.0f);
			glVertex3f(100.0, 100.0, 100.0);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3f(100.0, -100.0, 100.0);  
			glTexCoord2d(1.0f, 0.0f);
			glVertex3f(100.0, -100.0, -100.0);
			glTexCoord2d(1.0f, 1.0f);
			glVertex3f(100.0, 100.0, -100.0);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, texture_object[2]);
			glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 1.0f);
			glVertex3f(-100.0, 100.0, -100.0);  
			glTexCoord2d(0.0f, 0.0f);
			glVertex3f(100.0, 100.0, -100.0); 
			glTexCoord2d(1.0f, 0.0f);
			glVertex3f(100.0, -100.0, -100.0);
			glTexCoord2d(1.0f, 1.0f);
			glVertex3f(-100.0, -100.0, -100.0); 
			glEnd();

			glBindTexture(GL_TEXTURE_2D, texture_object[3]);
			glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 1.0f);
			glVertex3f(-100.0, 100.0, 100.0);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3f(-100.0, 100.0, -100.0); 
			glTexCoord2d(1.0f, 0.0f);
			glVertex3f(-100.0, -100.0, -100.0);
			glTexCoord2d(1.0f, 1.0f);
			glVertex3f(-100.0, -100.0, 100.0);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, texture_object[4]);
			glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 1.0f);
			glVertex3f(-100.0, -100.0, 100.0);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3f(-100.0, -100.0, -100.0);
			glTexCoord2d(1.0f, 0.0f);
			glVertex3f(100.0, -100.0, -100.0);
			glTexCoord2d(1.0f, 1.0f);
			glVertex3f(100.0, -100.0, 100.0);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, texture_object[5]);
			glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 1.0f);
			glVertex3f(-100.0, 100.0, 100.0);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3f(100.0, 100.0, 100.0);
			glTexCoord2d(1.0f, 0.0f);
			glVertex3f(100.0, 100.0, -100.0);
			glTexCoord2d(1.0f, 1.0f);
			glVertex3f(-100.0, 100.0, -100.0);
			glEnd();
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
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -500.0);

	glMatrixMode(GL_MODELVIEW);
}