#pragma once

#include "../game/gcommon.hpp"
#include "../tools/timer.hpp"
#include "../game/camera.hpp"

#include "object.hpp"
#include "skybox.hpp"

//#include "../tools/obj.hpp"
#include "../tools/texture.hpp"



class CRenderer
{
private:
	unsigned long	frame, frame_old;
	CTimer			time, time_old;
	SData			*data;
	CSkybox			*skybox;
	CObject			object;
	CShader			*phong;

	void            countFPS(void);
	void            setDisplayMatrices(void);
	void            setupLights(void);
	void            drawSky(void);


public:
	CRenderer(SData*);
	~CRenderer();

	void			compileShaders(void);
	bool			loadTextures(void);
	void            drawScene();


};
