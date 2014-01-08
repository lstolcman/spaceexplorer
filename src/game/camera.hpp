#pragma once
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
