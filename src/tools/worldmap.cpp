#include "stdafx.hpp"
#include "worldmap.hpp"





CWoldmap::CWoldmap(void)
{
	commentBlock = false;
	commentLine = false;


}

CWoldmap::~CWoldmap(void)
{

}



void CWoldmap::loadPlayerPos(SCamera *camera)
{

	player.open("resources/player.txt", std::ios::in);
	if (player.is_open() == false)
	{
		MessageBox(0, "Error loading: resources/player.txt", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
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

	player.close();
}

void CWoldmap::loadAsteroids(std::vector<SAsteroid> *asteroids)
{
	map.open("resources/worldmap.txt", std::ios::in);
	if (map.is_open() == false)
	{
		MessageBox(0, "Error loading: resources/worldmap.txt", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}


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
				sscanf(line.c_str(), "asteroid %f %f %f %f %f %f %f %f",
					&aster->pos.x, &aster->pos.y, &aster->pos.z,
					&aster->rotationAxis.x, &aster->rotationAxis.y, &aster->rotationAxis.z, &aster->rotationSpeed,
					&aster->scale);
				asteroids->push_back(*aster);
			}
		}

		commentLine = false;
	}


	map.close();
}


void CWoldmap::writeMap(std::vector<SAsteroid> *asteroids, SCamera *camera)
{

	player.open("resources/player.txt", std::ios::out|std::ios::trunc);
	if (player.is_open() == false)
	{
		MessageBox(0, "Error loading: resources/player.txt", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}
		std::stringstream s;
		s << "player_pos" << std::fixed << std::setprecision(2)
			<< camera->pos.x << " " << camera->pos.y << " " << camera->pos.z << std::endl;
		s << "player_view" << std::fixed << std::setprecision(2)
			<< camera->view.x << " " << camera->view.y << " " << camera->view.z << std::endl;
		s << "player_up" << std::fixed << std::setprecision(2)
			<< camera->up.x << " " << camera->up.y << " " << camera->up.z << std::endl;
		s << "player_speed" << std::fixed << std::setprecision(2)
			<< camera->speed << std::endl;
		player << s.str();
		player.flush();



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
	player.close();


	map.open("resources/worldmap.txt", std::ios::out|std::ios::trunc);
	if (map.is_open() == false)
	{
		MessageBox(0, "Error loading: resources/worldmap.txt", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}


	map << "// a(asteroid)	pos_x	pos_y	pos_z	rotation_speed	scale" << std::endl;
	for (std::vector<SAsteroid>::iterator i = asteroids->begin(); i != asteroids->end(); ++i)
	{
		std::stringstream s;
		s << "asteroid " 
			<< std::fixed << std::setprecision(2)
			<< i->pos.x << " " << i->pos.y << " " << i->pos.z << " " \
			<< i->rotationAxis.x << " " << i->rotationAxis.y << " " << i->rotationAxis.z << " " \
			<< i->rotationSpeed << " " << i->scale << "\n";
		map << s.str();
			map.flush();
	}

	map.close();
}








