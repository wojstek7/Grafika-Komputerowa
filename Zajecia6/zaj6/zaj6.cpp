// opengl_stos_modelowania.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/*
(c) Janusz Ganczarski
http://www.januszg.hg.pl
JanuszG@enter.net.pl
*/

#include <GL/glut.h>
#include <stdlib.h>

// sta�e do obs�ugi menu podr�cznego

enum
{
	FULL_WINDOW,       // aspekt obrazu - ca�e okno
	ASPECT_1_1,        // aspekt obrazu 1:1
	EXIT               // wyj�cie
};

// aspekt obrazu

int aspect = FULL_WINDOW;

// rozmiary bry�y obcinania

const GLdouble left = -10.0;
const GLdouble right = 10.0;
const GLdouble bottom = -10.0;
const GLdouble top = 10.0;
const GLdouble near_ = 50.0;
const GLdouble far_ = 70.0;

// wsp�czynnik skalowania

GLfloat scale = 1.0;

// k�ty obrotu

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

// przesuni�cie

GLfloat translatex = 0.0;
GLfloat translatey = 0.0;

// wska?nik naci�ni�cia lewego przycisku myszki

int button_state = GLUT_UP;

// po�o?enie kursora myszki

int button_x, button_y;

// funkcja rysuj�ca blok 3x3

void Cube3x3()
{
	glutWireSphere(0.5, 20, 10);
	glTranslatef(1.0, 0.0, 0.0);
	glutWireSphere(0.5, 20, 10);
	glTranslatef(0.0, -1.0, 0.0);
	glutWireSphere(0.5, 20, 10);
	glTranslatef(-1.0, 0.0, 0.0);
	glutWireSphere(0.5, 20, 10);
	glTranslatef(-1.0, 0.0, 0.0);
	glutWireSphere(0.5, 20, 10);
	glTranslatef(0.0, 1.0, 0.0);
	glutWireSphere(0.5, 20, 10);
	glTranslatef(0.0, 1.0, 0.0);
	glutWireSphere(0.5, 20, 10);
	glTranslatef(1.0, 0.0, 0.0);
	glutWireSphere(0.5, 20, 10);
	glTranslatef(1.0, 0.0, 0.0);
	glutWireSphere(0.5, 20, 10);
}

// funkcja rysuj�ca blok 2x2

void Cube2x2()
{
	glutWireSphere(0.5, 20, 10);
	glTranslatef(1.0, 0.0, 0.0);
	glutWireSphere(0.5, 20, 10);
	glTranslatef(0.0, -1.0, 0.0);
	glutWireSphere(0.5, 20, 10);
	glTranslatef(-1.0, 0.0, 0.0);
	glutWireSphere(0.5, 20, 10);
}

// funkcja rysuj�ca piramid� z sze�cian�w

void Pyramid()
{
	
	// drugi poziom 5x5
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(1.0, 1.0, 0.0);
	Cube3x3();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0, -1.0, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.0, 2.0, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.0, -1.0, 0.0);
	Cube3x3();
	glPopMatrix();
	glPopMatrix();

	// trzeci poziom 4x4
	glPushMatrix();
	glTranslatef(0.0, 0.0, 2.0);
	glPushMatrix();
	glTranslatef(0.5, -0.5, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5, 1.5, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.5, 1.5, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.5, -0.5, 0.0);
	Cube2x2();
	glPopMatrix();
	glPopMatrix();

	// czwarty poziom 3x3
	glPushMatrix();
	glTranslatef(0.0, 0.0, 3.0);
	Cube3x3();
	glPopMatrix();

	// pi�ty poziom 2x2
	glPushMatrix();
	glTranslatef(0.0, 0.0, 4.0);
	glTranslatef(-0.5, 0.5, 0.0);
	Cube2x2();
	glPopMatrix();

	// sz�sty poziom 1x1
	glPushMatrix();
	glTranslatef(0.0, 0.0, 5.0);
	glutWireSphere(0.5, 20, 10);
	glPopMatrix();
}

// funkcja generuj�ca scen� 3D

