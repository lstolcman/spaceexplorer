#pragma once

class CTimer
{
public:
	CTimer(void);
	~CTimer();

	void        start(void);
	void        reset(void);
	void        stop(void);

	unsigned    getElapsedMilliseconds(void);
	float       getElapsedSeconds(void);

	bool operator()();


private:
	bool               isStopped;
	unsigned long long timer_start, timer_end;


};
