#include "stdafx.hpp"
#include "logic.hpp"






CLogic::CLogic(SData *data)
{
	this->data = data;
	vehicleRadius = 2.0f;
	asteroidRadius = 12.0f;

	timer.start();
	loose = false;
	win = false;
	amb = false;

	soundsLoaded = false;
}


CLogic::~CLogic()
{
}

void CLogic::generateAsteroids(void)
{

	for (unsigned i = 0; i < data->genAsteroids; ++i)
	{
		SAsteroid *aster = new SAsteroid;
		aster->pos = 
			glm::fvec3((rand() % 2 == 0 ? rng(-500, -10) : rng(500, 10)),
			(rand() % 2 == 0 ? rng(-500, -10) : rng(500, 10)),
			(rand() % 2 == 0 ? rng(-500, -10) : rng(500, 10)));

		aster->rotationAxis = glm::vec3(1, (rand() % 2), (rand() % 2));
		aster->scale = rand() % 5 + 1;
		aster->rotationSpeed = rand() % 2 == 0 ? (rand() % 1000 / 1000.0) + 0.01 : -(rand() % 1000 / 1000.0) + 0.01;
		aster->distance = 0;


		data->asteroids->push_back(*aster);
	}

}



void CLogic::detectCollision(void)
{
	//distance from carrier
	distanceVec = (data->camera->pos + data->camera->view) - glm::vec3(1500, -128, -18);

	if (sqrt(distanceVec.x*distanceVec.x + distanceVec.y*distanceVec.y + distanceVec.z*distanceVec.z) < 400 && !data->debugMode)
	{
		data->gameState = WIN;
		data->camera->speed = 0.0f;
	}

	data->vehicleNearestAsteroidDistance = 10000.0f;

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

			if (!data->debugMode)
			{
				data->gameState = LOOSE;
				data->camera->speed = 0.0f;
			}

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
	CTimer t;
	t.start();
	distSound = audiere::OpenSoundEffect(data->audioDevice, "resources/sounds/distance.wav", audiere::MULTIPLE);
	distSound->setVolume(0.30f);
	std::cout << "sound: resources/sounds/distance.wav " << t.getElapsedMilliseconds() << "ms" << std::endl;
	t.reset();
	looseSound = audiere::OpenSoundEffect(data->audioDevice, "resources/sounds/theend.mp3", audiere::MULTIPLE);
	looseSound->setVolume(1.00f);
	std::cout << "sound: resources/sounds/theend.mp3 " << t.getElapsedMilliseconds() << "ms" << std::endl;
	t.reset();
	winSound = audiere::OpenSoundEffect(data->audioDevice, "resources/sounds/win.mp3", audiere::MULTIPLE);
	winSound->setVolume(0.70f);
	std::cout << "sound: resources/sounds/win.mp3 " << t.getElapsedMilliseconds() << "ms" << std::endl;
	t.reset();
	ambSound = audiere::OpenSoundEffect(data->audioDevice, "resources/sounds/tokyo.mp3", audiere::MULTIPLE);
	ambSound->setVolume(0.9);
	std::cout << "sound: resources/sounds/tokyo.mp3 " << t.getElapsedMilliseconds() << "ms" << std::endl;
	t.reset();
	explSound = audiere::OpenSoundEffect(data->audioDevice, "resources/sounds/explosion.mp3", audiere::MULTIPLE);
	explSound->setVolume(0.5);
	std::cout << "sound: resources/sounds/explosion.mp3 " << t.getElapsedMilliseconds() << "ms" << std::endl;
	t.stop();
	soundsLoaded = true;
}

void CLogic::playSounds(void)
{
	if (soundsLoaded == false)
		return;

	unsigned playMs;

	if (data->vehicleNearestAsteroidDistance < 30 * data->vehicleNearestAsteroidScale)
		playMs = 100;
	else if (data->vehicleNearestAsteroidDistance < 35 * data->vehicleNearestAsteroidScale)
		playMs = 200;
	else if (data->vehicleNearestAsteroidDistance < 45 * data->vehicleNearestAsteroidScale)
		playMs = 500;
	else if (data->vehicleNearestAsteroidDistance < 55 * data->vehicleNearestAsteroidScale)
		playMs = 1500;
	else
		playMs = 3000;


	if ((unsigned)timer.getElapsedMilliseconds() > playMs && data->gameState == PLAYING)
	{
		distSound->play();
		timer.reset();
	}

	if (amb == false)
	{
		ambSound->play();
		amb = true;
	}

	if (data->gameState != PLAYING)
	{
		ambSound->stop();
	}

	if (data->gameState == LOOSE && loose == false)
	{
		distSound->setVolume(0.0);
		explSound->play();
		looseSound->play();
		loose = true;
	}
	if (data->gameState == WIN && win == false)
	{
		distSound->setVolume(0.0);
		winSound->play();
		win = true;
	}
}








