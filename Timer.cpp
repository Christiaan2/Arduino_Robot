// 
// 
// 

#include "Timer.h"

Timer::Timer(int frequency)
	: frequency(frequency)
{
	prevTime = millis();
}

bool Timer::fire()
{
	unsigned long curTime = millis();
	if (int(curTime - prevTime) >= frequency)
	{
		prevTime = curTime;
		return true;
	}
	else
	{
		return false;
	}
}

Timer::~Timer()
{
}

