#pragma once

#include "../renderer/rcommon.hpp"
#include "../tools/timer.hpp"
#include "texture.hpp"


class CLoaderOBJ
{
	//Fields:
private:
	std::ifstream		obj;
	std::ifstream		mtl;
	GLuint				handle;
	CTexture			tex;

	SObjFile			*objHandle;

public:


	//Members:
private:



public:
	CLoaderOBJ(SObjFile*, std::string);
	CLoaderOBJ(SObjFile*);
	~CLoaderOBJ();

	bool				loadObj(std::string);
	void				disp(void);


};




















