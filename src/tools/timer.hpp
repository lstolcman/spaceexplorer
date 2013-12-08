#pragma once

class CTimer
{
public:
	CTimer();
	~CTimer();

	void        start();
	void        stop();

	unsigned    getElapsedMilliseconds();
	float       getElapsedSeconds();

	bool operator()();


private:
	bool               isStopped;
	unsigned long long timer_start, timer_end;


};
