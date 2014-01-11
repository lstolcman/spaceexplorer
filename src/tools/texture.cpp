#include "stdafx.hpp"
#include "texture.hpp"




CTexture::CTexture(SData *data)
{
	this->data = data;
	handle = NULL;
	loaded = false;
}


CTexture::CTexture(void)
{
	this->data = NULL;
	handle = NULL;
	loaded = false;
}



CTexture::~CTexture(void)
{
	glDeleteTextures(1, &handle);
}

GLuint CTexture::Load(std::string file)
{
	return Load(file, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
}
GLuint CTexture::Load(std::string file, int magFilter, int minFilter)
{
	CLoaderBMP *texture = new CLoaderBMP;
	if (!texture->loadBMP(file))
	{
		std::cout << "Error loading texture: " << file << "!" << std::endl;
		MessageBox(0, ("Error loading: "+file).c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(-1);
		return -1;
	}

	// Utworzenie nowego id wolnej tekstury
	glGenTextures(1, &handle);


	glActiveTexture(GL_TEXTURE0);
	// "Bindowanie" tekstury o nowoutworzonym id
	glBindTexture(GL_TEXTURE_2D, handle);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Okre�lenie parametr�w filtracji dla tekstury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter); // Filtracja, gdy tekstura jest powi�kszana
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter); // Filtracja, gdy tekstura jest pomniejszana

	// Wys�anie tekstury do pami�ci karty graficznej zale�nie od tego, czy chcemy korzysta� z mipmap czy nie
	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST)
	{
		// Automatyczne zbudowanie mipmap i wys�anie tekstury do pami�ci karty graficznej
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, texture->bmWidth, texture->bmHeight, GL_RGB, GL_UNSIGNED_BYTE, texture->data);
	}
	else
	{
		// Wys�anie tekstury do pami�ci karty graficznej 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->bmWidth, texture->bmHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);
	}

	// Zwolnienie pami�ci, usuni�cie bitmapy z pami�ci - bitmapa jest ju� w pami�ci karty graficznej
	delete texture;
	std::cout << "loaded: " << file << std::endl;
	// Zwr�cenie id tekstury
	return handle;
}


GLuint CTexture::operator()()
{
	return handle;
}






