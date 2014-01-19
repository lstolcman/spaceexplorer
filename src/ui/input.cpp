#include "stdafx.hpp"
#include "input.hpp"


CInput::CInput(SData *data)
{
	this->data = data;

	//init state - nothing pressed
	for (int i = 0; i < 256; ++i)
	{
		data->inputState->keys[i] = KEYUP;
		data->inputState->specialKeys[i] = KEYUP;
	}
	data->inputState->mouse.state = KEYUP;
	mouseSensitivity = 0.031f;
	captureMouse = true;
}

CInput::~CInput()
{

}


void CInput::mouseButtonPress(int button, int state, int x, int y)
{
	data->inputState->mouse.button = (SMouseKey)button;
	data->inputState->mouse.state = (SKeyState)state;
	data->inputState->mouse.x = x;
	data->inputState->mouse.y = y;

	/*
#ifdef _DEBUG
	std::cout << "mouseButtonPress: " << x << "x" << y;
	switch (state)
	{
	case KEYUP:
		std::cout << " s: UP"; break;
	case KEYDOWN:
		std::cout << " s: DOWN"; break;
	};
	switch (button)
	{
	case LEFT_BUTTON:
		std::cout << " b: LEFT"; break;
	case MIDDLE_BUTTON:
		std::cout << " b: MIDDLE"; break;
	case RIGHT_BUTTON:
		std::cout << " b: RIGHT"; break;
	case WHEELSCROLLUP:
		std::cout << " s: WHEEL SCROLL UP"; data->camera->speed += 0.005f; break;
	case WHEELSCROLLDOWN:
		std::cout << " s: WHEEL SCROLL DOWN";  data->camera->speed -= 0.005f; break;
	case HOLDWHEELSCROLLUP:
		std::cout << " s: HOLD WHEEL SCROLL UP"; break;
	case HOLDWHEELSCROLLDOWN:
		std::cout << " s: HOLD WHEEL SCROLL DOWN"; break;
	};
	std::cout << "\t\t\r";
#endif
	*/


	if (data->inputState->mouse.state == KEYDOWN)
	{
		switch (data->inputState->mouse.button)
		{
		case LEFT_BUTTON:

			break;

		case MIDDLE_BUTTON:

			break;

		case RIGHT_BUTTON:

			break;

		case WHEELSCROLLUP:
			data->camera->speed += 1.0f;
			break;

		case WHEELSCROLLDOWN:
			data->camera->speed -= 1.0f;
			break;

		case HOLDWHEELSCROLLUP:

			break;

		case HOLDWHEELSCROLLDOWN:

			break;

		};
	}


}

void CInput::mouseMove(int x, int y)
{
	data->inputState->mouse.x = x;
	data->inputState->mouse.y = y;
	/*
#ifdef _DEBUG
	std::cout << "mouseMove: " << x << "x" << y;
	switch (data->inputState->mouse.state)
	{
	case KEYUP:
		std::cout << " s: UP"; break;
	case KEYDOWN:
		std::cout << " s: DOWN"; break;
	};
	switch (data->inputState->mouse.button)
	{
	case LEFT_BUTTON:
		std::cout << " b: LEFT"; break;
	case MIDDLE_BUTTON:
		std::cout << " b: MIDDLE"; break;
	case RIGHT_BUTTON:
		std::cout << " b: RIGHT"; break;
	case WHEELSCROLLUP:
		std::cout << " s: WHEEL SCROLL UP"; break;
	case WHEELSCROLLDOWN:
		std::cout << " s: WHEEL SCROLL DOWN"; break;
	case HOLDWHEELSCROLLUP:
		std::cout << " s: HOLD WHEEL SCROLL UP"; break;
	case HOLDWHEELSCROLLDOWN:
		std::cout << " s: HOLD WHEEL SCROLL DOWN"; break;
	};
	std::cout << "\t\t\r";
#endif
	*/

}

