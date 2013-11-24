#pragma once
#include "../tools/math.hpp"

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	FORWARD,
	BACKWARD
};

struct SPlayer
{
	vec3 pos;
	vec3 dir;
	float speed;
	float velRX;
	float velRY;
	float velM;
	float velS;
};