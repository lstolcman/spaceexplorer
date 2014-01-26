#pragma once
#include "../tools/timer.hpp"
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
	std::string	size;
	std::string version;

	GLuint		frontHandle;
	GLuint		backHandle;
	GLuint		rightHandle;
	GLuint		leftHandle;
	GLuint		topHandle;
	GLuint		bottomHandle;
public:


	//Members:
private:

public:
	CSkybox(void);
	~CSkybox();

	void		load(void);
	void		draw(void);

};



