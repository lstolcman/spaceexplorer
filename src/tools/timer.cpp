#include "stdafx.hpp"
#include "timer.hpp"



CTimer::CTimer(void)
{
	timer_start = 0;
	timer_end   = 0;
	isStopped   = true;
}

CTimer::~CTimer()
{
}

void CTimer::start(void)
{
	timer_start = GetTickCount64();
	timer_end   = 0;
	isStopped   = false;
}

void CTimer::reset(void)
{
	this->start();
}

void CTimer::stop(void)
{
	timer_end = GetTickCount64();
	isStopped = true;
}




unsigned CTimer::getElapsedMilliseconds(void)
{
	timer_end = GetTickCount64();
	return static_cast<unsigned>(timer_end - timer_start);
}

float CTimer::getElapsedSeconds(void)
{
	return getElapsedMilliseconds() / 1000.0f;
}


bool CTimer::operator()()
{
	return isStopped;
}
