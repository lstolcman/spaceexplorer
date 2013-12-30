#pragma once

#include "../tools/math.hpp"


class COBJ
{
	//Fields:
private:
	struct SFace {
		int v[3];
		int n[3];
		int t[3];
	};
	std::ifstream		obj;
	GLuint				handle;
public:


	//Members:
private:

public:
	COBJ(void);
	~COBJ();

	bool				loadObj(std::string);
	void				disp(void);


};




















