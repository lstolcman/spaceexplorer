#pragma once

#include "./game/gcommon.hpp"
#include "../tools/timer.hpp"
#include "../tools/rng.hpp"

class CLogic
{
	// Fields:
private:
	SData			*data;

	glm::fvec3		asteroidPos;
	glm::fvec3		asteroidScale;
	glm::fvec3		playerPos;
	glm::fvec3		vehiclePos;
	glm::fvec3		vehicleScale;
	glm::fvec3		distanceVec;
	float			distance;
	float			radiusLOD;


	float vehicleRadius;	
	float asteroidRadius;

	CRng					rng;

	audiere::SoundEffectPtr distSound;
	audiere::SoundEffectPtr looseSound;
	audiere::SoundEffectPtr winSound;
	audiere::SoundEffectPtr ambSound;
	audiere::SoundEffectPtr explSound;

	CTimer					timer;

	bool					soundsLoaded;

	bool					loose;
	bool					win;
	bool					amb;

public:



	//Members:
private:

public:
	CLogic(SData*);
	~CLogic();

	void			generateAsteroids(void);
	void			detectCollision(void);
	void			loadSounds(void);
	void			playSounds(void);

};






























