#include "stdafx.hpp"
#include "renderer.hpp"



CRenderer::CRenderer(SData *data)
{
	srand(static_cast<unsigned>(std::time(0)));
	this->data = data;


	skybox = NULL;
	//phong = NULL;

	fpsTimer.start();
	globalTimer.start();
	frame = 0;
	frame_old = 0;



	ang = 0;
}


CRenderer::~CRenderer()
{
	delete worldmap;
	delete skybox;
}


bool CRenderer::loadData(void)
{
	//load skybox
	skybox = new CSkybox;
	skybox->load();
	vehicle = new CObject;

	vehicle->bindModel("resources/models/vehicle");
	a_12k_tris = new CObject;
	a_12k_tris->bindModel("resources/models/asteroid-12k");
	a_6k_tris = new CObject;
	a_2k_tris = new CObject;
	a_60_tris = new CObject;
	a_6k_tris->bindModel("resources/models/asteroid-6k");
	a_2k_tris->bindModel("resources/models/asteroid-2k");
	a_60_tris->bindModel("resources/models/asteroid-60");


	worldmap = new CWoldmap;

	worldmap->loadPlayerPos(data->camera);
	worldmap->loadAsteroids(data->asteroids);



	for (unsigned i = 0; i < 500; ++i)
	{
	SAsteroid *aster = new SAsteroid;
	aster->pos = glm::fvec3(rng(-300, 300), rng(-300, 300), rng(-300, 300));

	//aster->rotationAxis = glm::fvec3(rng("nz", -1, 1), rng("nz", -1, 1), rng("nz", -1, 1));// rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
	aster->rotationAxis = glm::vec3((rand() % 2), (rand() % 2), (rand() % 2));
	//aster->rotationAxis = glm::fvec3(1, 0, 0);
	float scale = ( rand() % 100 / 100)+1000;

	//aster->scale = glm::fvec3(scale + rand() % 20 / 5, scale + rand() % 20 / 5, scale + rand() % 20 / 5);
	aster->scale = 1.0;
	//aster->scale = glm::fvec3(1, 1, 1);
	aster->rotationSpeed = rand() % 2 == 0 ? (rand() % 1000 / 1000.0 ) : -(rand() % 1000 / 1000.0 );
	aster->distance = 0;
	data->asteroids->push_back(*aster);
	}



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
	if (fpsTimer.getElapsedMilliseconds() > 1000)
	{
		data->last_fps = frame - frame_old;
		frame_old = frame;
		fpsTimer.reset(); //reset timer to 0
	}

	if (globalTimer.getElapsedMilliseconds() > 3)
	{
		globalTimer.reset();
		if (ang > 360)
			ang = 0;
		ang += (GLfloat)0.2;
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
	//float globalAmbient[4] = { 0.40f, 0.40f, 0.40f, 1.0f };
	float globalAmbient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
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
	//if (data->flash)
	{
	glEnable(GL_LIGHT1);
	float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float l0_dif[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	float l0_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//float l0_pos[] = { 2.7f, 2.7f, -1.3f, 1.0f };
	//float l0_dir[] = { -0.9f, -0.3f, 1.3f};
	float l0_pos[] = { data->camera->pos.x, data->camera->pos.y, data->camera->pos.z, 1.0f };
	float l0_dir[] = { data->camera->view.x, data->camera->view.y, data->camera->view.z };
	glLightfv(GL_LIGHT1, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT1, GL_POSITION, l0_pos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l0_dir);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0f);
	glDisable(GL_LIGHT1);
	}
	}
	*/

}


void CRenderer::drawSky(void)
{
	glPushMatrix();
	float ambientSky[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientSky);
	// Just in case we set all vertices to white.
	glColor4f(1, 1, 1, 1);


	// W³¹czamy teksturowanie
	// Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTranslatef(data->camera->pos.x, data->camera->pos.y, data->camera->pos.z);
	//	glScaled(2500, 2500, 2500);
	glScaled(data->zFar / 2, data->zFar / 2, data->zFar / 2);

	skybox->draw();
	glPopMatrix();
}


