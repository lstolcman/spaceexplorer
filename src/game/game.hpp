#pragma once
#include "../tools/timer.hpp"
#include "../ui/ui.hpp"
#include "../ui/input.hpp"
#include "../renderer/renderer.hpp"
#include "player.hpp"
#include "gcommon.hpp"

class CGame
{
// Fields:
private:
	//unsigned long		frame, frameold;
	unsigned long long	t1, t2;
	static CGame		*instance;
	CTimer				timexx;
	CInput				*input;
	CPlayer				*player;
	CRenderer			*renderer;


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

	//static void     drawFPS(int);

public:
	CGame(void);
	~CGame(void);

	void    Init(int, char **);
	void    Update(void);
	void    Render(void);
	void    Reshape(int width, int height);

};




/*

petla gry:
{
//events:

//logic:

//rendering: world, skydome/box,
}

*/