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
	GLfloat			width, height;

	CTexture		win, loose;
	CTexture		speed8;
	CTexture		speed6;
	CTexture		speed4;
	CTexture		speed2;
	CTexture		speed0;
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



