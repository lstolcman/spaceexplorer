#include "stdafx.hpp"
#include "renderer.hpp"



CRenderer::CRenderer()
{
	time.start();
	frame		= 0;
	frame_old	= 0;
}

CRenderer::~CRenderer()
{

}

void CRenderer::lookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
                       GLdouble centerX, GLdouble centerY, GLdouble centerZ,
                       GLdouble upX, GLdouble upY, GLdouble upZ)
{
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upZ, upZ);
}

void CRenderer::setDisplayMatrices(void)
{
	// Wyczysc zawartosc bufora koloru i glebokosci.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Wybor macierzy, ktora od tej pory bedziemy modyfikowac
	// - macierz Modelu/Widoku.
	glMatrixMode(GL_MODELVIEW);

	// Zaladowanie macierzy jednostkowej.
	glLoadIdentity();

}


void CRenderer::setupLights(void)
{

}

void CRenderer::playerGetCoordinates(SPlayer player)
{
	gluLookAt(player.pos.x, player.pos.y, player.pos.z,
	          player.pos.x + player.dir.x, player.pos.y + player.dir.y, player.pos.z + player.dir.z,
	          0.0f, 1.0f, 0.0f);
}

void CRenderer::drawScene(void)
{
	drawFPS();
	//gluLookAt(player.pos.x, player.pos.y, player.pos.z,
	//         player.pos.x + player.dir.x, player.pos.y + player.dir.y, player.pos.z + player.dir.z,
	//          0.0f, 1.0f, 0.0f);
	//gluLookAt(player., eyeY, eyeZ, centerX, centerY, centerZ, upX, upZ, upZ);
	setDisplayMatrices();
	//setupLights();

	// Przesuniecie swiata (przeciwienstwo przesuniecia kamery).
	glTranslatef(0.0f, 0.0f, -20.0f);

	// Obrot kamery - aby zatrzymac ja w miejscu, nalezy zakomentowac.
	//glRotatef(frame / 2, 0.0f, 1.0f, 0.0f);


	// Rysowanie obiektow na scenie.

	// klatka
	glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(1.0, 3.0, 1.0);
	glutWireCube(5);
	glPopMatrix();


	// Jesli instrukcje w danej implementacji OpenGL byly buforowane,
	// w tym momencie bufor zostanie oprozniony a instrukcje wykonane.
	glFlush();

	// Zamien front-buffer z back-bufferem (double buffering).
	glutSwapBuffers();

	// Nakaz wyswietlic kolejna klatke.
	glutPostRedisplay();

	// Inkrementacja licznika klatek.
	frame += 1;

}



void CRenderer::drawFPS()
{
	//std::cout << "elapsedmsL:"<< instance->timexx.getElapsedMilliseconds()<<"\r";
	if (time.getElapsedMilliseconds() > 1000)
	{

		std::stringstream title;
		title << "FPS: " << static_cast<int>(frame - frame_old) << "   frames:" << frame;
		//std::cout << "old:" << frame_old << " new:" << frame << " minus:" << frame - frame_old << "\r";
		frame_old = frame;
		glutSetWindowTitle(title.str().c_str());
		time.start();
	}
}
