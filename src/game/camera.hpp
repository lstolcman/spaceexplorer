#pragma once
#include "../tools/math.hpp"
#include "gcommon.hpp"

class CCamera
{
public:

	bool  free3DMovement;
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


	CCamera();
	~CCamera();

	void cameraMove(void);
	void rotX(float);
	void rotY(float);
	void rotZ(float);
};
