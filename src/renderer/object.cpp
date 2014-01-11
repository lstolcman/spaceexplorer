#include "stdafx.hpp"
#include "object.hpp"





CObject::CObject(void)
{
	modelLoaded = false;
	obj = NULL;
	objFile = new SObjFile;
}


CObject::~CObject()
{
	delete obj;
	delete objFile;
	delete map_Kd;
}



bool CObject::bindTexture(std::string texture)
{
	map_Kd = new CTexture;
	map_Kd->Load("resources/models/" + texture);
	return true;
}


bool CObject::bindModel(std::string modelPath)
{
	CLoaderOBJ *obj = new CLoaderOBJ(objFile);

	if (obj->loadObj(modelPath) == true)
	{
		map_Kd = new CTexture;
		map_Kd->Load("resources/models/" + objFile->map_Kd);

		modelListHandle = glGenLists(1);
		glNewList(modelListHandle, GL_COMPILE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, (*map_Kd)());
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < objFile->f->size(); ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				glm::vec3 *cv = &(*objFile->v)[((*objFile->f)[i].v[j] - 1)];
				glm::vec2 *ct = &(*objFile->t)[((*objFile->f)[i].t[j] - 1)];
				glm::vec3 *cn = &(*objFile->n)[((*objFile->f)[i].n[j] - 1)];
				glTexCoord2f(ct->x, ct->y);
				glNormal3f(cn->x, cn->y, cn->z);
				glVertex3f(cv->x, cv->y, cv->z);
			}
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glEndList();
		glPopMatrix();

		delete objFile->v;
		delete objFile->n;
		delete objFile->t;
		delete objFile->f;


		modelLoaded = true;
		return true;
	}
	else
	{
		modelLoaded = false;
		return false;
	}

}

bool CObject::bindShader(CShader *shader)
{
	this->shader = shader;


	return true;
}



void CObject::draw(void)
{
	if (modelLoaded == false)
	{
		MessageBox(0, "Model not loaded", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}


	glPushMatrix();

	float o_amb[] = { objFile->amb.x, objFile->amb.y, objFile->amb.z, 1.0f };
	float o_dif[] = { objFile->dif.x, objFile->dif.y, objFile->dif.z, 1.0f };
	float o_spe[] = { objFile->spe.x, objFile->spe.y, objFile->spe.z, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, o_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, o_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, o_spe);

	glCallList(modelListHandle);

	glPopMatrix();
}







