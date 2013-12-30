#include "stdafx.hpp"
#include "bitmap.hpp"


/*
CBitmap::CBitmap(std::string file)
{
data = NULL;
bmHandle.open(file, std::ios::in | std::ios::binary);
}
*/



CBitmap::CBitmap(void)
{
	bmWidth = 0;
	bmHeight = 0;
	data = NULL;
}


CBitmap::~CBitmap()
{
	if (bmHandle.is_open())
		bmHandle.close();
	delete data;
}



bool CBitmap::loadBMP(std::string file)
{
	unsigned bmSize;
	char tmp;

	bmHandle.open(file, std::ios::in | std::ios::binary);

	if (!bmHandle.is_open())
	{
		std::cout << file << " failed: file not found" << std::endl;
		return false;
}

	bmHandle.read((char*)&bmfh, sizeof(bmfh));

	if (bmfh.bfType != 19778) // 'BM' magic
	{
		std::cout << file << " failed: wrong file header" << std::endl;
		return false;
	}

	bmHandle.read((char*)&bmih, sizeof(bmih));

	if (bmih.biBitCount != 24)
	{
		std::cout << file << " failed: only 24bpp bitmaps" << std::endl;
		return false;
	}

	bmWidth = bmih.biWidth;
	bmHeight = bmih.biHeight;
	bmSize = (bmih.biWidth*bmih.biHeight*(unsigned)(bmih.biBitCount / 8.0));

	data = new char[bmSize];

	bmHandle.read(data, bmSize);
	bmHandle.close();

	//swap colors: BGR -> RGB
	for (unsigned i = 0; i < bmSize; i = i + 3)
	{
		tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}

	return true;
}


