#include "stdafx.hpp"
#include "camera.hpp"



CCamera::CCamera(SData *data)
{
	this->data = data;
	
	data->camera->captureMouse   = true;

	data->camera->speed = 0.02f;

	data->camera->pos.x = 0.0f;
	data->camera->pos.y = 0.0f;
	data->camera->pos.z = 0.0f;

	data->camera->view.x = 1.0f;
	data->camera->view.y = 0.0f;
	data->camera->view.z = 0.0f;

	data->camera->up.x = 0.0f;
	data->camera->up.y = 1.0f;
	data->camera->up.z = 0.0f;

	data->camera->velM = 0.0f;
	data->camera->velRX = 0.0f;
	data->camera->velRY = 0.0f;
	data->camera->velRZ = 0.0f;
	data->camera->velS = 0.0f;


	data->camera->angleX = 0.0f;
	data->camera->angleY = 0.0f;
	data->camera->angleZ = 0.0f;

}


CCamera::~CCamera()
{

}


void CCamera::cameraMove(void)
{

	//Obrót kamery (wsp. sferyczne):
	data->camera->angleX = acos(data->camera->view.y);
	data->camera->angleY = atan2(data->camera->view.z, data->camera->view.x);
	data->camera->angleX -= data->camera->velRX * .03f;
	data->camera->angleY += data->camera->velRY * .03f;


	if (data->camera->angleX < 3.14 && data->camera->angleX > 0.01)
	{
		data->camera->view.x = sin(data->camera->angleX) * cos(data->camera->angleY);
		data->camera->view.y = cos(data->camera->angleX);
		data->camera->view.z = sin(data->camera->angleX) * sin(data->camera->angleY);
	}


	// Obrot kamery
	data->camera->angleZ = atan2(data->camera->up.x, data->camera->up.y);
	data->camera->angleZ -= .02f * data->camera->velRZ;
	data->camera->up.y = cos(data->camera->angleZ);
	data->camera->up.x = sin(data->camera->angleZ);

	/*std::cout << std::fixed << std::setprecision(4)// << "B" << angleX << " " << angleY << " "
		<< data->camera->pos.x << "x" << data->camera->pos.y << "x" << data->camera->pos.z << " "
		<< data->camera->view.x << "x" << data->camera->view.y << "x" << data->camera->view.z
		<< "velRX:" << data->camera->velRX << "velRY:" << data->camera->velRY << "\t\r";*/


	// Wektor prostopad³y:
	glm::vec3 per;
	per.x = -data->camera->view.z;
	per.y = data->camera->view.y; //0;
	per.z = data->camera->view.x;

	// Ruch przod/tyl:
	data->camera->pos.x += data->camera->view.x * 	data->camera->velM * .1f;
	data->camera->pos.y += data->camera->view.y * data->camera->velM * .1f;
	data->camera->pos.z += data->camera->view.z * data->camera->velM * .1f;

	// Ruch na boki:
	data->camera->pos.x += per.x * data->camera->velS * .1f;
	data->camera->pos.y += data->camera->view.y * data->camera->velM * .1f;
	data->camera->pos.z += per.z * 	data->camera->velS * .1f;

	// Inercja:
	data->camera->velRX /= 1.1f;
	data->camera->velRY /= 1.1f;
	data->camera->velRZ /= 1.1f;
	data->camera->velM /= 1.1f;
	data->camera->velS /= 1.1f;

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






