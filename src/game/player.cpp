#include "stdafx.hpp"
#include "player.hpp"



CPlayer::CPlayer()
{
	free3DMovement		= true;
	captureMouse		= true;

	player.speed		= 0.3f;

	player.pos.x		= 0.0f;
	player.pos.y		= 2.0f;
	player.pos.z		= 0.0f;

	player.dir.x		= 1.0f;
	player.dir.y		= 0.0f;
	player.dir.z		= 0.0f;

	player.velM			= 0.0f;
	player.velRX		= 0.0f;
	player.velRY		= 0.0f;
	player.velS			= 0.0f;

}


CPlayer::~CPlayer()
{

}


void CPlayer::playerMove(SPlayer input)
{
}



SPlayer* CPlayer::playerCoordinates(void)
{
	return &player;
};
