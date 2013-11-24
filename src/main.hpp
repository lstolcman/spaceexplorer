#pragma once




//no console in release version
#ifndef _DEBUG
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif



#include "game/game.hpp"
