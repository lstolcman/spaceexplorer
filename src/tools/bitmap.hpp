#pragma once



class CBitmap
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
	//CBitmap(std::string);
	CBitmap(void);
	~CBitmap();

	bool				loadBMP(std::string);

};