void CRenderer::drawScene()
{
	//draw any opengl errors
	GLenum errCode;
	if ((errCode = glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGL Error: " << gluErrorString(errCode) << std::endl;

	countFPS();

	setDisplayMatrices();

	drawSky();

	setupLights();


	/* 3rd CAMERA */
	/* DO NOT PUT THE PROCEDURE BEFORE SCALING THE ENVIRONMENT */

	glPushMatrix();
	glTranslatef(data->camera->view.x + data->camera->pos.x, data->camera->view.y + data->camera->pos.y, data->camera->view.z + data->camera->pos.z);
	glRotatef(-((data->camera->angleY * 180) / PI), 0, 1, 0);
	glRotatef(-((data->camera->angleX * 180) / PI), 0, 0, 1);
	glRotatef(180, 1, 0, 0);
	glRotatef(90, 0, 0, 1);

	//main vehicle rotation procedure
	//factors are[according to opengl xyz spec.]
	//glTranslatef(Z, Y, -X) 
	//glTranslatef(0.6, 0.0, 0.0);
	glRotated(0, 1, 0, 0); //rotate +left z-axis
	glRotated(0, 0, 1, 0);	//rotate +left y-axis
	glRotated(-10, 0, 0, 1); //rotate -left x-axis
	//glutWireCube(0.2);
	glScaled(0.03, 0.03, 0.03);
	vehicle->draw();

	/*glPushMatrix();
	float amb[] = { 0, 0.5, 0, 1.0f };
	float dif[] = { 0, 0.5, 0, 1.0f };
	float spe[] = { 0, 0.5, 0, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex3f(0, 20, 0);
	glVertex3f(0, -20, 0);
	glEnd();
	glPopMatrix();
	*/

	glTranslatef(-data->camera->view.x - data->camera->pos.x, -data->camera->view.y - data->camera->pos.y, -data->camera->view.z - data->camera->pos.z);
	glPopMatrix();

	if (data->drawCollisionEdges && data->debugMode)
	{
		float amb[] = { 0, 0, 0.5, 1.0f };
		float dif[] = { 0, 0, 0.5, 1.0f };
		float spe[] = { 0, 0, 0.5, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
		//glScaled(1, 0.2, 1);
		glPushMatrix();
		glTranslatef(data->camera->view.x + data->camera->pos.x, data->camera->view.y + data->camera->pos.y, data->camera->view.z + data->camera->pos.z);
		glutWireSphere(0.5, 20, 20);
		glPopMatrix();

		/*
		glPushMatrix();
		glTranslatef(data->camera->view.x + data->camera->pos.x, data->camera->view.y + data->camera->pos.y, data->camera->view.z + data->camera->pos.z);
		glutWireSphere(0.4, 15, 15);
		glPopMatrix();
		*/

	}








	/* 3rd CAMERA end */


	/*
	//bounding sphere from player-pos to vehicle-pos
	glPushMatrix();
	glTranslatef(data->camera->view.x + data->camera->pos.x, data->camera->view.y + data->camera->pos.y, data->camera->view.z + data->camera->pos.z);
	glRotatef(-((data->camera->angleY * 180) / PI), 0, 1, 0);
	glRotatef(-((data->camera->angleX * 180) / PI), 0, 0, 1);

	//main vehicle rotation procedure
	//factors are[according to opengl xyz spec.]
	//glTranslatef(Z, Y, -X)
	glTranslatef(0.0, -0.7, 0.0);
	//glutWireCube(0.2);
	//glScaled(0.01, 0.01, 0.01);
	glutWireSphere(0.2, 15, 15);
	glPopMatrix();
	*/



	if (data->drawEdges && data->debugMode)
		glPolygonMode(GL_FRONT, GL_LINE);



	// Przesuniecie swiata (przeciwienstwo przesuniecia kamery).
	// Obrot kamery - aby zatrzymac ja w miejscu, nalezy zakomentowac.
	//glRotatef(frame / 2, 0.0f, 1.0f, 0.0f);


	// Rysowanie obiektow na scenie.



	/*glPushMatrix();
	glTranslatef(0, -10, 3);
	glRotatef(90, 0, 1, 0);
	vehicle->draw();
	glPopMatrix();
	*/

	if (data->debugInsertAsteroid && data->debugMode)
	{

		data->debugInsertAsteroid = false;

		SAsteroid *aster = new SAsteroid;
		aster->pos = data->camera->pos;

		aster->rotationAxis = glm::vec3(1, 0, 0);
		aster->scale = 1.0;
		aster->rotationSpeed = 1;
		aster->distance = 0;
		data->asteroids->push_back(*aster);


		std::stringstream s;

		s << "insert aster." << data->camera->pos.x << "x" << data->camera->pos.y << "x" << data->camera->pos.z;

		std::cout << s.str() << std::endl;
	}

	glScaled(0.001, 0.001, 0.001);

	for (std::vector<SAsteroid>::iterator i = data->asteroids->begin(); i != data->asteroids->end(); i++)
	{
		glPushMatrix();
		glTranslatef(i->pos.x * 1000, i->pos.y * 1000, i->pos.z * 1000);
		//glRotatef(ang, i->rotation.x, i->rotation.y, i->rotation.z);
		//glScalef(i->scale.x * 100, i->scale.y * 100, i->scale.z * 100);
		glScalef(i->scale * 1000, i->scale * 1000, i->scale * 1000);
		if ((i->rotationAxis.x && i->rotationAxis.y && i->rotationAxis.z) == 0)
			glRotatef(ang*i->rotationSpeed, i->rotationAxis.x, i->rotationAxis.y, i->rotationAxis.z);


		//level of detail
		if ((i->distance - i->radiusLOD) < 50)
			a_12k_tris->draw();
		else if ((i->distance - i->radiusLOD) < 100)
			a_6k_tris->draw();
		else if ((i->distance - i->radiusLOD) < 200)
			a_2k_tris->draw();
		else 
			a_60_tris->draw();



		if (data->drawCollisionEdges && data->debugMode)
		{

			glPushMatrix();
			float amb[] = { 0, 0.5, 0, 1.0f };
			float dif[] = { 0, 0.5, 0, 1.0f };
			float spe[] = { 0, 0.5, 0, 1.0f };
			glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
			glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
			glutWireSphere(12, 20, 20);
			glPopMatrix();
		}



		/*
		glPushMatrix();
		float amb[] = { 0, 0.5, 0, 1.0f };
		float dif[] = { 0, 0.5, 0, 1.0f };
		float spe[] = { 0, 0.5, 0, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
		glLineWidth(5);
		glBegin(GL_LINES);
		glVertex3f(-14,0,0);
		glVertex3f(14,0,0);
		glEnd();
		glPopMatrix();
		*/

		glPopMatrix();
	}





	/*

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



	*/

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


