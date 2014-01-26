#pragma once

#include "../game/gcommon.hpp"

#include "../tools/texture.hpp"



class CUI
{
	//Fields:
private:
	void*			font;
	SData			*data;
	unsigned		textLines;
	CTexture		*win, *loose;
	unsigned		width, height;

public:


	//Members:
private:
	void			printOnScreen(std::string&);
	void			printOnScreen(int, int, std::string&);
	void			displayHUD(void);
	void			displayFPS(void);
	void			displayDebug(void);

public:
	CUI(SData*);
	~CUI();

	void			drawUI(void);
	void			setFont(void*);
	void			loadUIData(void);

};



