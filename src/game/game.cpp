#include "stdafx.hpp"
#include "game.hpp"


/*
petla gry:
{
//events:

//logic:

//rendering: world, skydome/box,
}
*/

CGame *CGame::instance = NULL;

CGame::CGame(void)
{
	CGame::instance = this;
	timexx.start();
	frame       = 0;
	frameold    = 0;

}


CGame::~CGame(void)
{
}


void CGame::Init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Game");
	glutDisplayFunc(callbackRender);
	glutReshapeFunc(callbackReshape);
	glEnable(GL_DEPTH_TEST);
	//glutSetWindowTitle("dfgdfgs");
	//glutTimerFunc(1000, callbackDrawFPS, 0);
	//glutIdleFunc(callbackRedisplay);
	//glutRedisplayFunc(callbackRedisplay);
	glutMainLoop();
}


void CGame::Update(void)
{
}


void CGame::Render(void)
{
	static int f = 0;

	if ((int)frame % 2 == 0)
	{
		f += 1;
	}
	if (f > 100)
	{
		f = 0;
	}

	//std::cout << "f=" << f << "\r\n";
	// Wyczysc zawartosc bufora koloru i glebokosci.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Wybor macierzy, ktora od tej pory bedziemy modyfikowac
	// - macierz Modelu/Widoku.
	glMatrixMode(GL_MODELVIEW);

	// Zaladowanie macierzy jednostkowej.
	glLoadIdentity();

	// Przesuniecie swiata (przeciwienstwo przesuniecia kamery).
	glTranslatef(0.0f, 0.0f, -20.0f);

	// Obrot kamery - aby zatrzymac ja w miejscu, nalezy zakomentowac.
	glRotatef(frame / 4, 0.0f, 1.0f, 0.0f);


	// Rysowanie obiektow na scenie.
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidCube(5);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(5.0f, 2.0f, 0.0f);
	glutWireSphere(2, 12, 6);
	glPopMatrix();



	// Jesli instrukcje w danej implementacji OpenGL byly buforowane,
	// w tym momencie bufor zostanie oprozniony a instrukcje wykonane.
	glFlush();

	// Zamien front-buffer z back-bufferem (double buffering).
	glutSwapBuffers();


	instance->drawFPS(1);

	// Inkrementacja licznika klatek.
	frame += 1.0;


}


void CGame::callbackRender()
{
	instance->Render();
}

void CGame::Reshape(int width, int height)
{
	// Wybor macierzy - macierz Projekcji.
	glMatrixMode(GL_PROJECTION);

	// Zaladowanie macierzy jednostkowej.
	glLoadIdentity();

	// Okreslenie obszaru renderowania - caly obszar okna.
	glViewport(0, 0, width, height);

	// Chcemy uzyc kamery perspektywicznej o kacie widzenia 60 stopni
	// i zasiegu renderowania 0.01-100.0 jednostek.
	gluPerspective(60.0f, (float) width / height, 0.01f, 100.0f);
}

void CGame::callbackReshape(int width, int height)
{
	instance->Reshape(width, height);
}


void CGame::drawFPS(int id)
{
	//std::cout << "elapsedmsL:"<< instance->timexx.getElapsedMilliseconds()<<"\r";
	if (instance->timexx.getElapsedMilliseconds() > 1000)
	{

		std::stringstream title;
		title
		    << "FPS: " << static_cast<int>(instance->frame - instance->frameold)
		    << "   frames:" << instance->frame;
		std::cout
		    << "old:" << instance->frameold
		    << " new:" << instance->frame
		    << " minus:" << instance->frame - instance->frameold
		    << "\r";
		instance->frameold = instance->frame;
		glutSetWindowTitle(title.str().c_str());
		instance->timexx.start();
	}
}


void CGame::callbackDrawFPS(int id)
{
	instance->drawFPS(id);
}

void CGame::callbackRedisplay(void)
{
	glutPostRedisplay();
}
