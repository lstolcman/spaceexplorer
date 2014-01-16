#include "stdafx.hpp"
#include "worldmap.hpp"





CWoldmap::CWoldmap(void)
{
	commentBlock = false;
	commentLine = false;
	//load map

	map.open("resources/worldmap.txt", std::ios::in);
	if (map.is_open() == false)
	{
		MessageBox(0, "Error loading: resources/worldmap.txt", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	player.open("resources/player.txt", std::ios::in);
	if (map.is_open() == false)
	{
		MessageBox(0, "Error loading: resources/player.txt", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
}

CWoldmap::~CWoldmap(void)
{
	map.close();
	player.close();
}



void CWoldmap::loadPlayerPos(SCamera *camera)
{
	//read player pos 
	while (std::getline(player, line))
	{
		if (line.find("/*") != std::string::npos)
		{
			commentBlock = true;
		}
		if (line.find("*/") != std::string::npos)
		{
			commentBlock = false;
		}
		if (line.find(";") != std::string::npos)
		{
			commentLine = true;
		}

		if ((commentBlock == false) && (commentLine == false))
		{
			if (line.find("player_pos") != std::string::npos)
			{
				sscanf(line.c_str(), "player_pos %f %f %f", &camera->pos.x, &camera->pos.y, &camera->pos.z);
			}
			if (line.find("player_view") != std::string::npos)
			{
				sscanf(line.c_str(), "player_view %f %f %f", &camera->view.x, &camera->view.y, &camera->view.z);
			}
			if (line.find("player_up") != std::string::npos)
			{
				sscanf(line.c_str(), "player_up %f %f %f", &camera->up.x, &camera->up.y, &camera->up.z);
			}
			if (line.find("player_speed") != std::string::npos)
			{
				sscanf(line.c_str(), "player_speed %f", &camera->speed);
			}
		}

		commentLine = false;
	}
}

void CWoldmap::loadAsteroids(std::vector<SAsteroid> *asteroids)
{
	//read map file
	while (std::getline(map, line))
	{
		if (line.find("/*") != std::string::npos)
		{
			commentBlock = true;
		}
		if (line.find("*/") != std::string::npos)
		{
			commentBlock = false;
		}
		if (line.find(";") != std::string::npos)
		{
			commentLine = true;
		}

		if ((commentBlock == false) && (commentLine == false))
		{

			if (line.find("asteroid") != std::string::npos)
			{
				std::cout << "linia: " << line << std::endl;
				SAsteroid *aster = new SAsteroid;
				// asteroid vec3(position) vec4(rotation axis+speed) vec3(scale)
				sscanf(line.c_str(), "asteroid %f %f %f %f %f %f %f %f %f %f",
					&aster->pos.x, &aster->pos.y, &aster->pos.z,
					&aster->rotationAxis.x, &aster->rotationAxis.y, &aster->rotationAxis.z, &aster->rotationSpeed,
					&aster->scale.x, &aster->scale.y, &aster->scale.z);
				asteroids->push_back(*aster);
			}
		}

		commentLine = false;
	}
}









