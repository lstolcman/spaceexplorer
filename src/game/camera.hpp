#pragma once
#include "../tools/math.hpp"
#include "gcommon.hpp"

class CCamera
{
	//Fields:
private:
	SData *data;
public:

	//Members:
private:

public:
	CCamera(SData*);
	~CCamera();

	void cameraMove(void);
	void rotX(float);
	void rotY(float);
	void rotZ(float);
};
