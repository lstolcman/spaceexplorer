// stdafx.hpp : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

// => put standard headers and other libraries in there, such as all boost includes.

#pragma once



#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS



#ifndef _DEBUG
	#define FREEGLUT_STATIC
	#define GLEW_STATIC
	#pragma comment(lib,"glew32s.lib")
#else
	#pragma comment(lib,"glew32.lib")
#endif

	#pragma comment(lib,"audiere.lib")
	#pragma comment(lib,"FreeImage.lib")




#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <audiere.h>
#include <FreeImage.h>


#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <valarray>
#include <iomanip>
#include <vector>
#include <map>
#include <fstream>


//#include <regex>


#include <Windows.h>
