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


public:
	CRenderer();
	~CRenderer();

	void			playerGetCoordinates(SPlayer player);
	void			drawScene(void);
	void			lookAt(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ,
	                       GLdouble centerX, GLdouble centerY, GLdouble centerZ,
	                       GLdouble upX, GLdouble upY, GLdouble upZ);



};
