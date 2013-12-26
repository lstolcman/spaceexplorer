#include "stdafx.hpp"
#include "input.hpp"


CInput::CInput(SCamera *camera)
{
	//init state - nothing pressed

	for (int i = 0; i < 256; i++)
	{
		inputState.keys[i]        = KEYUP;
		inputState.specialKeys[i] = KEYUP;
	}
	inputState.mouse.state = KEYUP;
	mouseSensitivity       = 0.2f;
	captureMouse           = true;
	this->camera           = camera;

}

CInput::~CInput()
{

}


void CInput::mouseButtonPress(int button, int state, int x, int y)
{
	inputState.mouse.button = (MouseKey)button;
	inputState.mouse.state  = (KeyState)state;
	inputState.mouse.x      = x;
	inputState.mouse.y      = y;

#ifdef _DEBUG
	std::cout << "mouseButtonPress: " << x << "x" << y;
	switch (state)
	{
	case KEYUP:
		std::cout << " s: UP"; break;
	case KEYDOWN:
		std::cout << " s: DOWN"; break;
	}
	;
	switch (button)
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
	}
	;
	std::cout << "\t\t\r";
#endif

}


void CInput::mouseMove(int x, int y)
{
	inputState.mouse.x = x;
	inputState.mouse.y = y;

	/*
	#ifdef _DEBUG
	std::cout << "mouseMove: " << x << "x" << y;
	switch (inputState.mouse.state)
	{
	case KEYUP:
	std::cout << " s: UP"; break;
	case KEYDOWN:
	std::cout << " s: DOWN"; break;
	};
	switch (inputState.mouse.button)
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
	/*
	#ifdef _DEBUG
	std::cout << "keyDown " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
	#endif
	*/

	switch (keyid)
	{
	case KEY_ESC:
		glutLeaveMainLoop();
		break;
	case 'm':
	case 'M':
		if (captureMouse)
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

	case 'p':
	case 'P':
			camera->latarka = !camera->latarka;
		break;

	}
}

void CInput::keyUp(unsigned char keyid, int x, int y)
{
	/*
	#ifdef _DEBUG
	std::cout << "keyUp " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
	#endif
	*/

	inputState.keys[keyid] = KEYUP;
}

void CInput::keyPress(unsigned char keyid, int x, int y)
{
	/*
	#ifdef _DEBUG
	std::cout << "keyPress " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
	#endif
	*/
	if (inputState.keys[keyid] == KEYUP)
	{
		inputState.keys[keyid] = KEYDOWN;
		keyDown(keyid, x, y);
	}

}

bool CInput::isKeyDown(int keyid)
{
	if (inputState.keys[keyid] == DOWN)
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
	/*
	#ifdef _DEBUG
	std::cout << "specialKeyDown " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
	#endif
	*/
	/*switch (keyid)
	{
	case KEY_ESC: //esc is not special key
	glutLeaveMainLoop();
	break;
	}*/
}

void CInput::specialKeyUp(int keyid, int x, int y)
{
	/*
	#ifdef _DEBUG
	std::cout << "specialKeyUp " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
	#endif
	*/
	inputState.keys[keyid] = KEYUP;
}

void CInput::specialKeyPress(int keyid, int x, int y)
{
	/*
	#ifdef _DEBUG
	std::cout << "specialKeyPress " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
	#endif
	*/
	if (!inputState.specialKeys[keyid])
	{
		inputState.specialKeys[keyid] = KEYDOWN;
		specialKeyDown(keyid, x, y);
	}
}

bool CInput::isSpecialKeyDown(int keyid)
{
	if (inputState.specialKeys[keyid] == DOWN)
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
	if (inputState.mouse.state == 1)
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
	#pragma region Ruch kamery


	//std::cout
	//	<< camera.pos.x << "x" << camera.pos.y << "x" << camera.pos.z << " "
	//	<< camera.dir.x << "x" << camera.dir.y << "x" << camera.dir.z << "\n";
	bool free3DMovement = true;
	if (captureMouse)
	{

		camera->velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - inputState.mouse.x);
		camera->velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - inputState.mouse.y);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}

	if (inputState.keys['w'] == KEYDOWN)
	{
		camera->velM = camera->speed;
	}
	if (inputState.keys['s'] == KEYDOWN)
	{
		camera->velM = -camera->speed;
	}
	if (inputState.keys['a'] == KEYDOWN)
	{
		camera->velS = -camera->speed;
	}
	if (inputState.keys['d'] == KEYDOWN)
	{
		camera->velS = camera->speed;
	}
	if (inputState.keys['q'] == KEYDOWN)
	{
		camera->velRY = -camera->speed;
	}
	if (inputState.keys['e'] == KEYDOWN)
	{
		camera->velRY = camera->speed;
	}
	if (inputState.keys['f'] == KEYDOWN)
	{
		camera->velRX = -camera->speed;
	}
	if (inputState.keys['c'] == KEYDOWN)
	{
		camera->velRX = camera->speed;
	}


	#pragma endregion

	return true;
}