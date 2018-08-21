// 
// 
// 

#include "Propulsion.h"

Propulsion::Propulsion()
	:motorL(4, 5, 2, 2.5, 1.5), motorR(7, 6, 3, 2.5, 1.5), sumError(0)
{
}

void Propulsion::setForwards(int speed, int distance)
{
	motorL.setDirection(true);
	motorR.setDirection(true);
	motorL.setSpeed(speed);
	motorR.setSpeed(speed);
	motorL.setInitialSpeed(speed);
	motorR.setInitialSpeed(speed);
	motorL.setDistance(distance); // distance = 0 corresponds to infinity, distance in #pulses
	motorR.setDistance(distance);
}

void Propulsion::setBackwards(int speed, int distance)
{
	motorL.setDirection(false);
	motorR.setDirection(false);
	motorL.setSpeed(speed);
	motorR.setSpeed(speed);
	motorL.setInitialSpeed(speed);
	motorR.setInitialSpeed(speed);
	motorL.setDistance(distance); // distance = 0 corresponds to infinity, distance in #pulses
	motorR.setDistance(distance);
}

bool Propulsion::drive()
{
	bool resultL = true;
	bool resultR = true;

	if (motorL.getSpeed() == 0 && motorR.getSpeed() == 0)
	{
		reset();
		return true;
	}

	if (motorL.getDistance() - int(motorL.getPointerToEncoder()->getEncoderTicks()) <=
		min(140, motorL.getInitialSpeed() * 15) && motorL.getDistance() != 0)
	{
		if (motorL.getDistance() - int(motorL.getPointerToEncoder()->getEncoderTicks()) <= 0)
		{
			motorL.setSpeed(0);
			resultL = false;
		}
		else
		{
			motorL.setSpeed(2);
		}
	}

	if (motorR.getDistance() - int(motorR.getPointerToEncoder()->getEncoderTicks()) <=
		min(140, motorR.getInitialSpeed() * 15) && motorR.getDistance() != 0)
	{
		if (motorR.getDistance() - int(motorR.getPointerToEncoder()->getEncoderTicks()) <= 0)
		{
			motorR.setSpeed(0);
			resultR = false;
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
	return resultL || resultR;
}

void Propulsion::setLeftRotation(int speed, int distance)
{
	motorL.setDirection(true);
	motorR.setDirection(false);
	motorL.setSpeed(speed);
	motorR.setSpeed(speed);
	motorL.setInitialSpeed(speed);
	motorR.setInitialSpeed(speed);
	motorL.setDistance(distance); // distance = 0 corresponds to infinity, distance in #pulses
	motorR.setDistance(distance);
}

void Propulsion::setRightRotation(int speed, int distance)
{
	motorL.setDirection(false);
	motorR.setDirection(true);
	motorL.setSpeed(speed);
	motorR.setSpeed(speed);
	motorL.setInitialSpeed(speed);
	motorR.setInitialSpeed(speed);
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
}

void Propulsion::stopMotors()
{
	motorL.setPWM_val(0);
	motorR.setPWM_val(0);
	//Not finished
}