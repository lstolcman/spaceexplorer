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
	bmHandle.open(file, std::ios::in | std::ios::binary);

	bmHandle.read((char*)&bmfh, sizeof(bmfh));

	if (bmfh.bfType != 19778) // 'BM' magic
	{
		std::cout << file << ": Wrong file header, cancelled" << std::endl;
		return false;
	}

	bmHandle.read((char*)&bmih, sizeof(bmih));

	if (bmih.biBitCount != 24)
	{
		std::cout << file << ": Only 24bpp bitmaps, cancelled" << std::endl;
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
		char tmp;
		tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}

	return true;
}


