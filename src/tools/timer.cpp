#include "stdafx.hpp"
#include "timer.hpp"



CTimer::CTimer()
{
	timer_start = 0;
	timer_end   = 0;
	isStopped   = true;
}

CTimer::~CTimer()
{
}

void CTimer::start()
{
	timer_start = GetTickCount64();
	timer_end   = 0;
	isStopped   = false;
}

void CTimer::stop()
{
	timer_end = GetTickCount64();
	isStopped = true;
}




unsigned CTimer::getElapsedMilliseconds()
{
	timer_end = GetTickCount64();
	return static_cast<unsigned>(timer_end - timer_start);
}

float CTimer::getElapsedSeconds()
{
	return getElapsedMilliseconds() / 1000.0;
}


bool CTimer::operator()()
{
	return isStopped;
}
