#pragma once
#include "../tools/timer.hpp"
#include "../tools/model.hpp"
#include "../tools/texture.hpp"

#include "../tools/obj.hpp"





class CSkybox
{
	//Fields:
private:
	CTexture	front;
	CTexture	back;
	CTexture	right;
	CTexture	left;
	CTexture	top;
	CTexture	bottom;
public:


	//Members:
private:

public:
	CSkybox(void);
	~CSkybox();

	void		load(void);
	void		draw(void);

};



