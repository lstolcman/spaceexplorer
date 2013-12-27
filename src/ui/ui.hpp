#pragma once



class CUI
{
	//Fields:
private:
	void*			font;

public:


	//Members:
private:
	void			printOnScreen(int, int, std::string);
	void			displayHUD(void);
	void			displayFPS(void);

public:
	CUI(void);
	~CUI();

	void			drawUI(void);
	void			setFont(void*);

};



