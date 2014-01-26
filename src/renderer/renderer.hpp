#pragma once

#include "rcommon.hpp"
#include "../game/gcommon.hpp"

#include "object.hpp"
#include "skybox.hpp"

#include "../tools/timer.hpp"
#include "../tools/rng.hpp"
#include "../tools/obj.hpp"
#include "../tools/texture.hpp"
#include "../tools/worldmap.hpp"
#include "../game/camera.hpp"







class CRenderer
{
private:
	unsigned long	frame, frame_old;
	CTimer			fpsTimer, globalTimer;
	CRng			rng;
	SData			*data;
	CSkybox			*skybox;
	CWoldmap		*worldmap;
	CObject			*vehicle;
	CObject			*asteroid;
	CObject			*carrier;
	GLfloat			ang;

	void            countFPS(void);
	void            setDisplayMatrices(void);
	void            setupLights(void);
	void            drawSky(void);


public:
	CRenderer(SData*);
	~CRenderer();

	bool			loadData(void);
	void            drawScene(void);

};


