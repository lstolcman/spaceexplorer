#include "stdafx.hpp"
#include "texture.hpp"




CTexture::CTexture(void)
{
	handle = NULL;
}

CTexture::CTexture(std::string file, int magFilter, int minFilter)
{
	Load(file, magFilter, minFilter);
}

CTexture::~CTexture(void)
{
	glDeleteTextures(1, &handle);
}

GLuint CTexture::Load(std::string file, int magFilter, int minFilter)
{
	Bitmap *texture = new Bitmap;
	if (!texture->loadBMP((char*)file.c_str()))
	{
		std::cout << "Error loading texture " << file << "!" << endl;
		return -1;
	}

	// Utworzenie nowego id wolnej tekstury
	glGenTextures(1, &handle);

	// "Bindowanie" tekstury o nowoutworzonym id
	glBindTexture(GL_TEXTURE_2D, handle);

	// Okre�lenie parametr�w filtracji dla tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter); // Filtracja, gdy tekstura jest powi�kszana
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter); // Filtracja, gdy tekstura jest pomniejszana

	// Wys�anie tekstury do pami�ci karty graficznej zale�nie od tego, czy chcemy korzysta� z mipmap czy nie
	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST) {
		// Automatyczne zbudowanie mipmap i wys�anie tekstury do pami�ci karty graficznej
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, texture->width, texture->height, GL_RGB, GL_UNSIGNED_BYTE, texture->data);
	}
	else {
		// Wys�anie tekstury do pami�ci karty graficznej 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);
	}

	// Zwolnienie pami�ci, usuni�cie bitmapy z pami�ci - bitmapa jest ju� w pami�ci karty graficznej
	delete texture;

	// Zwr�cenie id tekstury
	return handle;
}


GLuint CTexture::operator()()
{
	return handle;
}






