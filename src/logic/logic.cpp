#include "stdafx.hpp"
#include "logic.hpp"






CLogic::CLogic(SData *data)
{
	this->data = data;
	vehicleRadius = 2.0f;
	asteroidRadius = 12.0f;

	timer.start();
}


CLogic::~CLogic()
{
}


/*
1. detect collision between vehicle and last collided object(sphere-sphere check) - for better performance
2. if sp-sp == true - detect collsion between every vertice of asteroid
*/


/*
This small operation calcuates the distance between two points. The routine can work in any number of dimensions, so you cold apply it to 2D or 3D.
In 3D - Define your two points. Point 1 at (x1, y1, z1) and Point 2 at (x2, y2, z2).

xd = x2-x1
yd = y2-y1
zd = z2-z1
Distance = SquareRoot(xd*xd + yd*yd + zd*zd)

As you can see, this requires that you perform a square root. Square roots should be avoided like the plague if you want to write fast code. Only perform a Square Root if you really need to.

Ways to avoid Square Roots:
If you don't need a very accurate distance, you can use a lookup table to calculate it.
If, for example, you are performing collision detection between spheres, and all you want to know is whether or not two have collided, then you do not need to use a square root. Simply change the piece of code from:

if SquareRoot(xd*xd + yd*yd) < Diameter

to:

if (xd*xd + yd*yd) < (Diameter*Diameter)


*/
void CLogic::detectCollision(void)
{
	data->vehicleNearestAsteroid = 10000.0f;


	for (std::vector<SAsteroid>::iterator i = data->asteroids->begin(); i != data->asteroids->end(); ++i)
	{

		asteroidPos = i->pos;
		vehiclePos = data->camera->pos + data->camera->view;
		distanceVec = asteroidPos - vehiclePos;

		i->distance = sqrt(distanceVec.x*distanceVec.x + distanceVec.y*distanceVec.y + distanceVec.z*distanceVec.z);

		if (i->distance < data->vehicleNearestAsteroid)
			data->vehicleNearestAsteroid = i->distance;
	}


	//check last collision first!!!!
	for (std::vector<SAsteroid>::iterator i = data->asteroids->begin(); i != data->asteroids->end(); ++i)
	{
		radiusLOD = (asteroidRadius*i->scale) + vehicleRadius;
		if (i->distance < radiusLOD)
		{
			i->collision = true;
			i->radiusLOD = radiusLOD;
			data->debugCollision = true;
		}
		else
		{
			i->collision = false;
			i->radiusLOD = radiusLOD;
			data->debugCollision = false;
		}
	}

}


void CLogic::loadSounds(void)
{
	distSound = audiere::OpenSoundEffect(data->audioDevice, "resources/sounds/distance.wav", audiere::MULTIPLE);

	distSound->setVolume(0.30f);
}

void CLogic::playSounds(void)
{
	unsigned playMs;

	if (data->vehicleNearestAsteroid < 20)
		playMs = 100;
	else if (data->vehicleNearestAsteroid < 25)
		playMs = 200;
	else if (data->vehicleNearestAsteroid < 35)
		playMs = 500;
	else if (data->vehicleNearestAsteroid < 45)
		playMs = 1500;
	else
		playMs = 3000;


	std::cout << "\nevery: " << playMs << "\n";

	if ((unsigned)timer.getElapsedMilliseconds() > playMs)
	{
		distSound->play();
		timer.reset();
	}
}








