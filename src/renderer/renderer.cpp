#include "stdafx.hpp"
#include "renderer.hpp"



CRenderer::CRenderer(CCamera *player)
{
	this->player = player;
	time.start();
	frame = 0;
	frame_old = 0;
}

CRenderer::~CRenderer()
{

}


void CRenderer::setDisplayMatrices(void)
{

}


void CRenderer::setupLights(void)
{
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//oswietlenie ambient - wszystkie wierzcho³ki - wy³¹czone
	float l0_amb[] = { 0.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glDisable(GL_LIGHT0);
	/*float l0_dif[] = { 0.6f, 0.6f, 0.6f };
	float l0_spe[] = { 1.0f, 1.0f, 1.0f };
	float l0_pos[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//float l0_pos[] = { player->pos.x, player->pos.y, player->pos.z, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);*/
}



void CRenderer::drawScene()
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
		player->pos.x + player->view.x, player->pos.y + player->view.y, player->pos.z + player->view.z,
		player->up.x, player->up.y, player->up.z
		);


	setupLights();

	// Przesuniecie swiata (przeciwienstwo przesuniecia kamery).

	// Obrot kamery - aby zatrzymac ja w miejscu, nalezy zakomentowac.
	//glRotatef(frame / 2, 0.0f, 1.0f, 0.0f);


	// Rysowanie obiektow na scenie.


	/* 3rd CAMERA */
	/*
	glPushMatrix();
	glTranslatef(player->view.x + player->pos.x, player->view.y + player->pos.y, player->view.z + player->pos.z);
	glRotatef(-((player->angleY * 180) / PI), 0, 1, 0);
	glRotatef(-((player->angleX * 180) / PI), 0, 0, 1);
	glutWireCube(0.2);
	glTranslatef(-player->view.x - player->pos.x, -player->view.y - player->pos.y , -player->view.z - player->pos.z);
	glPopMatrix();
	*/


#pragma region Szescian

	glPushMatrix();

	glTranslatef(-1.5f, 1.0f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);

	float m1_amb[] = { 0.8f, 0.8f, 0.2f };
	float m1_dif[] = { 0.8f, 0.8f, 0.2f };
	float m1_spe[] = { 0.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m1_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m1_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m1_spe);

	glBegin(GL_QUADS);

	// Przod
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Tyl
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Lewa
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Prawa
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Gora
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	// Dol
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glEnd();

	glPopMatrix();

#pragma endregion

#pragma region Walec

	glPushMatrix();

	glTranslatef(1.5f, 1.0f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);

	float m2_amb[] = { 0.8f, 0.2f, 0.8f };
	float m2_dif[] = { 0.8f, 0.2f, 0.8f };
	float m2_spe[] = { 0.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m2_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m2_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m2_spe);

	int Np = 48;

	// Powierzchnia boczna
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= Np; ++i) {
		float x = sin(2.0f * PI * ((float)i / Np));
		float z = cos(2.0f * PI * ((float)i / Np));
		glNormal3f(x, 0.0f, z);
		glVertex3f(x, 1.0f, z);
		glNormal3f(x, 0.0f, z);
		glVertex3f(x, -1.0f, z);
	}
	glEnd();

	// Podstawa gorna
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i <= Np; ++i) {
		float x = sin(2.0f * PI * ((float)i / Np));
		float z = cos(2.0f * PI * ((float)i / Np));
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(x, 1.0f, z);
	}
	glEnd();

	// Podstawa dolna
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	for (int i = Np; i >= 0; --i) {
		float x = sin(2.0f * PI * ((float)i / Np));
		float z = cos(2.0f * PI * ((float)i / Np));
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(x, -1.0f, z);
	}
	glEnd();

	glPopMatrix();

#pragma endregion

#pragma region Sciany

	glBegin(GL_QUADS);

#pragma region Przednia sciana
	{
		float m_amb[] = { 1.0f, 1.0f, 1.0f };
		float m_dif[] = { 1.0f, 1.0f, 1.0f };
		float m_spe[] = { 0.0f, 0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-5.0f, 5.0f, -5.0f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-5.0f, 0.0f, -5.0f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(5.0f, 0.0f, -5.0f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(5.0f, 5.0f, -5.0f);
	}
#pragma endregion

#pragma region Lewa sciana
	{
		float m_amb[] = { 1.0f, 0.0f, 0.0f };
		float m_dif[] = { 1.0f, 0.0f, 0.0f };
		float m_spe[] = { 0.0f, 0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-5.0f, 0.0f, -5.0f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-5.0f, 5.0f, -5.0f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-5.0f, 5.0f, 5.0f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-5.0f, 0.0f, 5.0f);
	}
#pragma endregion

#pragma region Prawa sciana
	{
		float m_amb[] = { 0.0f, 1.0f, 0.0f };
		float m_dif[] = { 0.0f, 1.0f, 0.0f };
		float m_spe[] = { 0.0f, 0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(5.0f, 5.0f, -5.0f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(5.0f, 0.0f, -5.0f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(5.0f, 0.0f, 5.0f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(5.0f, 5.0f, 5.0f);
	}
#pragma endregion

#pragma region Tylna sciana
	{
		float m_amb[] = { 1.0f, 1.0f, 1.0f };
		float m_dif[] = { 1.0f, 1.0f, 1.0f };
		float m_spe[] = { 0.0f, 0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-5.0f, 0.0f, 5.0f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-5.0f, 5.0f, 5.0f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(5.0f, 5.0f, 5.0f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(5.0f, 0.0f, 5.0f);
	}
#pragma endregion

#pragma region Podloga
	{
		float m_amb[] = { 1.0f, 1.0f, 1.0f };
		float m_dif[] = { 1.0f, 1.0f, 1.0f };
		float m_spe[] = { 0.0f, 0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-5.0f, 0.0f, -5.0f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-5.0f, 0.0f, 5.0f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(5.0f, 0.0f, 5.0f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(5.0f, 0.0f, -5.0f);
	}
#pragma endregion

#pragma region Sufit
	{
		float m_amb[] = { 1.0f, 1.0f, 1.0f };
		float m_dif[] = { 1.0f, 1.0f, 1.0f };
		float m_spe[] = { 0.0f, 0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-5.0f, 5.0f, 5.0f);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-5.0f, 5.0f, -5.0f);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(5.0f, 5.0f, -5.0f);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(5.0f, 5.0f, 5.0f);
	}
#pragma endregion

	glEnd();

#pragma endregion


	glPushMatrix();
	glLineWidth(5);
	glBegin(GL_LINES);
	//glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(player->pos.x + player->view.x, player->pos.y + player->view.y, player->pos.z + player->view.z);
	glVertex3f(player->pos.x + player->view.x, player->pos.y + player->view.y, player->pos.z + player->view.z);
	//glVertex3f(player->pos.x, player->pos.y, player->pos.z);
	//glVertex3f(0, 0, 0);
	glEnd();
	glPopMatrix();

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
	if (time.getElapsedMilliseconds() > 1000)
	{
		std::stringstream title;
		title << "FPS: " << static_cast<int>(frame - frame_old) << "   frames:" << frame;
		frame_old = frame;
		glutSetWindowTitle(title.str().c_str());
		time.start();
	}
}
