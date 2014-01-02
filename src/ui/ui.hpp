#pragma once

#include "../game/gcommon.hpp"

#include "../tools/texture.hpp"



class CUI
{
	//Fields:
private:
	void*			font;
	SData			*data;

public:


	//Members:
private:
	void			printOnScreen(int, int, std::string);
	void			displayHUD(void);
	void			displayFPS(void);
	void			displayDebug(void);

public:
	CUI(SData*);
	~CUI();

	void			drawUI(void);
	void			setFont(void*);

};



