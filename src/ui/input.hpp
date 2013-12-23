#pragma once
#include "../game/gcommon.hpp"
#include "../game/camera.hpp"

//additional mouse state definitions
#define KEY_F1          GLUT_KEY_F1
#define KEY_F2          GLUT_KEY_F2
#define KEY_F3          GLUT_KEY_F3
#define KEY_F4          GLUT_KEY_F4
#define KEY_F5          GLUT_KEY_F5
#define KEY_F6          GLUT_KEY_F6
#define KEY_F7          GLUT_KEY_F7
#define KEY_F8          GLUT_KEY_F8
#define KEY_F9          GLUT_KEY_F9
#define KEY_F10         GLUT_KEY_F10
#define KEY_F11         GLUT_KEY_F11
#define KEY_F12         GLUT_KEY_F12
#define KEY_LEFT        GLUT_KEY_LEFT
#define KEY_UP          GLUT_KEY_UP
#define KEY_RIGHT       GLUT_KEY_RIGHT
#define KEY_DOWN        GLUT_KEY_DOWN
#define KEY_PAGE_UP     GLUT_KEY_PAGE_UP
#define KEY_PAGE_DOWN   GLUT_KEY_PAGE_DOWN
#define KEY_HOME        GLUT_KEY_HOME
#define KEY_END         GLUT_KEY_END
#define KEY_INSERT      GLUT_KEY_INSERT
#define KEY_ESC         27


class CInput
{
	//Fields:
private:
	float mouseSensitivity;
	bool  captureMouse;


public:


	//Members:
private:

public:
	struct //Input
	{
		Mouse mouse;
		KeyState keys[256];
		KeyState specialKeys[256];
	} inputState;

	SCamera *camera;

	CInput(SCamera*);
	~CInput();

	void        mouseButtonPress(int, int, int, int);
	void        mouseMove(int, int);
	void        keyDown(unsigned char, int, int);
	void        keyUp(unsigned char, int, int);
	void        keyPress(unsigned char, int, int);
	void        specialKeyDown(int, int, int);
	void        specialKeyUp(int, int, int);
	void        specialKeyPress(int, int, int);
	bool        isKeyDown(int);
	bool        isSpecialKeyDown(int);
	bool        isMouseButtonDown(int);
	bool        checkInput();




};
