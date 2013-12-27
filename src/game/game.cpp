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

	data.camera = new SCamera;
	handlers.camera   = new CCamera(data.camera);
	handlers.input    = new CInput(data.camera);
	handlers.renderer = new CRenderer(data.camera);
}


CGame::~CGame(void)
{
	delete handlers.renderer;
	delete handlers.camera;
	delete handlers.input;

	delete data.camera;
}


void CGame::Init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 360);
	glutInitWindowPosition(400, 300);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Space Explorer");



	//glutTimerFunc(1000, callbackDrawFPS, 0);
	//glutTimerFunc(15, callbackRedisplay, 0);


	//glutRedisplayFunc(callbackRedisplay);
	glutFullScreen();

	glEnable(GL_DEPTH_TEST);

	// ustawienie jakoœci renderingu punktów

	// ustawienie jakoœci renderingu wielok¹tów


	glEnable(GL_CULL_FACE); // W³¹czenie cullingu - rysowania tylko jednej strony wielok¹tów
	glCullFace(GL_BACK); // Okreœlenie, któr¹ stronê wielok¹tów chcemy ukrywaæ
	glFrontFace(GL_CCW); // Okreœlenie, jaki kierunek definicji wierzcho³ków oznacza przód wielok¹tu (GL_CCW - przeciwnie do ruchu wskazówek zegara, GL_CW - zgodnie)

	glEnable(GL_LIGHTING);


	setMouse();
	loadTextures();

	setGlutCallbacks();
	glutTimerFunc(17, callbackCaptureInput, 0);
	glutMainLoop();
}


void CGame::Update(void)
{
}


void CGame::Render(void)
{
	handlers.renderer->drawScene();
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
	gluPerspective(50.0f, (float)width / height, 0.01f, 100.0f);
}


void CGame::setGlutCallbacks(void)
{

	glutDisplayFunc(callbackRender);
	//glutIdleFunc(callbackRedisplay); //http://forum.warsztat.gd/index.php?topic=4703.0
	glutReshapeFunc(callbackReshape);


	//glutMouseFunc(callbackMouseButtonPress);
	glutMotionFunc(callbackMouseMove);
	glutPassiveMotionFunc(callbackMouseMove);

	glutKeyboardFunc(callbackKeyPress);
	glutKeyboardUpFunc(callbackKeyUp);
	glutSpecialFunc(callbackSpecialKeyPress);
	glutSpecialUpFunc(callbackSpecialKeyUp);


}


void CGame::loadTextures(void)
{
	handlers.renderer->loadTextures();
}


void CGame::setMouse(void)
{
	// Ustawienie obs³ugi myszy
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2); // Przesuniêcie kursora na œrodek ekranu

	instance->handlers.input->inputState.mouse.x = glutGet(GLUT_WINDOW_WIDTH) / 2;
	instance->handlers.input->inputState.mouse.y = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutSetCursor(GLUT_CURSOR_NONE); // Ukrycie kursora
}






void CGame::callbackRender()
{
	instance->Render();
}


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
	instance->handlers.input->mouseButtonPress(button, state, x, y);
}


void CGame::callbackMouseMove(int x, int y)
{
	instance->handlers.input->mouseMove(x, y);
}


void CGame::callbackKeyPress(unsigned char keyid, int x, int y)
{
	instance->handlers.input->keyPress(keyid, x, y);
}


void CGame::callbackKeyUp(unsigned char keyid, int x, int y)
{
	instance->handlers.input->keyUp(keyid, x, y);
}


void CGame::callbackSpecialKeyPress(int keyid, int x, int y)
{
	instance->handlers.input->specialKeyPress(keyid, x, y);
}


void CGame::callbackSpecialKeyUp(int keyid, int x, int y)
{
	instance->handlers.input->specialKeyUp(keyid, x, y);
}


void CGame::callbackCaptureInput(int id)
{

	if (instance->handlers.input->checkInput())
	{
		instance->handlers.camera->cameraMove();
	}
	glutTimerFunc(17, callbackCaptureInput, 0);

}

