#include "stdafx.hpp"
#include "renderer.hpp"



CRenderer::CRenderer(SData *data)
{
	this->camera = data->camera;
	time.start();
	frame = 0;
	frame_old = 0;

}

CRenderer::~CRenderer()
{

}


bool CRenderer::loadTextures(void)
{
	CTimer t;
	t.start();
	skybox.front.Load("resources/s_front5.bmp", GL_NEAREST, GL_NEAREST);
	skybox.back.Load("resources/s_back6.bmp", GL_NEAREST, GL_NEAREST);
	skybox.right.Load("resources/s_right1.bmp", GL_NEAREST, GL_NEAREST);
	skybox.left.Load("resources/s_left2.bmp", GL_NEAREST, GL_NEAREST);
	skybox.top.Load("resources/s_top3.bmp", GL_NEAREST, GL_NEAREST);
	skybox.bottom.Load("resources/s_bottom4.bmp", GL_NEAREST, GL_NEAREST);
	t.stop();
	std::cout << "Skybox loaded, took " << t.getElapsedMilliseconds() << "ms" << std::endl;
	return true;
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


void CRenderer::setDisplayMatrices(void)
{
	// Wyczysc zawartosc bufora koloru i glebokosci.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Wybor macierzy, ktora od tej pory bedziemy modyfikowac
	// - macierz Modelu/Widoku.
	glMatrixMode(GL_MODELVIEW);

	// Zaladowanie macierzy jednostkowej.
	glLoadIdentity();

	gluLookAt(
		camera->pos.x, camera->pos.y, camera->pos.z,
		camera->pos.x + camera->view.x, camera->pos.y + camera->view.y, camera->pos.z + camera->view.z,
		camera->up.x, camera->up.y, camera->up.z
		);

}


void CRenderer::setupLights(void)
{
	//oswietlenie ambient - wszystkie wierzcho³ki - wy³¹czone
	float globAmbient[4] = { 1.1f, 1.1f, 1.1f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmbient);

	/*if (camera->latarka)
		glEnable(GL_LIGHT0);
		else
		glDisable(GL_LIGHT0);
		float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		float l0_dif[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		float l0_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		//float l0_pos[] = { 2.7f, 2.7f, -1.3f, 1.0f };
		//float l0_dir[] = { -0.9f, -0.3f, 1.3f};
		float l0_pos[] = { camera->pos.x, camera->pos.y, camera->pos.z, 1.0f };
		float l0_dir[] = { camera->view.x, camera->view.y, camera->view.z };
		glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
		glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0_dir);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0f);*/



	glEnable(GL_LIGHT0);
#pragma region Swiatlo
	float l0_amb[] = { 0.2f, 0.2f, 0.2f };
	float l0_dif[] = { 0.6f, 0.6f, 0.6f };
	float l0_spe[] = { 0.2f, 0.2f, 0.2f };
	float l0_pos[] = { 1.0f, 2.0f, 2.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
#pragma endregion




}


void CRenderer::drawSky(void)
{
	// Store the current matrix
	glPushMatrix();

	// Enable/Disable features

	// Just in case we set all vertices to white.
	glColor4f(1, 1, 1, 1);


	// W³¹czamy teksturowanie
	glEnable(GL_TEXTURE_2D);

	// Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glTranslatef(camera->pos.x, camera->pos.y, camera->pos.z);
	glScaled(50, 50, 50);

	float m_amb[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float m_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);

#pragma region Przednia sciana
	{
		glBindTexture(GL_TEXTURE_2D, skybox.front());
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glEnd();
		glPopMatrix();
	}
#pragma endregion


#pragma region Tylna sciana
	{
		glBindTexture(GL_TEXTURE_2D, skybox.back());
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glEnd();
		glPopMatrix();
	}
#pragma endregion


#pragma region Lewa sciana
	{
		glBindTexture(GL_TEXTURE_2D, skybox.left());
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glEnd();
		glPopMatrix();
	}
#pragma endregion


#pragma region Prawa sciana
	{
		glBindTexture(GL_TEXTURE_2D, skybox.right());
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glEnd();
		glPopMatrix();
	}
#pragma endregion


#pragma region Podloga
	{
		glBindTexture(GL_TEXTURE_2D, skybox.bottom());
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glEnd();
		glPopMatrix();
	}
#pragma endregion


#pragma region Sufit
	{
		glBindTexture(GL_TEXTURE_2D, skybox.top());
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glEnd();
		glPopMatrix();
	}
#pragma endregion


	// Restore enable bits and matrix
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


void CRenderer::drawScene()
{
	drawFPS();

	setDisplayMatrices();

	setupLights();

	drawSky();

	glScaled(0.1, 0.1, 0.1);

	// Przesuniecie swiata (przeciwienstwo przesuniecia kamery).

	// Obrot kamery - aby zatrzymac ja w miejscu, nalezy zakomentowac.
	//glRotatef(frame / 2, 0.0f, 1.0f, 0.0f);


	// Rysowanie obiektow na scenie.


	/* 3rd CAMERA */
	/*
	glPushMatrix();
	glTranslatef(camera->view.x + camera->pos.x, camera->view.y + camera->pos.y, camera->view.z + camera->pos.z);
	glRotatef(-((camera->angleY * 180) / PI), 0, 1, 0);
	glRotatef(-((camera->angleX * 180) / PI), 0, 0, 1);
	glutWireCube(0.2);
	glTranslatef(-camera->view.x - camera->pos.x, -camera->view.y - camera->pos.y , -camera->view.z - camera->pos.z);
	glPopMatrix();
	*/


	glPushMatrix();
	glLineWidth(0.1);
	glTranslatef(2.7f, 2.7f, -1.3f);
	float m_amb[] = { 0.6f, 0.6f, 0.0f };
	float m_dif[] = { 0.8f, 0.8f, 0.0f };
	float m_spe[] = { 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_spe);
	glutSolidSphere(0.2, 12, 8);
	glPopMatrix();


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


