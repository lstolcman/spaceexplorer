#pragma once






class CShader
{
	//Fields:
private:
	GLuint			handle;
	bool			loaded;
	bool			compiled;
	std::string		vertexCode;
	std::string		fragmentCode;
	std::string		vertexFile;
	std::string		fragmentFile;

public:



	//Members:
private:


public:
	CShader(void);
	~CShader();

	void			loadShader(std::string);
	void			compileShader(void);
	void			useShader(void);


};































