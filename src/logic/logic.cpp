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



void CLogic::generateAsteroids(void)
{

	for (unsigned i = 0; i < data->genAsteroids; ++i)
	{
		SAsteroid *aster = new SAsteroid;
		aster->pos = //glm::fvec3(rng(-500, 500), rng(-500, 500), rng(-500, 500));
		glm::fvec3((rand() % 2 == 0 ? rng(-500, -10) : rng(500, 10)),
					(rand() % 2 == 0 ? rng(-500, -10) : rng(500, 10)),
					(rand() % 2 == 0 ? rng(-500, -10) : rng(500, 10)));

		//aster->rotationAxis = glm::fvec3(rng("nz", -1, 1), rng("nz", -1, 1), rng("nz", -1, 1));// rand() % 2 + 1, rand() % 2 + 1, rand() % 2 + 1);
		aster->rotationAxis = glm::vec3(1/*(rand() % 2)*/, (rand() % 2), (rand() % 2));
		//aster->rotationAxis = glm::fvec3(1, 0, 0);

		//aster->scale = glm::fvec3(scale + rand() % 20 / 5, scale + rand() % 20 / 5, scale + rand() % 20 / 5);
		aster->scale = rand() % 5 + 1;
		//aster->scale = glm::fvec3(1, 1, 1);
		aster->rotationSpeed = rand() % 2 == 0 ? (rand() % 1000 / 1000.0) + 0.01 : -(rand() % 1000 / 1000.0) + 0.01;
		aster->distance = 0;


		data->asteroids->push_back(*aster);
	}

	//check if asteroid are not too close
	/*for (std::vector<SAsteroid>::iterator x = data->asteroids->begin(); x != data->asteroids->end(); ++x)
	{
		for (std::vector<SAsteroid>::iterator y = data->asteroids->begin(); y != data->asteroids->end(); ++y)
		{
			distanceVec = x->pos - y->pos;

			distance = sqrt(distanceVec.x*distanceVec.x + distanceVec.y*distanceVec.y + distanceVec.z*distanceVec.z);

			if (distance < (asteroidRadius*x->scale + asteroidRadius*y->scale)) // colliding each other
			{
				data->asteroids->erase(x);
				break;
			}
		}
	}*/


}



void CLogic::detectCollision(void)
{
	data->vehicleNearestAsteroidDistance = 10000.0f;
	//data->vehicleNearestAsteroidScale = 0.5f;


	for (std::vector<SAsteroid>::iterator i = data->asteroids->begin(); i != data->asteroids->end(); ++i)
	{

		asteroidPos = i->pos;
		vehiclePos = data->camera->pos + data->camera->view;
		distanceVec = asteroidPos - vehiclePos;

		i->distance = sqrt(distanceVec.x*distanceVec.x + distanceVec.y*distanceVec.y + distanceVec.z*distanceVec.z);

		if (i->distance < data->vehicleNearestAsteroidDistance)
		{
			data->vehicleNearestAsteroidDistance = i->distance;
			data->vehicleNearestAsteroidScale = i->scale;
		}
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

	if (data->vehicleNearestAsteroidDistance < 30*data->vehicleNearestAsteroidScale)
		playMs = 100;
	else if (data->vehicleNearestAsteroidDistance < 35 * data->vehicleNearestAsteroidScale)
		playMs = 200;
	else if (data->vehicleNearestAsteroidDistance < 45 * data->vehicleNearestAsteroidScale)
		playMs = 500;
	else if (data->vehicleNearestAsteroidDistance < 55 * data->vehicleNearestAsteroidScale)
		playMs = 1500;
	else
		playMs = 3000;


	if ((unsigned)timer.getElapsedMilliseconds() > playMs)
	{
		distSound->play();
		timer.reset();
	}
}








