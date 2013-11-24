#include "stdafx.hpp"
#include "player.hpp"






CPlayer::CPlayer()
{
	player.speed		= 0;
	mouseSensitivity	= .2f;
	free3DMovement		= true;
	captureMouse		= true;
}



CPlayer::~CPlayer()
{

}


void CPlayer::cameraMove(Direction direction, int x, int y)
{
	/*	#pragma region Ruch kamery

	if (captureMouse) {
	player.velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
	player.velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}

	if (keystate['w']) {
	player.velM = player.speed;
	}
	if (keystate['s']) {
	player.velM = -player.speed;
	}
	if (keystate['a']) {
	player.velS = -player.speed;
	}
	if (keystate['d']) {
	player.velS = player.speed;
	}
	if (keystate['q']) {
	player.velRY = -player.speed;
	}
	if (keystate['e']) {
	player.velRY = player.speed;
	}
	if (keystate['f']) {
	player.velRX = -player.speed;
	}
	if (keystate['c']) {
	player.velRX = player.speed;
	}

	// Obrót kamery (wsp. sferyczne):
	float T = acos(player.dir.y);
	float G = atan2(player.dir.z, player.dir.x);
	T -= player.velRX * .03f;
	G += player.velRY * .03f;
	player.dir.x = sin(T) * cos(G);
	player.dir.y = cos(T);
	player.dir.z = sin(T) * sin(G);

	// Wektor prostopad³y:
	vec3 per;
	per.x = -player.dir.z;
	per.y = 0;
	per.z = player.dir.x;

	// Ruch przod/tyl:
	player.pos.x += player.dir.x * player.velM * .1f;
	if (free3DMovement) {
	player.pos.y += player.dir.y * player.velM * .1f;
	}
	else {
	player.pos.y = 1.0f;
	}
	player.pos.z += player.dir.z * player.velM * .1f;

	// Ruch na boki:
	player.pos.x += per.x * player.velS * .1f;
	if (free3DMovement) {
	player.pos.y += player.dir.y * player.velM * .1f;
	}
	else {
	player.pos.y = 1.0f;
	}
	player.pos.z += per.z * player.velS * .1f;

	// Inercja:
	player.velRX /= 1.2;
	player.velRY /= 1.2;
	player.velM /= 1.2;
	player.velS /= 1.2;

	#pragma endregion*/
}



SPlayer CPlayer::playerCoordinates(void)
{
	return player;
};
