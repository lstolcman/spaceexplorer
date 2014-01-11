#pragma once


struct SFace {
	unsigned v[3];
	unsigned t[3];
	unsigned n[3];
};

struct SObjFile
{
	std::vector<glm::vec3> *v = new std::vector<glm::vec3>();
	std::vector<glm::vec2> *t = new std::vector<glm::vec2>();
	std::vector<glm::vec3> *n = new std::vector<glm::vec3>();
	std::vector<SFace> *f = new std::vector<SFace>();
	glm::vec3 amb;
	glm::vec3 dif;
	glm::vec3 spe;
	std::string map_Kd;
};




































