#pragma once

#include "../game/gcommon.hpp"
#include "../tools/timer.hpp"
#include "../game/camera.hpp"

class CRenderer
{
private:
	unsigned long frame, frame_old;
	CTimer        time, time_old;
	SCamera *camera;

	void            drawFPS(void);
	void            setDisplayMatrices(void);
	void            setupLights(void);
	void            drawSky(void);


public:
	CRenderer(SCamera*);
	~CRenderer();

	void            drawScene();


};
