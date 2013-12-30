#include "stdafx.hpp"
#include "obj.hpp"





COBJ::COBJ(void)
{


}



COBJ::~COBJ()
{

}

bool COBJ::loadObj(std::string file)
{
	std::string line;
	std::vector<vec3> * v = new std::vector<vec3>();
	std::vector<vec3> * n = new std::vector<vec3>();
	std::vector<vec3> * t = new std::vector<vec3>();
	std::vector<SFace> * f = new std::vector<SFace>();

	vec3 a;

	obj.open(file, std::ios::in);
	if (obj.is_open() == NULL)
	{
		std::cout << "Blad otwierania pliku: " << file << std::endl;
		return false;
	}

	while (std::getline(obj, line))
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			vec3 * vertex = new vec3;
			sscanf(line.c_str(), "v %f %f %f", &vertex->x, &vertex->y, &vertex->z);
			v->push_back(*vertex);
		}
		if (line[0] == 'v' && line[1] == 't')
		{
			vec3 * vertex = new vec3;
			sscanf(line.c_str(), "vt %f %f", &vertex->x, &vertex->y);
			t->push_back(*vertex);
		}
		if (line[0] == 'v' && line[1] == 'n')
		{
			vec3 * vertex = new vec3;
			sscanf(line.c_str(), "vn %f %f %f", &vertex->x, &vertex->y, &vertex->z);
			n->push_back(*vertex);
		}
		if (line[0] == 'f' && line[1] == ' ')
		{
			SFace * face = new SFace;
			sscanf(line.c_str(), "f %d//%d %d//%d %d//%d",
				&face->v[0], /*&face->t[0],*/ &face->n[0],
				&face->v[1],/* &face->t[1],*/ &face->n[1],
				&face->v[2], /*&face->t[2],*/ &face->n[2]
				);
			f->push_back(*face);
		}
	}

	obj.close();

	//GLuint dlId;
	//dlId = glGenLists(1);
	handle = glGenLists(1);
	glNewList(handle, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < f->size(); ++i) {
		for (int j = 0; j < 3; ++j) {
			
			vec3 * cv = &(*v)[((*f)[i].v[j] - 1)];
			//vec3 * ct = &(*t)[((*f)[i].t[j] - 1)];
			vec3 * cn = &(*n)[((*f)[i].n[j] - 1)];
			//glTexCoord2f(ct->x, ct->y);
			glNormal3f(cn->x, cn->y, cn->z);
			glVertex3f(cv->x, cv->y, cv->z);
			
		}
	}
	glEnd();
	glEndList();

	delete v;
	delete n;
	delete t;
	delete f;



	return true;

}



void COBJ::disp(void)
{
	glCallList(handle);
}














