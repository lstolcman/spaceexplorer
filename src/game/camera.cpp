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


	angleX = 0.0;
	angleY = 0.0;
	angleZ = 0.0;



	latarka = false;

}


CCamera::~CCamera()
{

}


void CCamera::cameraMove(void)
{

	//Obrót kamery (wsp. sferyczne):
	angleX = acos(view.y);
	angleY = atan2(view.z, view.x);
	angleX -= velRX * .03f;
	angleY += velRY * .03f;



	if (angleX < 3.14 && angleX > 0.01)
	{

		view.x = sin(angleX) * cos(angleY);
		view.y = cos(angleX);
		view.z = sin(angleX) * sin(angleY);
	}



	std::cout << std::setprecision(3)// << "B" << angleX << " " << angleY << " "
	          << pos.x << "x" << pos.y << "x" << pos.z << " "
	          << view.x << "x" << view.y << "x" << view.z << "velRX:" << velRX << "velRY:" << velRY << "\t\r";




	// Wektor prostopad³y:
	vec3 per;
	per.x = -view.z;
	per.y = 0;
	per.z = view.x;

	// Ruch przod/tyl:

	pos.x += view.x * velM * .1f;
	if (free3DMovement)
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
	if (free3DMovement)
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








void rotX(float)
{

}


void rotY(float)
{

}


void rotZ(float)
{

}






