#pragma once

#include "../game/gcommon.hpp"
#include "../tools/timer.hpp"
#include "../game/camera.hpp"

class CRenderer
{
private:
	unsigned long frame, frame_old;
	CTimer        time, time_old;
	CCamera       *player;

	void            drawFPS(void);
	void            setDisplayMatrices(void);
	void            setupLights(void);


public:
	CRenderer(CCamera *);
	~CRenderer();

	void            drawScene();
	/*void            lookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
	                       GLdouble centerX, GLdouble centerY, GLdouble centerZ,
	                       GLdouble upX, GLdouble upY, GLdouble upZ);*/



};
