#pragma once
#include "../tools/math.hpp"

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	FORWARD,
	BACKWARD
};

struct SPlayer
{
	vec3 pos;
	vec3 view;
	vec3 up;
	float speed;
	float velRX;
	float velRY;
	float velM;
	float velS;
};

enum KeyState
{
	KEYUP = 1,    //GLUT_UP,
	KEYDOWN = 0,    //GLUT_DOWN,
	WHEELSCROLLUP = 3,    // wheel scroll up
	WHEELSCROLLDOWN = 4,    // wheel scroll down
	HOLDWHEELSCROLLUP = 35,   // hold wheel and scroll up
	HOLDWHEELSCROLLDOWN = 36    // hold wheel and scroll down
};

enum MouseKey
{
	LEFT_BUTTON = GLUT_LEFT_BUTTON,
	MIDDLE_BUTTON = GLUT_MIDDLE_BUTTON,
	RIGHT_BUTTON = GLUT_RIGHT_BUTTON,

};

struct Mouse
{
	MouseKey button;
	KeyState state;
	int x;
	int y;
};




struct SCamera
{

	//bool  free3DMovement;
	bool  captureMouse;
	vec3  pos;
	vec3  view;
	vec3  up;
	float speed;

	float velRX;
	float velRY;

	float velM;
	float velS;

	float angleX;
	float angleY;
	float angleZ;
};




struct SData
{
	bool fullscreen;

	SCamera	*camera;
};


