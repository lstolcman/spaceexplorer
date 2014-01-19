#pragma once

#include "../game/gcommon.hpp"
#include "../renderer/rcommon.hpp"
#include "../tools/timer.hpp"



class CWoldmap
{
	//Fields:
private:
	std::string		line;
	std::fstream	map;
	std::fstream	player;
	bool			commentBlock;
	bool			commentLine;
public:


	//Members:
private:

public:

	CWoldmap(void);
	~CWoldmap();
	void			loadPlayerPos(SCamera*);
	void			loadAsteroids(std::vector<SAsteroid>*);
	void			writeMap(std::vector<SAsteroid>*, SCamera*);
};
































