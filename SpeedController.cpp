// 
// 
// 

#include "SpeedController.h"

SpeedController::SpeedController(float Kp, float Kd)
	: Kp(Kp), Kd(Kd), prevError(0), prevOutput(0)
{
}

int SpeedController::calcPidTerm(int setPoint, int curValue)
{
	if (setPoint <= 1)
	{
		prevOutput = 0;
		return 0;
	}
	else
	{
		int error = abs(setPoint) - abs(curValue);
		float pidTerm = (Kp * error) + (Kd * (error - prevError));
		prevError = error;
		int output = constrain(prevOutput + int(pidTerm), 0, 255);
		prevOutput = output;
		return output;
	}
}