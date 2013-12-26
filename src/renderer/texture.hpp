#pragma once
#include "../tools/bitmap.hpp"



class CTexture
{
	//Fields:
private:
	GLuint		handle;
public:


	//Members:
private:

public:
	CTexture(void);
	CTexture(std::string, int, int);
	~CTexture(void);

	GLuint		Load(std::string, int, int);
	GLuint		operator()();

};
















