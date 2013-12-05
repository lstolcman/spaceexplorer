#pragma once
#include "../tools/math.hpp"
#include "gcommon.hpp"

class CPlayer
{
private:
	

	bool	free3DMovement;
	bool	captureMouse;
	SPlayer player;

public:
	
	CPlayer();
	~CPlayer();

	void playerMove(SPlayer input);
	SPlayer* playerCoordinates(void);

};