void CInput::keyDown(unsigned char keyid, int x, int y)
{
	
	#ifdef _DEBUG
	std::cout << "keyDown " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
	#endif
	

	switch (keyid)
	{
	case KEY_ESC:
		glutLeaveMainLoop();
		break;

	case 'a':
	case 'A':

		break;

	case 'b':
	case 'B':
		data->writeMap = true;
		break;

	case 'c':
	case 'C':

		break;

	case 'd':
	case 'D':

		break;

	case 'e':
	case 'E':

		break;

	case 'f':
	case 'F':
		break;

	case 'g':
	case 'G':

		break;

	case 'h':
	case 'H':

		break;

	case 'i':
	case 'I':

		break;

	case 'j':
	case 'J':

		break;

	case 'k':
	case 'K':
		if (data->debugMode)
		{
			data->drawCollisionEdges = !data->drawCollisionEdges;
		}
		break;

	case 'l':
	case 'L':
		break;

	case 'm':
	case 'M':
		if (captureMouse && !data->fullscreen)
		{
			captureMouse = false;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
		else
		{
			captureMouse = true;
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		break;

	case 'n':
	case 'N':
		if (data->fullscreen)
		{
			//glutReshapeWindow(data->window.size.x, data->window.size.y);
			//glutPositionWindow(data->window.pos.x, data->window.pos.y);
			glutLeaveFullScreen();
			data->fullscreen = false;
		}
		else
		{
			glutFullScreen();
			data->fullscreen = true;
			captureMouse = true;
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		break;

	case 'o':
	case 'O':

		break;

	case 'p':
	case 'P':
		break;

	case 'q':
	case 'Q':

		break;

	case 'r':
	case 'R':
		break;

	case 's':
	case 'S':

		break;

	case 't':
	case 'T':
		break;

	case 'u':
	case 'U':

		break;

	case 'v':
	case 'V':
		data->drawHUD = !data->drawHUD;
		break;

	case 'w':
	case 'W':

		break;

	case 'x':
	case 'X':

		break;

	case 'y':
	case 'Y':

		break;

	case 'z':
	case 'Z':

		break;

	case ' ':
		if (data->debugMode)
		{
			data->debugInsertAsteroid = true;
		}
		break;


	default:
		break;

	}
}

void CInput::keyUp(unsigned char keyid, int x, int y)
{
#ifdef _DEBUG
	std::cout << "keyUp " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
#endif

	data->inputState->keys[keyid] = KEYUP;

	//when shift-letter was pressed and letter was released w/o shfift - release both keys (works with a-z only!!)
	if (keyid >= 97 || keyid <= 122)
		data->inputState->keys[keyid - 32] = KEYUP;

	if (keyid >= 65 || keyid <= 90)
		data->inputState->keys[keyid + 32] = KEYUP;

}

void CInput::keyPress(unsigned char keyid, int x, int y)
{
#ifdef _DEBUG
	std::cout << "keyPress " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
#endif
	if (data->inputState->keys[keyid] == KEYUP)
	{
		data->inputState->keys[keyid] = KEYDOWN;
		keyDown(keyid, x, y);
	}

}

bool CInput::isKeyDown(int keyid)
{
	if (data->inputState->keys[keyid] == KEYDOWN)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CInput::specialKeyDown(int keyid, int x, int y)
{
	#ifdef _DEBUG
	std::cout << "specialKeyDown " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
	#endif

	switch (keyid)
	{

	case KEY_F1:
		data->drawFPS = !data->drawFPS;
		break;

	case KEY_F2:
		break;

	case KEY_F3:
		break;

	case KEY_F4:
		break;

	case KEY_F5:
		break;

	case KEY_F6:
		break;

	case KEY_F7:
		break;

	case KEY_F8:
		if (data->debugMode)
		{
			data->drawEdges = !data->drawEdges;
		}
		break;

	case KEY_F9:
		if (data->debugMode)
		{
			data->drawDebug = false;
			data->drawEdges = false;
			data->drawCollisionEdges = false;
		}
		data->debugMode = !data->debugMode;
		break;


	case KEY_F10:
		break;


	case KEY_F11:
		break;

	case KEY_F12:
		if (data->debugMode)
		{
			data->drawDebug = !data->drawDebug;
		}
		break;

	}


}

void CInput::specialKeyUp(int keyid, int x, int y)
{
	#ifdef _DEBUG
	std::cout << "specialKeyUp " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
	#endif
	data->inputState->specialKeys[keyid] = KEYUP;
}

void CInput::specialKeyPress(int keyid, int x, int y)
{

#ifdef _DEBUG
	std::cout << "specialKeyPress " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
#endif

	if (data->inputState->specialKeys[keyid] == KEYUP)
	{
		data->inputState->specialKeys[keyid] = KEYDOWN;
		specialKeyDown(keyid, x, y);
	}
}

bool CInput::isSpecialKeyDown(int keyid)
{
	if (data->inputState->specialKeys[keyid] == KEYDOWN)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CInput::isMouseButtonDown(int keyid)
{
	if (data->inputState->mouse.state == KEYUP && data->inputState->mouse.button == keyid)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CInput::checkInput()
{
	if (captureMouse)
	{
		data->camera->velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - data->inputState->mouse.x);
		data->camera->velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - data->inputState->mouse.y);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}

	if (data->inputState->keys['w'] == KEYDOWN)
	{
		data->camera->velM = data->camera->speed;
	}
	if (data->inputState->keys['s'] == KEYDOWN)
	{
		data->camera->velM = -data->camera->speed;
	}
	if (data->inputState->keys['a'] == KEYDOWN)
	{
		data->camera->velS = -data->camera->speed;
	}
	if (data->inputState->keys['d'] == KEYDOWN)
	{
		data->camera->velS = data->camera->speed;
	}
	if (data->inputState->keys['q'] == KEYDOWN)
	{
		data->camera->velRZ = -data->camera->speed;
	}
	if (data->inputState->keys['e'] == KEYDOWN)
	{
		data->camera->velRZ = data->camera->speed;
	}
	if (data->inputState->keys['f'] == KEYDOWN)
	{
		data->camera->velRX = -data->camera->speed;
	}
	if (data->inputState->keys['c'] == KEYDOWN)
	{
		data->camera->velRX = data->camera->speed;
	}

	return true;
}




