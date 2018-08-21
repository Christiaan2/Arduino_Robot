// SpeedController.h

#ifndef SPEEDCONTROLLER_H
#define SPEEDCONTROLLER_H
#include "Arduino.h"

class SpeedController
{
private:
	float Kp;
	float Kd;
	float prevError;
	int prevOutput;
public:
	SpeedController(float Kp, float Kd);
	int calcPidTerm(int setPoint, int curValue);
	void reset();
};


#endif

