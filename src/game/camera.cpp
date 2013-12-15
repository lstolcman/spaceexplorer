#include "stdafx.hpp"
#include "camera.hpp"



CCamera::CCamera()
{
	free3DMovement = true;
	captureMouse   = true;

	speed = 0.3f;

	pos.x = 0.0f;
	pos.y = 2.0f;
	pos.z = 0.0f;

	view.x = 1.0f;
	view.y = 0.0f;
	view.z = 0.0f;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	velM  = 0.0f;
	velRX = 0.0f;
	velRY = 0.0f;
	velS  = 0.0f;

}


CCamera::~CCamera()
{

}


void CCamera::cameraMove(void)
{

	//Obrót kamery (wsp. sferyczne):
	float T = acos(view.y);
	float G = atan2(view.z, view.x);
	T -= velRX * .03f;
	G += velRY * .03f;

	if (T < 3.14 && T > 0.01)
	{

		view.x = sin(T) * cos(G);
		view.y = cos(T);
		view.z = sin(T) * sin(G);
	}



	std::cout << std::setprecision(3) << "B"
	          << pos.x << "x" << pos.y << "x" << pos.z << " "
	          << view.x << "x" << view.y << "x" << view.z << "\tvelRX:" << velRX << "\tvelRY:" << velRY << "\t\r";




	// Wektor prostopad³y:
	vec3 per;
	per.x = -view.z;
	per.y = 0;
	per.z = view.x;

	// Ruch przod/tyl:

	pos.x += view.x * velM * .1f;
	if (!free3DMovement)
	{
		pos.y += view.y * velM * .1f;
	}
	else
	{
		pos.y = 1.0f;
	}
	pos.z += view.z * velM * .1f;

	// Ruch na boki:
	pos.x += per.x * velS * .1f;
	if (!free3DMovement)
	{
		pos.y += view.y * velM * .1f;
	}
	else
	{
		pos.y = 1.0f;
	}
	pos.z += per.z * velS * .1f;
	// Inercja:


	velRX /= 2.2;
	velRY /= 2.2;
	velM  /= 2.2;
	velS  /= 2.2;


}


void changeSpeed(float speed)
{

}


void changePitch(float degrees)
{

}


void changeRoll(float degrees)
{

}
