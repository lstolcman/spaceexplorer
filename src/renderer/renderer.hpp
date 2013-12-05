#pragma once

#include "../game/gcommon.hpp"
#include "../tools/timer.hpp"

class CRenderer
{
private:
	unsigned long	frame, frame_old;
	CTimer			time, time_old;

	void			drawFPS(void);
	void			setDisplayMatrices(void);
	void			setupLights(void);
	SPlayer			*player;


public:
	CRenderer(SPlayer*);
	~CRenderer();

	void			drawScene();//SPlayer player);
	void			lookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
	                       GLdouble centerX, GLdouble centerY, GLdouble centerZ,
	                       GLdouble upX, GLdouble upY, GLdouble upZ);



};
