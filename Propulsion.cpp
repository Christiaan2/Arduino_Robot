// 
// 
// 

#include "Propulsion.h"

Propulsion::Propulsion()
	:motorL(4, 5, 2, 4.0, 2.5), motorR(7, 6, 3, 4.0, 2.5), sumError(0), progress(0), allowSpeedControll(true)
{
}

void Propulsion::setForwards(int distance = 0)
{
	motorL.setDirection(true);
	motorR.setDirection(true);
	motorL.setDistance(distance); // distance = 0 corresponds to infinity, distance in #pulses
	motorR.setDistance(distance);
}

void Propulsion::setBackwards(int distance = 0)
{
	motorL.setDirection(false);
	motorR.setDirection(false);
	motorL.setDistance(distance); // distance = 0 corresponds to infinity, distance in #pulses
	motorR.setDistance(distance);
}

void Propulsion::setSpeed(int speed)
{
	motorL.setSpeed(speed);
	motorR.setSpeed(speed);
}

void Propulsion::setAllowSpeedControl(bool allowSpeedControll)
{
	this->allowSpeedControll = allowSpeedControll;
}

bool Propulsion::getAllowSpeedControll()
{
	return allowSpeedControll;
}

bool Propulsion::drive()
{
	bool resultL = false;
	bool resultR = false;

	if (motorL.getSpeed() == 0 && motorR.getSpeed() == 0)
	{
		reset();
		return false;
	}

	if (motorL.getDistance() - int(motorL.getPointerToEncoder()->getEncoderTicks()) <=
		min(140, motorL.getSpeed() * 15) && motorL.getDistance() != 0)
	{
		if (motorL.getDistance() - int(motorL.getPointerToEncoder()->getEncoderTicks()) <= 0)
		{
			motorL.setSpeed(0);
			resultL = true;
		}
		else
		{
			motorL.setSpeed(2);
		}
	}

	if (motorR.getDistance() - int(motorR.getPointerToEncoder()->getEncoderTicks()) <=
		min(140, motorR.getSpeed() * 15) && motorR.getDistance() != 0)
	{
		if (motorR.getDistance() - int(motorR.getPointerToEncoder()->getEncoderTicks()) <= 0)
		{
			motorR.setSpeed(0);
			resultR = true;
		}
		else
		{
			motorR.setSpeed(2);
		}
	}

	int PWML = motorL.calcPWM_val();
	int PWMR = motorR.calcPWM_val();
	
	int error = int(motorL.getPointerToEncoder()->getEncoderTicks() -
		motorR.getPointerToEncoder()->getEncoderTicks());
	sumError = sumError + error;
	int prevError = int(motorL.getPointerToEncoder()->getPrevEncoderTicks() -
		motorR.getPointerToEncoder()->getPrevEncoderTicks());
	int boost = (KP * error) + (KD * (error - prevError))
		+ (KI * sumError);
	PWML = PWML - boost;
	PWMR = PWMR + boost;
	
	motorL.setPWM_val(PWML);
	motorR.setPWM_val(PWMR);
	return resultL && resultR;
}

void Propulsion::setLeftRotation(int distance)
{
	motorL.setDirection(true);
	motorR.setDirection(false);
	motorL.setDistance(distance); // distance = 0 corresponds to infinity, distance in #pulses
	motorR.setDistance(distance);
}

void Propulsion::setRightRotation(int distance)
{
	motorL.setDirection(false);
	motorR.setDirection(true);
	motorL.setDistance(distance); // distance = 0 corresponds to infinity, distance in #pulses
	motorR.setDistance(distance);
}

Motor* Propulsion::getPointerToMotorL()
{
	return motorL.getPointer();
}

Motor* Propulsion::getPointerToMotorR()
{
	return motorR.getPointer();
}

void Propulsion::resetSumError()
{
	sumError = 0;
}

void Propulsion::reset()
{
	getPointerToMotorL()->reset();
	getPointerToMotorR()->reset();
	sumError = 0;
	allowSpeedControll = true;
}

void Propulsion::stopMotors()
{
	motorL.setPWM_val(0);
	motorR.setPWM_val(0);
	//Not finished
}

void Propulsion::setProgress(int progress)
{
	this->progress = progress;
}

int Propulsion::getProgress()
{
	return progress;
}

void Propulsion::incrementProgress()
{
	progress++;
}