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

	input		= new CInput;
	player		= new CPlayer;
	renderer	= new CRenderer;

	renderer->playerGetCoordinates(player->playerCoordinates());
}


CGame::~CGame(void)
{
	delete renderer;
	delete player;
	delete input;

}


void CGame::Init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 360);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Game");


	glutDisplayFunc(callbackRender);
	glutReshapeFunc(callbackReshape);


	glutMouseFunc(callbackMouseButtonPress);
	glutMotionFunc(callbackMouseMove);

	glutKeyboardFunc(callbackKeyPress);
	glutKeyboardUpFunc(callbackKeyUp);
	glutSpecialFunc(callbackSpecialKeyPress);
	glutSpecialUpFunc(callbackSpecialKeyUp);
	glutSetWindowTitle("dfgdfgs");
	//glutTimerFunc(1000, callbackDrawFPS, 0);
	//glutTimerFunc(15, callbackRedisplay, 0);
	//glutIdleFunc(callbackRedisplay);
	glEnable(GL_DEPTH_TEST);
	//glutRedisplayFunc(callbackRedisplay);
	glutMainLoop();
}


void CGame::Update(void)
{
}


void CGame::Render(void)
{

	renderer->drawScene();

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
	gluPerspective(50.0f, (float) width / height, 0.01f, 100.0f);
}


/*
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
*/

void CGame::callbackReshape(int width, int height)
{
	instance->Reshape(width, height);
}


void CGame::callbackDrawFPS(int id)
{
//	instance->drawFPS(id);
}

void CGame::callbackRedisplay(void)
{
	glutPostRedisplay();
}


void CGame::callbackMouseButtonPress(int button, int state, int x, int y)
{
	instance->input->mouseButtonPress(button, state, x, y);
}


void CGame::callbackMouseMove(int x, int y)
{
	instance->input->mouseMove(x, y);
}


void CGame::callbackKeyPress(unsigned char keyid, int x, int y)
{
	instance->input->keyPress(keyid, x, y);
}


void CGame::callbackKeyUp(unsigned char keyid, int x, int y)
{
	instance->input->keyUp(keyid, x, y);
}


void CGame::callbackSpecialKeyPress(int keyid, int x, int y)
{
	instance->input->specialKeyPress(keyid, x, y);
}


void CGame::callbackSpecialKeyUp(int keyid, int x, int y)
{
	instance->input->specialKeyUp(keyid, x, y);
}
