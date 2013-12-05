#include "stdafx.hpp"
#include "renderer.hpp"



CRenderer::CRenderer(SPlayer *player)
{
	this->player = player;
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

}


void CRenderer::setupLights(void)
{
	float l0_amb[] = { 0.2f, 0.2f, 0.2f };
	float l0_dif[] = { 0.6f, 0.6f, 0.6f };
	float l0_spe[] = { 1.0f, 1.0f, 1.0f };
	float l0_pos[] = { 1.0f, 5.0f, 4.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
}



void CRenderer::drawScene()//SPlayer player)
{
	drawFPS();

	//setDisplayMatrices();

	// Wyczysc zawartosc bufora koloru i glebokosci.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Wybor macierzy, ktora od tej pory bedziemy modyfikowac
	// - macierz Modelu/Widoku.
	glMatrixMode(GL_MODELVIEW);

	// Zaladowanie macierzy jednostkowej.
	glLoadIdentity();

	gluLookAt(
		player->pos.x, player->pos.y, player->pos.z,
		player->pos.x + player->dir.x, player->pos.y + player->dir.y, player->pos.z + player->dir.z,
		0.0f, 1.0f, 0.0f
		);


	setupLights();

	// Przesuniecie swiata (przeciwienstwo przesuniecia kamery).
	//glTranslatef(0.0f, 0.0f, -20.0f);

	// Obrot kamery - aby zatrzymac ja w miejscu, nalezy zakomentowac.
	//glRotatef(frame / 2, 0.0f, 1.0f, 0.0f);


	// Rysowanie obiektow na scenie.

	glPushMatrix();

	glScalef(2, 2, 2);
	glColor3d(40, 34, 52);
	glutSolidSphere(11, 20, 20);
	glTranslatef(2, 0, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	{
		float m_amb[] = { 0.5f, 0.5f, 0.5f };
		float m_dif[] = { 0.5f, 0.2f, -0.5f };
		float m_spe[] = { 0.5f, 0.5f, -0.3f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

		glNormal3f( 0.0f,  1.0f,  0.0f);
		glVertex3f(-5.0f,  0.0f, -5.0f);

		glNormal3f( 0.0f,  1.0f,  0.0f);
		glVertex3f(-5.0f,  0.0f,  5.0f);

		glNormal3f( 0.0f,  1.0f,  0.0f);
		glVertex3f( 5.0f,  0.0f,  5.0f);

		glNormal3f( 0.0f,  1.0f,  0.0f);
		glVertex3f( 15.0f,  0.0f, -10.0f);
	}
	glEnd();




	// Zamien front-buffer z back-bufferem (double buffering).
	glutSwapBuffers();


	// Jesli instrukcje w danej implementacji OpenGL byly buforowane,
	// w tym momencie bufor zostanie oprozniony a instrukcje wykonane.
	glFlush();



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













