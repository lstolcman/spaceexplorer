#pragma once
#include "../tools/texture.hpp"
#include "../tools/shader.hpp"
#include "../tools/obj.hpp"
#include "rcommon.hpp"

class CObject
{
	//Fields:
private:
	bool		modelLoaded;

	GLuint		modelListHandle;

	SObjFile	*objFile;

	CTexture	*map_Kd;


	CLoaderOBJ	*obj;
	CShader		*shader;
	glm::vec3	pos;
	float		rotationSpeed;
public:


	//Members:
private:

public:
	CObject(void);
	~CObject();

	bool			bindTexture(std::string);
	bool			bindModel(std::string);

	void			draw(void);


};









