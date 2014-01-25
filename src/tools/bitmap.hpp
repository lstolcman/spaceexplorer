#pragma once



class CLoaderBitmap
{
	//Fields:
private:
	FIBITMAP			*bmHandle;
	FREE_IMAGE_FORMAT	bmFmt;
public:
	unsigned			bmWidth;
	unsigned			bmHeight;
	BYTE				*data;

	//Members:
private:

public:
	CLoaderBitmap(void);
	~CLoaderBitmap();

	bool				loadBitmap(std::string);
	bool				unloadBitmap(void);

};












