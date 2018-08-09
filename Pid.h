// Pid.h

#ifndef PID_H
#define PID_H
#include "Arduino.h"

class Pid
{
private:
	float Kp;
	float Kd;
	float prevError;
	int prevOutput;
public:
	Pid(float Kp, float Kd);
	int calcPidTerm(int setPoint, int curValue);
};


#endif

