#pragma once

#include "./game/gcommon.hpp"


class CLogic
{
	// Fields:
private:
	SData			*data;


	//collision sphere-sphere

	// vec3-position, vec3-scaling factor to determie the spehere size
	glm::fvec3		asteroidPos;
	glm::fvec3		asteroidScale;
	glm::fvec3		playerPos;
	glm::fvec3		vehiclePos; //calculate vehiclePos from playerPos [translations of the vehicle]
	glm::fvec3		vehicleScale;
	glm::fvec3		distanceVec;
	float			distance;

public:



	//Members:
private:

public:
	CLogic(SData*);
	~CLogic();

	void			detectCollision(void);

};





























