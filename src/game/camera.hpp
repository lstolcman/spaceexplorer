#pragma once
#include "../tools/math.hpp"
#include "gcommon.hpp"

class CCamera
{
public:

	


	CCamera(SData*);
	~CCamera();

	SCamera *camera;
	void cameraMove(void);
	void rotX(float);
	void rotY(float);
	void rotZ(float);
};
