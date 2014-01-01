#pragma once

#include "../game/gcommon.hpp"
#include "../tools/timer.hpp"
#include "../tools/obj.hpp"
#include "../game/camera.hpp"

#include "../tools/texture.hpp"



class CRenderer
{
private:
	unsigned long	frame, frame_old;
	CTimer			time, time_old;
	SCamera			*camera;
	SData			*data;

	COBJ			obj;

	// front, right, back, left, top, bottom
	struct
	{
		CTexture	front;
		CTexture	back;
		CTexture	right;
		CTexture	left;
		CTexture	top;
		CTexture	bottom;
	} skybox;

	void            countFPS(void);
	void            setDisplayMatrices(void);
	void            setupLights(void);
	void            drawSky(void);


public:
	CRenderer(SData*);
	~CRenderer();

	bool			loadTextures(void);
	void            drawScene();


};
