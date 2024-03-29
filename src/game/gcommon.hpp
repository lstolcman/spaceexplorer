#pragma once

#define PI 3.1415926535f

enum SKeyState
{
	KEYUP = 1,    //GLUT_UP,
	KEYDOWN = 0,    //GLUT_DOWN,
	WHEELSCROLLUP = 3,    // wheel scroll up
	WHEELSCROLLDOWN = 4,    // wheel scroll down
	HOLDWHEELSCROLLUP = 35,   // hold wheel and scroll up
	HOLDWHEELSCROLLDOWN = 36    // hold wheel and scroll down
};

enum SMouseKey
{
	LEFT_BUTTON = GLUT_LEFT_BUTTON,
	MIDDLE_BUTTON = GLUT_MIDDLE_BUTTON,
	RIGHT_BUTTON = GLUT_RIGHT_BUTTON,
};

enum SGameState
{
	PLAYING,
	WIN,
	LOOSE
};

struct SMouseState
{
	SMouseKey button;
	SKeyState state;
	int x;
	int y;
};



struct SAsteroid
{
	glm::vec3 pos;
	glm::vec3 rotationAxis;
	float rotationSpeed;
	float scale;
	float distance;
	float radiusLOD;
	bool collision;
};



struct SCamera
{
	bool  captureMouse;
	glm::vec3 pos;
	glm::vec3 view;
	glm::vec3 up;
	float speed;

	float velRX;
	float velRY;
	float velRZ;

	float velM;
	float velS;

	float angleX;
	float angleY;
	float angleZ;

	float rotX;
	float rotY;
};


struct SWindow
{
	glm::ivec2 size;
	glm::ivec2 pos;
};

struct SInputState
{
	SMouseState mouse;
	SKeyState keys[256];
	SKeyState specialKeys[256];
};

struct SData
{
	bool drawDebug;
	bool debugMode;
	bool debugInsertAsteroid;
	bool debugCollision;
	glm::fvec4 p;

	//clipping planes
	float zNear;
	float zFar;

	bool fullscreen;
	bool drawHUD;
	bool drawFPS;

	bool drawEdges;
	bool drawCollisionEdges;

	bool writeMap;

	unsigned last_fps;

	float	vehicleNearestAsteroidDistance; //distance for nearest asteroid
	float	vehicleNearestAsteroidScale;

	std::vector<SAsteroid>		*asteroids;
	unsigned					genAsteroids;

	SInputState *inputState;
	SCamera	*camera;
	SWindow *window;


	SGameState gameState;


	audiere::AudioDevicePtr		audioDevice;
};



