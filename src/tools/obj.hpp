#pragma once

#include "../tools/math.hpp"
#include "texture.hpp"


class CLoaderOBJ
{
	//Fields:
private:
	struct SFace {
		unsigned v[3];
		unsigned t[3];
		unsigned n[3];
	};
	std::ifstream		obj;
	std::ifstream		mtl;
	GLuint				handle;
	CTexture			tex;

public:


	//Members:
private:



public:
	CLoaderOBJ(void);
	~CLoaderOBJ();

	bool				loadObj(std::string);
	void				disp(void);


};




















