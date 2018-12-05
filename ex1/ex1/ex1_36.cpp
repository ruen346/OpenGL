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

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	// 바이너리 읽기 모드로 파일을 연다 
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다. 
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
	{
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다. 
	if (header.bfType != 'MB')
	{
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다. 
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다. 
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
	{
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다. 
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize)
	{
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정 
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 *  abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다. 
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL)
	{
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다. 
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize)
	{
		free(*info);
		free(bits);
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
	TexBits = LoadDIBitmap("ex1_36_image\\b.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 400, 400, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, TexBits);
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




	light0[0] = 0.1;
	light0[1] = 0.1;
	light1[0] = 1.5;
	light1[1] = 1.5;
	light2[0] = 0.5;
	light2[1] = 0.5;

	srand(time(NULL));
}

void Timer(int value)
{

	if (ball_turn < 355)
		ball_turn += 5;
	else
		ball_turn = 0;


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

	case 'o':
		if (on == 1)
			on = 0;
		else
			on = 1;
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
	glDisable(GL_CULL_FACE);
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



		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);


		GLfloat AmbientLight[] = { light0[0], light0[0], light0[0], 0.0f };//주변 조명
		GLfloat DiffuseLight[] = { light1[0], light1[0], light1[0] * 2, 0.0f };//산란 반사 조명
		GLfloat SpecularLight[] = { light2[0], light2[0], light2[0], 0.0f };//거울반사 조명
		GLfloat lightPos[] = { cos((light_ro + 180) * 3.14 / 180) * 250, 200, sin((light_ro + 180) * 3.14 / 180) * 250, 0 };

		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


		GLfloat AmbientLight1[] = { light0[1], light0[1], light0[1], 0.0f };//주변 조명
		GLfloat DiffuseLight1[] = { light1[1] * 2, light1[1], light1[1], 0.0f };//산란 반사 조명
		GLfloat SpecularLight1[] = { light2[1], light2[1], light2[1], 0.0f };//거울반사 조명
		GLfloat lightPos1[] = { cos(light_ro * 3.14 / 180) * 250, 200, sin(light_ro * 3.14 / 180) * 250, 0 };

		glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight1);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
		GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
		glMateriali(GL_FRONT, GL_SHININESS, 64);
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

		glPushMatrix();//바닥
		{
			glBindTexture(GL_TEXTURE_2D, texture_object[0]);
			glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 1.0f);
			glVertex3f(-200.0, 0.0, 200.0);
			glTexCoord2d(0.0f, 0.0f);
			glVertex3f(200.0, 0.0, 200.0);
			glTexCoord2d(1.0f, 0.0f);
			glVertex3f(200.0, 0.0, -200.0);
			glTexCoord2d(1.0f, 1.0f);
			glVertex3f(-200.0, 0.0, -200.0);
			glEnd();
		}
		glPopMatrix();

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
			glEnable(GL_NORMALIZE);
			glEnable(GL_AUTO_NORMAL);

			glBindTexture(GL_TEXTURE_2D, texture_object[0]);

			glBegin(GL_QUADS);
			if (on == 1)
				glNormal3f(0, 100, 50);
			glTexCoord2d(0.5f, 1.0f);
			glVertex3f(0, 200, 0);//시작
			glTexCoord2d(0.0f, 0.0f);
			glVertex3f(-100, 0, 100);
			glTexCoord2d(1.0f, 0.0f);
			glVertex3f(100, 0, 100);
			glVertex3f(0, 200, 0);//시작
			glEnd();

			glBegin(GL_QUADS);
			if (on == 1)
				glNormal3f(50, 100, -100);
			glTexCoord2d(0.5f, 1.0f);
			glVertex3f(0, 200, 0);//시작
			glTexCoord2d(0.0f, 0.0f);
			glVertex3f(100, 0, -100);
			glTexCoord2d(1.0f, 0.0f);
			glVertex3f(100, 0, 100);
			glVertex3f(0, 200, 0);//시작
			glEnd();

			glBegin(GL_QUADS);
			if (on == 1)
				glNormal3f(0, 100, -50);
			glTexCoord2d(0.5f, 1.0f);
			glVertex3f(0, 200, 0);//시작
			glTexCoord2d(0.0f, 0.0f);
			glVertex3f(-100, 0, -100);
			glTexCoord2d(1.0f, 0.0f);
			glVertex3f(100, 0, -100);
			glVertex3f(0, 200, 0);//시작
			glEnd();

			glBegin(GL_QUADS);
			if (on == 1)
				glNormal3f(-50, 100, -100);
			glTexCoord2d(0.5f, 1.0f);
			glVertex3f(0, 200, 0);//시작
			glTexCoord2d(0.0f, 0.0f);
			glVertex3f(-100, 0, 100);
			glTexCoord2d(1.0f, 0.0f);
			glVertex3f(-100, 0, -100);
			glVertex3f(0, 200, 0);//시작
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