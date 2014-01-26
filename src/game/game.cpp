#include "stdafx.hpp"
#include "game.hpp"


/*

game loop:
{
//events:
input keyboard
input mouse

//logic:
collisions
menu-game/in-game/end-game

//rendering:
world
skydome
vehicle
}

*/

CGame *CGame::instance = NULL;

CGame::CGame(void)
{
	CGame::instance = this;

	data = new SData;
	data->inputState = new SInputState;
	data->camera = new SCamera;
	data->window = new SWindow;
	data->asteroids = new std::vector<SAsteroid>;

	handlers.camera = new CCamera(data);
	handlers.input = new CInput(data);
	handlers.renderer = new CRenderer(data);
	handlers.ui = new CUI(data);
	handlers.logic = new CLogic(data);

	///

	data->drawDebug = true;
	data->debugInsertAsteroid = false;
	data->debugCollision = false;
	data->drawFPS = true;
	data->drawHUD = true;
	data->drawEdges = false;
	data->drawCollisionEdges = false;
#ifdef _DEBUG
	data->fullscreen = false;
	data->debugMode = true;
#else
	data->fullscreen = true;
	data->debugMode = false;
#endif

	data->window->pos.x = 400;
	data->window->pos.y = 300;
	data->window->size.x = 640;
	data->window->size.y = 360;

	data->zNear = 0.001f;
	data->zFar = 4000.f;

	data->last_fps = 0;
	data->genAsteroids = 0;

	data->vehicleNearestAsteroidDistance = 10000.0f;
	data->vehicleNearestAsteroidScale = 1.0f;

	data->writeMap = false;
	data->gameState = PLAYING;
}


CGame::~CGame(void)
{
	delete handlers.renderer;
	delete handlers.camera;
	delete handlers.ui;
	delete handlers.input;
	delete handlers.logic;

	delete data->asteroids;
	delete data->camera;
	delete data->inputState;
	delete data->window;
	delete data;
}


void CGame::Init(int argc, char **argv)
{
	srand(time(0));

	glutInit(&argc, argv);
	glutInitContextVersion(3, 0);

	//if (data->fullscreen)
	//{
	//glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	//glutInitWindowPosition(0, 0);
	//}
	//else
	//{
	glutInitWindowSize(1, 1);
	glutInitWindowPosition(1, 1);
	//glutInitWindowSize(data->window->size.x, data->window->size.y);
	//glutInitWindowPosition(data->window->pos.x, data->window->pos.y);
	//}

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Space Explorer");

	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		MessageBox(0, (LPCSTR)glewGetErrorString(err), "GLEW Error", MB_ICONERROR | MB_OK);
		exit(1);
	}

	if (GLEW_VERSION_3_0 == false)
	{
		MessageBox(0, "To run a game, OpenGL 3.0 or higher is required", "Error", MB_ICONERROR | MB_OK);
		exit(1);
	}
	std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;


	data->audioDevice = audiere::OpenDevice();


	//glutTimerFunc(1000, callbackDrawFPS, 0);
	//glutTimerFunc(15, callbackRedisplay, 0);
	//glutRedisplayFunc(callbackRedisplay);

	setMouse();
	loadData();

	setGlutCallbacks();

	glutFullScreen();

	glutMainLoop();
}


void CGame::Update(void)
{
	if (!data->debugMode)
		handlers.logic->playSounds();

	if (instance->handlers.input->checkInput())
	{
		instance->handlers.camera->cameraMove();
	}
	handlers.logic->detectCollision();
}


void CGame::Render(void)
{
	if (data->gameState == PLAYING)
		handlers.renderer->drawScene();

	handlers.ui->drawUI();

	// Zamien front-buffer z back-bufferem (double buffering).
	glutSwapBuffers();

	// Jesli instrukcje w danej implementacji OpenGL byly buforowane,
	// w tym momencie bufor zostanie oprozniony a instrukcje wykonane.
	glFlush();

	// Nakaz wyswietlic kolejna klatke.
	glutPostRedisplay();
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
	gluPerspective(60.0f, (float)width / height, data->zNear, data->zFar);
}


void CGame::setGlutCallbacks(void)
{
	glutDisplayFunc(callbackRender);
	//glutIdleFunc(callbackRedisplay); //http://forum.warsztat.gd/index.php?topic=4703.0
	glutReshapeFunc(callbackReshape);

	glutMouseFunc(callbackMouseButtonPress);
	glutMotionFunc(callbackMouseMove);
	glutPassiveMotionFunc(callbackMouseMove);

	glutKeyboardFunc(callbackKeyPress);
	glutKeyboardUpFunc(callbackKeyUp);
	glutSpecialFunc(callbackSpecialKeyPress);
	glutSpecialUpFunc(callbackSpecialKeyUp);


	glutTimerFunc(17, callbackUpdate, 0);

}


void CGame::loadData(void)
{
	handlers.renderer->loadData();

	if (!data->debugMode)
		handlers.logic->loadSounds();

	handlers.logic->generateAsteroids();
	handlers.ui->loadUIData();
}


void CGame::setMouse(void)
{
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	data->inputState->mouse.x = glutGet(GLUT_WINDOW_WIDTH) / 2;
	data->inputState->mouse.y = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutSetCursor(GLUT_CURSOR_NONE);
}



void CGame::callbackRender()
{
	instance->Render();
}


void CGame::callbackReshape(int width, int height)
{
	instance->Reshape(width, height);
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


void CGame::callbackUpdate(int id)
{

	instance->Update();
	glutTimerFunc(17, callbackUpdate, 0);

}





