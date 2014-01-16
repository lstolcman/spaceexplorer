#pragma once





struct SFace {
	unsigned v[3];
	unsigned t[3];
	unsigned n[3];
};

struct SObjFile
{
	std::vector<glm::vec3> *v;
	std::vector<glm::vec2> *t;
	std::vector<glm::vec3> *n;
	std::vector<SFace> *f;
	glm::vec3 amb;
	glm::vec3 dif;
	glm::vec3 spe;
	std::string map_Kd;
};




































