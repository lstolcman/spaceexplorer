#include "stdafx.hpp"
#include "obj.hpp"





CLoaderOBJ::CLoaderOBJ(void)
{


}



CLoaderOBJ::~CLoaderOBJ()
{

}

bool CLoaderOBJ::loadObj(std::string file)
{
	std::string line;
	std::vector<glm::vec3> *v = new std::vector<glm::vec3>();
	std::vector<glm::vec2> *t = new std::vector<glm::vec2>();
	std::vector<glm::vec3> *n = new std::vector<glm::vec3>();
	std::vector<SFace> *f = new std::vector<SFace>();


	obj.open(file+".obj", std::ios::in);
	if (obj.is_open() == NULL)
	{
		std::cout << "Blad otwierania pliku modelu: " << file << std::endl;
		MessageBox(0, ("Error loading: " + file).c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(-1);
		return false;
	}

	//read vertices, texture coords, normals and faces to vectors
	while (std::getline(obj, line))
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			glm::vec3 *vertex = new glm::vec3;
			sscanf(line.c_str(), "v %f %f %f", &vertex->x, &vertex->y, &vertex->z);
			v->push_back(*vertex);
		}
		if (line[0] == 'v' && line[1] == 't')
		{
			glm::vec2 *texture = new glm::vec2;
			sscanf(line.c_str(), "vt %f %f", &texture->x, &texture->y);
			t->push_back(*texture);
		}
		if (line[0] == 'v' && line[1] == 'n')
		{
			glm::vec3 *normals = new glm::vec3;
			sscanf(line.c_str(), "vn %f %f %f", &normals->x, &normals->y, &normals->z);
			n->push_back(*normals);
		}
		if (line[0] == 'f' && line[1] == ' ')
		{
			SFace *face = new SFace;
			sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&face->v[0], &face->t[0], &face->n[0],
				&face->v[1], &face->t[1], &face->n[1],
				&face->v[2], &face->t[2], &face->n[2]
				);
			f->push_back(*face);
		}
	}
	obj.close();

	mtl.open(file+".mtl", std::ios::in);
	glm::vec4 amb, dif, spe;
	char *map_Kd = (char*)calloc(100, 1);

	//read light attributes
	while (std::getline(mtl, line))
	{

		if (line[0] == 'K' && line[1] == 'a')
		{
			sscanf(line.c_str(), "Ka %f %f %f", &amb.x, &amb.y, &amb.z);
		}
		if (line[0] == 'K' && line[1] == 'd')
		{
			sscanf(line.c_str(), "Kd %f %f %f", &dif.x, &dif.y, &dif.z);
		}
		if (line[0] == 'K' && line[1] == 's')
		{
			sscanf(line.c_str(), "Ks %f %f %f", &spe.x, &spe.y, &spe.z);
		}
		if (line.find("map_Kd") != std::string::npos)
		{
			sscanf(line.c_str(), "map_Kd %s", map_Kd);
		}
	}

	mtl.close();

	tex.Load("resources/models/"+std::string(map_Kd));// , GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);// GL_NEAREST);

	handle = glGenLists(1);
	glPushMatrix();


	float o_amb[] = { amb.x, amb.y, amb.z, 1.0f };
	float o_dif[] = { dif.x, dif.y, dif.z, 1.0f };
	float o_spe[] = { spe.x, spe.y, spe.z, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, o_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, o_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, o_spe);


	glNewList(handle, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex());
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < f->size(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			glm::vec3 *cv = &(*v)[((*f)[i].v[j] - 1)];
			glm::vec2 *ct = &(*t)[((*f)[i].t[j] - 1)];
			glm::vec3 *cn = &(*n)[((*f)[i].n[j] - 1)];
			glTexCoord2f(ct->x, ct->y);
			glNormal3f(cn->x, cn->y, cn->z);
			glVertex3f(cv->x, cv->y, cv->z);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEndList();
	glPopMatrix();

	delete v;
	delete n;
	delete t;
	delete f;



	return true;

}



void CLoaderOBJ::disp(void)
{
	glCallList(handle);

}

























