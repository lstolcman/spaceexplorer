#include "stdafx.hpp"
#include "camera.hpp"



CCamera::CCamera(SCamera *camera)
{
	this->camera = camera;
	
	camera->captureMouse   = true;

	camera->speed = 0.3f;

	camera->pos.x = 0.0f;
	camera->pos.y = 2.0f;
	camera->pos.z = 0.0f;

	camera->view.x = 1.0f;
	camera->view.y = 0.0f;
	camera->view.z = 0.0f;

	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;

	camera->velM = 0.0f;
	camera->velRX = 0.0f;
	camera->velRY = 0.0f;
	camera->velS = 0.0f;


	camera->angleX = 0.0f;
	camera->angleY = 0.0f;
	camera->angleZ = 0.0f;

	camera->latarka = true;

}


CCamera::~CCamera()
{

}


void CCamera::cameraMove(void)
{

	//Obrót kamery (wsp. sferyczne):
	camera->angleX = acos(camera->view.y);
	camera->angleY = atan2(camera->view.z, camera->view.x);
	camera->angleX -= camera->velRX * .03f;
	camera->angleY += camera->velRY * .03f;



	if (camera->angleX < 3.14 && 	camera->angleX > 0.01)
	{

		camera->view.x = sin(camera->angleX) * cos(camera->angleY);
		camera->view.y = cos(camera->angleX);
		camera->view.z = sin(camera->angleX) * sin(camera->angleY);
	}



	std::cout << std::setprecision(3)// << "B" << angleX << " " << angleY << " "
		<< camera->pos.x << "x" << camera->pos.y << "x" << camera->pos.z << " "
		<< camera->view.x << "x" << camera->view.y << "x" << camera->view.z
		<< "velRX:" << camera->velRX << "velRY:" << camera->velRY << "\t\r";




	// Wektor prostopad³y:
	vec3 per;
	per.x = -camera->view.z;
	per.y = 0;
	per.z = camera->view.x;

	// Ruch przod/tyl:

	camera->pos.x += camera->view.x * 	camera->velM * .1f;
		camera->pos.y += camera->view.y * camera->velM * .1f;
	camera->pos.z += camera->view.z * camera->velM * .1f;

	// Ruch na boki:
	camera->pos.x += per.x * camera->velS * .1f;
		camera->pos.y += camera->view.y * camera->velM * .1f;
	camera->pos.z += per.z * 	camera->velS * .1f;
	// Inercja:


	camera->velRX /= 2.2f;
	camera->velRY /= 2.2f;
	camera->velM /= 2.2f;
	camera->velS /= 2.2f;


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






