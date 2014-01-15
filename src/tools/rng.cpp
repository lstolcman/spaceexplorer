#include "stdafx.hpp"
#include "rng.hpp"



CRng::CRng(void)
{
}


CRng::~CRng(void)
{

}

float CRng::operator()(float end)
{
	if (end < 0) //gen (end, 0]
	{
		return ((rand() << 16 | rand()) % (int)end);
	}
	else //gen [0, end)
	{
		return ((rand() << 16 | rand()) % (int)end) - end;
	}
}


float CRng::operator()(float start, float end)
{
	if (start == end)
	{
		float tmp = start;
		start = end;
		end = start;
	}
	//gen (start, end)
	if (start < 0)
	{
		return ((rand() << 16 | rand()) % (int)(end - start)) + start;
	}
	else
	{
		return ((rand() << 16 | rand()) % (int)(end - start)) + start;
	}
}

float CRng::operator()(std::string fmt, float end)
{
	if (fmt == "d") // discrete values
	{
		if (end < 0) //gen (end, 0]
		{
			return ((rand() << 16 | rand()) % (int)end);
		}
		else //gen [0, end)
		{
			return ((rand() << 16 | rand()) % (int)end) - (int)end;
		}
	}
	else if (fmt == "nz") //non-zero values
	{
		if (end < 0) //gen (end, 0]
		{
			float r;
			do
			{
				r = ((rand() << 16 | rand()) % (int)end);
			} while (abs(r) < 0.001f);
			return r;
		}
		else //gen [0, end)
		{
			float r;
			do
			{
				r = ((rand() << 16 | rand()) % (int)end) - end;
			} while (abs(r) < 0.001f);
			return r;
		}
	}
	else
	{
		if (end < 0) //gen (end, 0]
		{
			return ((rand() << 16 | rand()) % (int)end);
		}
		else //gen [0, end)
		{
			return ((rand() << 16 | rand()) % (int)end) - end;
		}
	}

}


float CRng::operator()(std::string fmt, float start, float end)
{
	if (start == end)
	{
		float tmp = start;
		start = end;
		end = start;
	}
	if (fmt == "d")	//discrete values
	{
		//gen (start, end)
		if (start < 0)
		{
			return ((rand() << 16 | rand()) % (int)(end - start)) + (int)start;
		}
		else
		{
			return ((rand() << 16 | rand()) % (int)(end - start)) - (int)start;
		}
	}
	else if (fmt == "nz") //without zero
	{
		//gen (start, end)
		if (start < 0)
		{
			float r;
			do
			{
				r = ((rand() << 16 | rand()) % (int)(end - start)) + start;
			}
			while (abs(r) < 0.001f);
			return r;
		}
		else
		{
			float r;
			do
			{
				r = ((rand() << 16 | rand()) % (int)(end - start)) - start;
			}
			while (abs(r) < 0.001f);
			return r;
		}
	}
	else
	{
		//gen (start, end)
		if (start < 0)
		{
			return ((rand() << 16 | rand()) % (int)(end - start)) + start;
		}
		else
		{
			return ((rand() << 16 | rand()) % (int)(end - start)) - start;
		}
	}
}






























