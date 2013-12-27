#pragma once
#include "../tools/timer.hpp"
#include "../ui/ui.hpp"
#include "../ui/input.hpp"
#include "../renderer/renderer.hpp"
#include "camera.hpp"
#include "gcommon.hpp"

class CGame
{
	// Fields:
private:
	unsigned long long	t1, t2;

	static CGame		*instance;

	struct
	{
		CInput			*input;
		CCamera			*camera;
		CRenderer		*renderer;
		CUI				*ui;
	} handlers;

	SData				*data;


public:


	//Members:
private:
	static void     callbackRender(void);
	static void     callbackReshape(int, int);
	static void     callbackRedisplay(void);
	static void     callbackDrawFPS(int);
	static void     callbackMouseButtonPress(int, int, int, int);
	static void     callbackMouseMove(int, int);
	static void     callbackKeyPress(unsigned char, int, int);
	static void     callbackKeyUp(unsigned char, int, int);
	static void     callbackSpecialKeyPress(int, int, int);
	static void     callbackSpecialKeyUp(int, int, int);
	static void     callbackCaptureInput(int);

	void            Update(void);
	void            Render(void);
	void            Reshape(int width, int height);
	void			setGlutCallbacks(void);
	void			loadTextures(void);
	void			setMouse(void);


public:
	CGame(void);
	~CGame(void);

	void    Init(int, char **);


};




/*

petla gry:
{
//events:

//logic:

//rendering: world, skydome/box,
}

*/