#include "stdafx.hpp"
#include "obj.hpp"





COBJ::COBJ(void)
{


}



COBJ::~COBJ()
{

}

void COBJ::loadObj(std::string file)
{
	std::string line;

	obj.open(file, std::ios::in);

	while (std::getline(obj, line))
	{

	}


}















