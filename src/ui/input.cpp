#include "stdafx.hpp"
#include "input.hpp"




CInput::CInput()
{
	//init state - nothing pressed

	for (int i = 0; i < 256; i++)
	{
		inputState.keys[i]			= UP;
		inputState.specialKeys[i]	= UP;
	}
	inputState.mouse.state = UP;
}

CInput::~CInput()
{

}


void CInput::mouseButtonPress(int button, int state, int x, int y)
{
	inputState.mouse.button = (MouseKey)button;
	inputState.mouse.state	= (KeyState)state;
	inputState.mouse.x		= x;
	inputState.mouse.y		= y;

#ifdef _DEBUG
	std::cout << "mouseButtonPress: " << x << "x" << y;

	switch (state)
	{
	case UP:
		std::cout << " s: UP"; break;
	case DOWN:
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

}


void CInput::mouseMove(int x, int y)
{
	inputState.mouse.x	= x;
	inputState.mouse.y	= y;

#ifdef _DEBUG
	std::cout << "mouseMove: " << x << "x" << y;
	switch (inputState.mouse.state)
	{
	case UP:
		std::cout << " s: UP"; break;
	case DOWN:
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
	}
	/*if (keyid == KEY_ESC)
	{
		glutLeaveMainLoop();
	}*/
	/*if (keyid == 'm' || keyid == 'M')   // W³¹czenie/wy³¹czenie przechwytywania kursora myszy - "uwalnia" mysz
	{
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
	}*/
	/*if (key == 'l' || key == 'L') { // "Odklejenie" kamery od pod³ogi
	free3DMovement = !free3DMovement;
	}*/
}

void CInput::keyUp(unsigned char keyid, int x, int y)
{
#ifdef _DEBUG
	std::cout << "keyUp " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
#endif

	inputState.keys[keyid] = UP;
}

void CInput::keyPress(unsigned char keyid, int x, int y)
{
#ifdef _DEBUG
	std::cout << "keyPress " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
#endif

	if (inputState.keys[keyid] == UP)
	{
		inputState.keys[keyid] = DOWN;
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
#ifdef _DEBUG
	std::cout << "specialKeyDown " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
#endif

	/*switch (keyid)
	{
	case KEY_ESC: //esc is not special key
		glutLeaveMainLoop();
		break;
	}*/
}

void CInput::specialKeyUp(int keyid, int x, int y)
{
#ifdef _DEBUG
	std::cout << "specialKeyUp " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
#endif

	inputState.keys[keyid] = UP;
}

void CInput::specialKeyPress(int keyid, int x, int y)
{
#ifdef _DEBUG
	std::cout << "specialKeyPress " << keyid << "(" << (int)keyid << ") " << x << "x" << y << "\t\t\t\r";
#endif

	if (!inputState.specialKeys[keyid])
	{
		inputState.specialKeys[keyid] = DOWN;
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

/*
void CInput::onTimer(int id)
{

    glutTimerFunc(17, CInput::onTimer, 0);

    #pragma region Ruch kamery

    if (captureMouse)
    {
        player.velRY	= -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
        player.velRX	= mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);
        glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    }


    if (keystate['w']) {
        player.velM = player.speed;
    }
    if (keystate['s']) {
        player.velM = -player.speed;
    }
    if (keystate['a']) {
        player.velS = -player.speed;
    }
    if (keystate['d']) {
        player.velS = player.speed;
    }
    if (keystate['q']) {
        player.velRY = -player.speed;
    }
    if (keystate['e']) {
        player.velRY = player.speed;
    }
    if (keystate['f']) {
        player.velRX = -player.speed;
    }
    if (keystate['c']) {
        player.velRX = player.speed;
    }

    // Obrót kamery (wsp. sferyczne):
    float	T	= acos(player.dir.y);
    float	G	= atan2(player.dir.z, player.dir.x);
    T				-= player.velRX * .03f;
    G				+= player.velRY * .03f;
    player.dir.x	= sin(T) * cos(G);
    player.dir.y	= cos(T);
    player.dir.z	= sin(T) * sin(G);

    // Wektor prostopad³y:
    vec3 per;
    per.x	= -player.dir.z;
    per.y	= 0;
    per.z	= player.dir.x;

    // Ruch przod/tyl:
    player.pos.x += player.dir.x * player.velM * .1f;
    if (free3DMovement)
    {
        player.pos.y += player.dir.y * player.velM * .1f;
    }
    else
    {
        player.pos.y = 1.0f;
    }
    player.pos.z += player.dir.z * player.velM * .1f;

    // Ruch na boki:
    player.pos.x += per.x * player.velS * .1f;
    if (free3DMovement)
    {
        player.pos.y += player.dir.y * player.velM * .1f;
    }
    else
    {
        player.pos.y = 1.0f;
    }
    player.pos.z += per.z * player.velS * .1f;

    // Inercja:
    player.velRX	/= 1.2;
    player.velRY	/= 1.2;
    player.velM		/= 1.2;
    player.velS		/= 1.2;

    #pragma endregion
}

*/
