#pragma once

#include "../game/gcommon.hpp"
#include "../tools/timer.hpp"
#include "../tools/obj.hpp"
#include "../tools/texture.hpp"
#include "../game/camera.hpp"

#include "object.hpp"
#include "skybox.hpp"
#include "rcommon.hpp"





class CRenderer
{
private:
	unsigned long	frame, frame_old;
	CTimer			fpsTimer, globalTimer;
	SData			*data;
	CSkybox			*skybox;
	CObject			*object, *a;
	GLfloat			ang;
	/*
	CShader			*phong;
	CShader			*tex;
	*/
	std::vector<SAsteroid>		*asteroids;

	void            countFPS(void);
	void            setDisplayMatrices(void);
	void            setupLights(void);
	void            drawSky(void);


public:
	CRenderer(SData*);
	~CRenderer();

	bool			loadData(void);
	void            drawScene();


};
