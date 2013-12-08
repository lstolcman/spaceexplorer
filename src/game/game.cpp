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

	camera   = new CCamera;
	input    = new CInput(camera);
	renderer = new CRenderer(camera);
}


CGame::~CGame(void)
{
	delete renderer;
	delete camera;
	delete input;
}


void CGame::Init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 360);
	glutInitWindowPosition(400, 300);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Space Explorer");


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

	glutTimerFunc(17, callbackCaptureInput, 0);

	//glutTimerFunc(1000, callbackDrawFPS, 0);
	//glutTimerFunc(15, callbackRedisplay, 0);


	//glutRedisplayFunc(callbackRedisplay);
	//glutFullScreen();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE); // W³¹czenie cullingu - rysowania tylko jednej strony wielok¹tów
	glCullFace(GL_BACK); // Okreœlenie, któr¹ stronê wielok¹tów chcemy ukrywaæ
	glFrontFace(GL_CCW); // Okreœlenie, jaki kierunek definicji wierzcho³ków oznacza przód wielok¹tu (GL_CCW - przeciwnie do ruchu wskazówek zegara, GL_CW - zgodnie)

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);




	// Ustawienie obs³ugi myszy
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2); // Przesuniêcie kursora na œrodek ekranu

	instance->input->inputState.mouse.x = glutGet(GLUT_WINDOW_WIDTH) / 2;
	instance->input->inputState.mouse.y = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutSetCursor(GLUT_CURSOR_NONE); // Ukrycie kursora



	glutMainLoop();
}


void CGame::Update(void)
{
}


void CGame::Render(void)
{
	renderer->drawScene(); //instance->player->player);
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
	gluPerspective(50.0f, (float)width / height, 0.01f, 100.0f);
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

void CGame::callbackCaptureInput(int id)
{

	if (instance->input->checkInput())
	{
		instance->camera->cameraMove();
	}
	glutTimerFunc(17, callbackCaptureInput, 0);

}
