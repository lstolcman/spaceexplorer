#include "stdafx.hpp"
#include "bitmap.hpp"


/*
CLoaderBitmap::CLoaderBitmap(std::string file)
{
data = NULL;
bmHandle.open(file, std::ios::in | std::ios::binary);
}
*/



CLoaderBitmap::CLoaderBitmap(void)
{
	bmWidth = 0;
	bmHeight = 0;
	bmFmt = FIF_UNKNOWN;
	bmHandle = NULL;
	data = NULL;
}


CLoaderBitmap::~CLoaderBitmap()
{
	delete data;
}



bool CLoaderBitmap::loadBitmap(std::string file)
{
	bmFmt = FreeImage_GetFileType(file.c_str(), 0);

	if (bmFmt == FIF_UNKNOWN)
		return false;

	if (FreeImage_FIFSupportsReading(bmFmt))
		bmHandle = FreeImage_Load(bmFmt, file.c_str());
	else
		return false;

	data = FreeImage_GetBits(bmHandle);

	bmWidth = FreeImage_GetWidth(bmHandle);
	bmHeight = FreeImage_GetHeight(bmHandle);

	return true;
}


bool CLoaderBitmap::unloadBitmap(void)
{
	if (bmHandle)
	{
		FreeImage_Unload(bmHandle);
		return true;
	}
	else
	{
		return false;
	}
}
