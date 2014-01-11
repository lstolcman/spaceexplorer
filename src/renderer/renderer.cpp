#include "stdafx.hpp"
#include "renderer.hpp"



CRenderer::CRenderer(SData *data)
{
	this->data = data;

	skybox = NULL;
	//phong = NULL;

	time.start();
	frame = 0;
	frame_old = 0;

}


CRenderer::~CRenderer()
{
	delete skybox;
}


bool CRenderer::loadData(void)
{
	//load data
	skybox = new CSkybox;
	skybox->load();
	object = new CObject;
	object->bindModel("resources/models/vehicle");

	//compile shaders

	/*
	phong = new CShader;
	phong->loadShader("phong");
	phong->compileShader();
	tex = new CShader;
	tex->loadShader("tex");
	tex->compileShader();
	*/



	return true;
}


void CRenderer::countFPS()
{
	if (time.getElapsedMilliseconds() > 1000)
	{
		data->last_fps = frame - frame_old;
		frame_old = frame;
		time.start(); //reset timer to 0
	}
}


void CRenderer::setDisplayMatrices(void)
{
	glPolygonMode(GL_FRONT, GL_FILL);

	glEnable(GL_NORMALIZE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); // W³¹czenie cullingu - rysowania tylko jednej strony wielok¹tów
	glCullFace(GL_BACK); // Okreœlenie, któr¹ stronê wielok¹tów chcemy ukrywaæ
	glFrontFace(GL_CCW); // Okreœlenie, jaki kierunek definicji wierzcho³ków oznacza przód wielok¹tu (GL_CCW - przeciwnie do ruchu wskazówek zegara, GL_CW - zgodnie)

	glEnable(GL_LIGHTING);
	// Wyczysc zawartosc bufora koloru i glebokosci.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Wybor macierzy, ktora od tej pory bedziemy modyfikowac
	// - macierz Modelu/Widoku.
	glMatrixMode(GL_MODELVIEW);

	// Zaladowanie macierzy jednostkowej.
	glLoadIdentity();

	gluLookAt(
		data->camera->pos.x, data->camera->pos.y, data->camera->pos.z,
		data->camera->pos.x + data->camera->view.x, data->camera->pos.y + data->camera->view.y, data->camera->pos.z + data->camera->view.z,
		data->camera->up.x, data->camera->up.y, data->camera->up.z
		);

}


void CRenderer::setupLights(void)
{
	//phong->useShader();
//	tex->useShader();
	//oswietlenie ambient - wszystkie wierzcho³ki
	float globalAmbient[4] = { 0.30f, 0.30f, 0.30f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);



#pragma region Swiatlo
	glEnable(GL_LIGHT0);
	float l0_amb[] = { 0.2f, 0.2f, 0.2f };
	float l0_dif[] = { 0.6f, 0.6f, 0.6f };
	float l0_spe[] = { 0.2f, 0.2f, 0.2f };
	float l0_pos[] = { 6000.0f, 0.0f, -2000.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
#pragma endregion

/*
	if (data->debugMode)
	{
		if (data->flash)
		{
			glEnable(GL_LIGHT0);
			float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
			float l0_dif[] = { 0.4f, 0.4f, 0.4f, 1.0f };
			float l0_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			//float l0_pos[] = { 2.7f, 2.7f, -1.3f, 1.0f };
			//float l0_dir[] = { -0.9f, -0.3f, 1.3f};
			float l0_pos[] = { data->camera->pos.x, data->camera->pos.y, data->camera->pos.z, 1.0f };
			float l0_dir[] = { data->camera->view.x, data->camera->view.y, data->camera->view.z };
			glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
			glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
			glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0_dir);
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 25.0f);
			glDisable(GL_LIGHT0);
		}
	}
	*/
}


void CRenderer::drawSky(void)
{
	glPushMatrix();
	float ambientSky[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientSky);
	// Just in case we set all vertices to white.
	glColor4f(1, 1, 1, 1);


	// W³¹czamy teksturowanie
	// Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTranslatef(data->camera->pos.x, data->camera->pos.y, data->camera->pos.z);
	glScaled(200, 200, 200);

	skybox->draw();
	glPopMatrix();
}


void CRenderer::drawScene()
{

	countFPS();

	setDisplayMatrices();

	drawSky();

	setupLights();




	glScaled(0.01, 0.01, 0.01);

	if (data->drawEdges)
		glPolygonMode(GL_FRONT, GL_LINE);



	// Przesuniecie swiata (przeciwienstwo przesuniecia kamery).
	// Obrot kamery - aby zatrzymac ja w miejscu, nalezy zakomentowac.
	//glRotatef(frame / 2, 0.0f, 1.0f, 0.0f);


	// Rysowanie obiektow na scenie.



	glPushMatrix();
	glTranslatef(0, -10, 3);
	glRotatef(90, 0, 1, 0);
	glTranslatef(data->camera->pos.x, data->camera->pos.y, data->camera->pos.z);
	object->draw();
	glPopMatrix();


	/* 3rd CAMERA */
	/*
	glPushMatrix();
	glTranslatef(data->camera->view.x + data->camera->pos.x, data->camera->view.y + data->camera->pos.y, data->camera->view.z + data->camera->pos.z);
	glRotatef(-((data->camera->angleY * 180) / PI), 0, 1, 0);
	glRotatef(-((data->camera->angleX * 180) / PI), 0, 0, 1);
	glutWireCube(0.2);
	glTranslatef(-data->camera->view.x - data->camera->pos.x, -data->camera->view.y - data->camera->pos.y , -data->camera->view.z - data->camera->pos.z);
	glPopMatrix();
	*/



	glPushMatrix();
	glLineWidth(0.1f);
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


	{
		//reset light
		float amb[] = { 1.0f, 1.0f, 1.0f };
		float dif[] = { 0.0f, 0.0f, 0.0f };
		float spe[] = { 0.0f, 0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	}




	// Inkrementacja licznika klatek.
	frame += 1;
}


