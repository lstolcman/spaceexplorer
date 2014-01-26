#include "stdafx.hpp"
#include "obj.hpp"





CLoaderOBJ::CLoaderOBJ(SObjFile *obj, std::string file)
{
	objHandle = obj;
	loadObj(file);
}


CLoaderOBJ::CLoaderOBJ(SObjFile *obj)
{
	objHandle = obj;
}



CLoaderOBJ::~CLoaderOBJ()
{

}

bool CLoaderOBJ::loadObj(std::string file)
{
	CTimer t;
	std::string line;
	char *map_Kd = (char*)calloc(100, 1); //temp for sscanf %s
	t.start();
	loadTex = false;

	obj.open(file + ".obj", std::ios::in);
	if (obj.is_open() == false)
	{
		MessageBox(0, ("Error loading: " + file + ".obj").c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
		return false;
	}

	//read vertices, texture coords, normals and faces to vectors
	while (std::getline(obj, line))
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			glm::vec3 *vertex = new glm::vec3;
			sscanf(line.c_str(), "v %f %f %f", &vertex->x, &vertex->y, &vertex->z);
			objHandle->v->push_back(*vertex);
		}
		if (line[0] == 'v' && line[1] == 't')
		{
			glm::vec2 *texture = new glm::vec2;
			sscanf(line.c_str(), "vt %f %f", &texture->x, &texture->y);
			objHandle->t->push_back(*texture);
		}
		if (line[0] == 'v' && line[1] == 'n')
		{
			glm::vec3 *normals = new glm::vec3;
			sscanf(line.c_str(), "vn %f %f %f", &normals->x, &normals->y, &normals->z);
			objHandle->n->push_back(*normals);
		}
		if (line[0] == 'f' && line[1] == ' ')
		{
			if (line.find("//") != std::string::npos)  //no texture, face format: f %d//%d ...
			{
				loadTex = false;
				SFace *face = new SFace;
				sscanf(line.c_str(), "f %d//%d %d//%d %d//%d",
					&face->v[0], /*&face->t[0],*/ &face->n[0],
					&face->v[1], /*&face->t[1],*/ &face->n[1],
					&face->v[2], /*&face->t[2],*/ &face->n[2]
					);
				objHandle->f->push_back(*face);
			}
			else
			{
				loadTex = true;
				SFace *face = new SFace;
				sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&face->v[0], &face->t[0], &face->n[0],
					&face->v[1], &face->t[1], &face->n[1],
					&face->v[2], &face->t[2], &face->n[2]
					);
				objHandle->f->push_back(*face);
			}
		}
	}
	obj.close();


	if (loadTex)
	{

		mtl.open(file + ".mtl", std::ios::in);
		if (mtl.is_open() == false)
		{
			MessageBox(0, ("Error loading: " + file + ".mtl").c_str(), "Error", MB_OK | MB_ICONERROR);
			exit(1);
			return false;
		}

		//read light attributes
		while (std::getline(mtl, line))
		{

			if (line[0] == 'K' && line[1] == 'a')
			{
				sscanf(line.c_str(), "Ka %f %f %f", &objHandle->amb.x, &objHandle->amb.y, &objHandle->amb.z);
			}
			if (line[0] == 'K' && line[1] == 'd')
			{
				sscanf(line.c_str(), "Kd %f %f %f", &objHandle->dif.x, &objHandle->dif.y, &objHandle->dif.z);
			}
			if (line[0] == 'K' && line[1] == 's')
			{
				sscanf(line.c_str(), "Ks %f %f %f", &objHandle->spe.x, &objHandle->spe.y, &objHandle->spe.z);
			}
			if (line.find("map_Kd") != std::string::npos)
			{
				sscanf(line.c_str(), "map_Kd %s", map_Kd);
			}

		}

		mtl.close();

		objHandle->map_Kd = std::string(map_Kd);

	}
	t.stop();
	std::cout << "model: " << file << " " << t.getElapsedMilliseconds() << "ms" << std::endl;

	delete map_Kd;
	return true;
}



void CLoaderOBJ::disp(void)
{
	glCallList(handle);
}

