void Display()
{
	// kolor t�a - zawarto�� bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT);

	// wyb�r macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// przesuni�cie uk�adu wsp�rz�dnych obiektu do �rodka bry�y odcinania
	glTranslatef(0, 0, -(near_ + far_) / 2);

	// przesuni�cie obiektu - ruch myszk�
	glTranslatef(translatex, translatey, 0.0);

	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);

	// obroty obiektu - klawisze kursora
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	// kolor kraw�dzi obiektu
	glColor3f(0.0, 0.0, 0.0);

	// rysowanie piramidy
	Pyramid();

	// skierowanie polece� do wykonania
	glFlush();

	// zamiana bufor�w koloru
	glutSwapBuffers();
}

// zmiana wielko�ci okna

void Reshape(int width, int height)
{
	// obszar renderingu - ca�e okno
	glViewport(0, 0, width, height);

	// wyb�r macierzy rzutowania
	glMatrixMode(GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	// parametry bry�y obcinania
	if (aspect == ASPECT_1_1)
	{
		// wysoko�� okna wi�ksza od wysoko�ci okna
		if (width < height && width > 0)
			glFrustum(left, right, bottom*height / width, top*height / width, near_, far_);
		else

			// szeroko�� okna wi�ksza lub r�wna wysoko�ci okna
			if (width >= height && height > 0)
				glFrustum(left*width / height, right*width / height, bottom, top, near_, far_);
	}
	else
		glFrustum(left, right, bottom, top, near_, far_);

	// generowanie sceny 3D
	Display();
}

// obs�uga klawiatury

void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+')
		scale += 0.1;
	else

		// klawisz -
		if (key == '-' && scale > 0.1)
			scale -= 0.1;

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obs�uga klawiszy funkcyjnych i klawiszy kursora

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		// kursor w lewo
	case GLUT_KEY_LEFT:
		rotatey -= 1;
		break;

		// kursor w g�r�
	case GLUT_KEY_UP:
		rotatex -= 1;
		break;

		// kursor w prawo
	case GLUT_KEY_RIGHT:
		rotatey += 1;
		break;

		// kursor w d�
	case GLUT_KEY_DOWN:
		rotatex += 1;
		break;
	}

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obs�uga przycisk�w myszki

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// zapami�tanie stanu lewego przycisku myszki
		button_state = state;

		// zapami�tanie po�o?enia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}

// obs�uga ruchu kursora myszki

void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		translatex += 1.1 *(right - left) / glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
		button_x = x;
		translatey += 1.1 *(top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}

// obs�uga menu podr�cznego

void Menu(int value)
{
	switch (value)
	{
		// obszar renderingu - ca�e okno
	case FULL_WINDOW:
		aspect = FULL_WINDOW;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// obszar renderingu - aspekt 1:1
	case ASPECT_1_1:
		aspect = ASPECT_1_1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// wyj�cie
	case EXIT:
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);

	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// rozmiary g��wnego okna programu
	glutInitWindowSize(400, 400);

	// utworzenie g��wnego okna programu
	glutCreateWindow("Stos modelowania");

	// do��czenie funkcji generuj�cej scen� 3D
	glutDisplayFunc(Display);

	// do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// do��czenie funkcji obs�ugi klawiatury
	glutKeyboardFunc(Keyboard);

	// do��czenie funkcji obs�ugi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);

	// obs�uga przycisk�w myszki
	glutMouseFunc(MouseButton);

	// obs�uga ruchu kursora myszki
	glutMotionFunc(MouseMotion);

	// utworzenie podmenu - aspekt obrazu
	int MenuAspect = glutCreateMenu(Menu);
#ifdef WIN32

	glutAddMenuEntry("Aspekt obrazu - ca�e okno", FULL_WINDOW);
#else

	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
#endif

	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);

	// menu g��wne
	glutCreateMenu(Menu);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
#ifdef WIN32

	glutAddMenuEntry("Wyj�cie", EXIT);
#else

	glutAddMenuEntry("Wyjscie", EXIT);
#endif

	// okre�lenie przycisku myszki obs�uguj�cego menu podr�czne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// wprowadzenie programu do obs�ugi p�tli komunikat�w
	glutMainLoop();
	return 0;
}
