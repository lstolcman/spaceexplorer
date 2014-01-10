#pragma once
#include "../game/gcommon.hpp"

#include "../tools/bmp.hpp"



class CTexture
{
	//Fields:
private:
	GLuint		handle;
	bool		loaded;

	SData		*data;
public:


	//Members:
private:

public:
	CTexture(SData*);
	CTexture(void);
	~CTexture(void);

	GLuint		Load(std::string);
	GLuint		Load(std::string, int, int);
	GLuint		operator()();

};
















