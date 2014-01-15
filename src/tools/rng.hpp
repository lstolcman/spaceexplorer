#pragma once



class CRng
{
public:
	CRng(void);
	~CRng();
	


	float operator()(float);
	float operator()(float, float);
	float operator()(std::string, float);
	float operator()(std::string, float, float);


private:
	bool               isStopped;
	unsigned long long timer_start, timer_end;


};

























