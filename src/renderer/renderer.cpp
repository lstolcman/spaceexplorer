#include "stdafx.hpp"
#include "renderer.hpp"



CRenderer::CRenderer(SData *data)
{
	srand(static_cast<unsigned>(std::time(0)));
	this->data = data;

	skybox = NULL;

	fpsTimer.start();
	globalTimer.start();
	frame = 0;
	frame_old = 0;

	ang = 0;
}


CRenderer::~CRenderer()
{
	delete carrier;
	delete asteroid;
	delete worldmap;
	delete skybox;
}


bool CRenderer::loadData(void)
{
	//load skybox
	skybox = new CSkybox;
	vehicle = new CObject;
	asteroid = new CObject;
	carrier = new CObject;
	worldmap = new CWoldmap;

	skybox->load();

	vehicle->bindModel("resources/models/vehicle");
	asteroid->bindModel("resources/models/asteroid-12k");
	carrier->bindModel("resources/models/SS1");

	worldmap->loadPlayerPos(data->camera);
	worldmap->loadAsteroids(data->asteroids);

	return true;
}


void CRenderer::countFPS()
{
	if (fpsTimer.getElapsedMilliseconds() > 1000)
	{
		data->last_fps = frame - frame_old;
		frame_old = frame;
		fpsTimer.reset();
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
	//oswietlenie ambient - wszystkie wierzcho³ki
	float globalAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);


#pragma region Swiatlo
	glEnable(GL_LIGHT0);
	float l0_amb[] = { 0.4f, 0.4f, 0.4f };
	float l0_dif[] = { 0.5f, 0.5f, 0.5f };
	float l0_spe[] = { 0.2f, 0.2f, 0.2f };
	float l0_pos[] = { 6000.0f, 0.0f, -2000.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
#pragma endregion

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


void CRenderer::drawScene(void)
{
	//draw any opengl errors
	GLenum errCode;
	if ((errCode = glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGL Error: " << gluErrorString(errCode) << std::endl;

	glScalef(0.01, 0.01, 0.01);

	if (data->writeMap && data->debugMode)
	{
		data->writeMap = false;
		worldmap->writeMap(data->asteroids, data->camera);
		std::cout << "\nwrite map file\n";
	}


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
	glRotated(0 , 0, 1, 0);	//rotate +left y-axis
	glRotated(-10 , 0, 0, 1); //rotate -left x-axis
	//glutWireCube(0.2);
	glScaled(0.03, 0.03, 0.03);
	vehicle->draw();

	glTranslatef(-data->camera->view.x - data->camera->pos.x,-data->camera->view.y - data->camera->pos.y,\
					-data->camera->view.z - data->camera->pos.z);

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
	}

	glPushMatrix();
	glColor3b(0, 1, 1);
	glTranslated(1500, -128, -18);
	glRotated(90, 0, 1, 0);
	glScaled(50, 50, 50);
	carrier->draw();
	float amb[] = { 0.4, 0, 0.0, 1.0f };
	float dif[] = { 0.4, 0, 0.0, 1.0f };
	float spe[] = { 0.4, 0, 0.0, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spe);
	glRotated(ang, 1, 1, 1);
	glutWireSphere(6, 10, 10);
	glPopMatrix();



	if (data->drawEdges && data->debugMode)
		glPolygonMode(GL_FRONT, GL_LINE);


	if (data->debugInsertAsteroid && data->debugMode)
	{
		data->debugInsertAsteroid = false;
		SAsteroid *aster = new SAsteroid;
		aster->pos = data->camera->pos;
		aster->rotationAxis = glm::vec3(1, rand() % 2, rand() % 2);
		aster->scale = (rand() % 10) / 2 + 1;
		aster->rotationSpeed = (rand() % 8) / 2 + 1;
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
		glScalef(i->scale * 1000, i->scale * 1000, i->scale * 1000);
		if ((i->rotationAxis.x && i->rotationAxis.y && i->rotationAxis.z) == 0)
			glRotatef(ang*i->rotationSpeed, i->rotationAxis.x, i->rotationAxis.y, i->rotationAxis.z);

		asteroid->draw();

		if (data->drawCollisionEdges && data->debugMode && i->distance < i->scale * 80)
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
		glPopMatrix();
	}

	// Inkrementacja licznika klatek.
	frame += 1;
}





