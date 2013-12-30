// stdafx.hpp : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

// => put standard headers and other libraries in there, such as all boost includes.

#pragma once


#ifndef _DEBUG
#define FREEGLUT_STATIC

#define GLEW_STATIC
#pragma comment(lib,"glew32s.lib")

#else

#pragma comment(lib,"glew32.lib")

#endif


#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <string>
#include <sstream>
#include <valarray>
#include <iomanip>

#include <fstream>


//#include <regex>

#include <Windows.h>
