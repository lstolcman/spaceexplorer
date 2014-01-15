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

	data = new SData;
	data->inputState = new SInputState;
	data->camera = new SCamera;
	data->window = new SWindow;
	data->zNear = 0.001f;
	data->zFar = 1000.f;

	handlers.camera = new CCamera(data);
	handlers.input = new CInput(data);
	handlers.ui = new CUI(data);
	handlers.renderer = new CRenderer(data);

	///

	data->drawDebug = false;
	data->drawFPS = true;
	data->drawHUD = false;
	data->drawEdges = false;
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
	data->last_fps = 0;

}


CGame::~CGame(void)
{
	delete handlers.renderer;
	delete handlers.camera;
	delete handlers.ui;
	delete handlers.input;

	delete data->camera;
	delete data->inputState;
	delete data;
}


void CGame::Init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 0);
	glutInitWindowSize(data->window->size.x, data->window->size.y);
	glutInitWindowPosition(data->window->pos.x, data->window->pos.y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Space Explorer");

	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		// Problem: glewInit failed, something is seriously wrong.
		//std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		MessageBox(0, (LPCSTR)glewGetErrorString(err), "GLEW Error", MB_ICONERROR | MB_OK);
		exit(1);
	}

	if (GLEW_VERSION_3_0 == false)
	{
		MessageBox(0, "To run a game, OpenGL 3.0 or higher is required", "Error", MB_ICONERROR | MB_OK);
		exit(1);
	}
	std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	if (data->fullscreen)
		glutFullScreen();



	//glutTimerFunc(1000, callbackDrawFPS, 0);
	//glutTimerFunc(15, callbackRedisplay, 0);
	//glutRedisplayFunc(callbackRedisplay);



	setMouse();
	loadData();

	glutTimerFunc(17, callbackCaptureInput, 0);
	setGlutCallbacks();
	glutMainLoop();
}


void CGame::Update(void)
{
}


void CGame::Render(void)
{
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
	gluPerspective(60.0f, (float)width / height, data->zNear, data->zFar/*0.01f, 5000.0f*/);
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
}


void CGame::loadData(void)
{
	handlers.renderer->loadData();
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


void CGame::callbackCaptureInput(int id)
{

	if (instance->handlers.input->checkInput())
	{
		instance->handlers.camera->cameraMove();
	}
	glutTimerFunc(17, callbackCaptureInput, 0);

}

