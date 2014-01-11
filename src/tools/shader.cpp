#include "stdafx.hpp"
#include "shader.hpp"






CShader::CShader(void)
{
	loaded = false;
	compiled = false;
}


CShader::~CShader()
{

}


void CShader::loadShader(std::string shader)
{
	vertexFile = shader + ".vert";
	fragmentFile = shader + ".frag";

	std::string line;

	// Read the Vertex Shader code from the file
	std::ifstream vertexShaderStream("resources/shaders/" + shader + ".vert", std::ios::in);
	if (vertexShaderStream.is_open())
	{
		while (getline(vertexShaderStream, line))
			vertexCode += "\n" + line;

		vertexCode += "\0";
		vertexShaderStream.close();
	}
	else
	{
		MessageBox(0, ("Error loading file:\nresources/shaders/" + shader + ".vert").c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	// Read the Fragment Shader code from the file
	std::ifstream fragmentShaderStream("resources/shaders/" + shader + ".frag", std::ios::in);
	if (fragmentShaderStream.is_open())
	{
		while (getline(fragmentShaderStream, line))
			fragmentCode += "\n" + line;

		fragmentCode += "\0";
		fragmentShaderStream.close();
	}
	else
	{
		MessageBox(0, ("Error loading file:\nresources/shaders/" + shader + ".frag").c_str(), "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	loaded = true;

}


void CShader::compileShader(void)
{
	if (loaded == false)
	{
		MessageBox(0, "Shaders not loaded", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Create the shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);


	// Compile Vertex Shader
	std::cout << "Compiling shader " << vertexFile << std::endl;
	char const *vertexSourcePointer = vertexCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
	glCompileShader(vertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> vertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(vertexShaderID, InfoLogLength, NULL, &vertexShaderErrorMessage[0]);
	std::cout << &vertexShaderErrorMessage[0] << std::endl;

	// Compile Fragment Shader
	std::cout << "Compiling shader " << fragmentFile << std::endl;
	char const *fragmentSourcePointer = fragmentCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> fragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(fragmentShaderID, InfoLogLength, NULL, &fragmentShaderErrorMessage[0]);
	std::cout << &fragmentShaderErrorMessage[0] << std::endl;

	// Link the program
	std::cout << "Linking program" << std::endl;
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)));
	glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	std::cout << &ProgramErrorMessage[0] << std::endl;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	handle = programID;
	compiled = true;
}



void CShader::useShader(void)
{
	if (compiled == false)
	{
		MessageBox(0, "Shader not compiled", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	if (loaded)
		glUseProgram(handle);
	else
		std::cout << "Warning! Shader not loaded" << std::endl;
}















