#include "stdafx.hpp"
#include "object.hpp"





CObject::CObject(void)
{
	obj = NULL;
}


CObject::~CObject()
{
	delete obj;
}



bool CObject::bindTexture(CTexture *texture)
{
	this->texture = texture;


	return true;
}


bool CObject::bindModel(CModel *model)
{
	this->model = model;


	return true;
}

bool CObject::bindObj(CLoaderOBJ *obj)
{
	this->obj = obj;



	return true;
}



void CObject::draw(void)
{
	if (!obj)
	{
		obj = new CLoaderOBJ;
		obj->loadObj("resources/models/vehicle");
	}
	glPushMatrix();
	obj->disp();
	glPopMatrix();
}







