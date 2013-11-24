#pragma once
#include "../tools/math.hpp"
#include "gcommon.hpp"

class CPlayer
{
private:
	SPlayer player;
	float	mouseSensitivity;
	bool	free3DMovement;
	bool	captureMouse;

public:
	CPlayer();
	~CPlayer();

	void cameraMove(Direction, int, int);
	SPlayer playerCoordinates(void);

};
