#pragma once



class CLoaderBMP
{
	//Fields:
private:
	BITMAPFILEHEADER	bmfh;
	BITMAPINFOHEADER	bmih;
	std::ifstream		bmHandle;
public:
	unsigned			bmWidth;
	unsigned			bmHeight;
	char				*data;

	//Members:
private:

public:
	//CLoaderBMP(std::string);
	CLoaderBMP(void);
	~CLoaderBMP();

	bool				loadBMP(std::string);

};












