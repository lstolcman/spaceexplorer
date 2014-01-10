#pragma once
#include "../tools/model.hpp"
#include "../tools/texture.hpp"
#include "../tools/shader.hpp"
#include "../tools/obj.hpp"


class CObject
{
	//Fields:
private:
	CTexture	*texture;
	CModel		*model;
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


	bool			bindTexture(CTexture*);
	bool			bindModel(CModel*);
	bool			bindShader(CShader*);

	bool			bindObj(CLoaderOBJ*);

	void			draw(void);


};









