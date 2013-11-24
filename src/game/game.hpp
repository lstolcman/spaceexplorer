#pragma once
#include "..\tools\timer.hpp"


class CGame
{
// Fields:
private:
	unsigned long       frame, frameold;
	unsigned long long  t1, t2;
	static CGame        *instance;
	CTimer              timexx;

public:


//Members:
private:
	static void     callbackRender(void);
	static void     callbackReshape(int width, int height);
	static void     drawFPS(int);
	static void     callbackDrawFPS(int);
	static void     callbackRedisplay(void);

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