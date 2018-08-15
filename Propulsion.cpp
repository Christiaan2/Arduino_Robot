// 
// 
// 

#include "Propulsion.h"

Propulsion::Propulsion()
	:motorL(4, 5, 2, 2.5, 1.5), motorR(7, 6, 3, 2.5, 1.5), SumError(0)
{
	motorL.setDistance(548);
	motorR.setDistance(548);
}

void Propulsion::setForwards(int speed)
{
	motorL.setDirection(true);
	motorR.setDirection(true);
	motorL.setSpeed(speed);
	motorR.setSpeed(speed);
	motorL.setInitialSpeed(speed);
	motorR.setInitialSpeed(speed);
	//motorL.getPointerToEncoder()->reset();
	//motorR.getPointerToEncoder()->reset();
}

void Propulsion::setBackwards(int speed)
{
	motorL.setDirection(false);
	motorR.setDirection(false);
	motorL.setSpeed(speed);
	motorR.setSpeed(speed);
}

bool Propulsion::drive()
{
	bool resultL = true;
	bool resultR = true;
	if (motorL.getDistance() - int(motorL.getPointerToEncoder()->getEncoderTicks()) <=
		min(140, motorL.getInitialSpeed() * 15))
	{
		if (motorL.getDistance() - int(motorL.getPointerToEncoder()->getEncoderTicks()) <= 0)
		{
			motorL.setSpeed(0);
			resultL = false;
		}
		else
		{
			//motorL.setSpeed(max(2,((motorL.getDistance() - int(motorL.getPointerToEncoder()->getEncoderTicks()))
			//	* motorL.getInitialSpeed()) / (motorL.getInitialSpeed() * 15)));
			motorL.setSpeed(2);
		}
	}

	if (motorR.getDistance() - int(motorR.getPointerToEncoder()->getEncoderTicks()) <=
		min(140, motorR.getInitialSpeed() * 15))
	{
		if (motorR.getDistance() - int(motorR.getPointerToEncoder()->getEncoderTicks()) <= 0)
		{
			motorR.setSpeed(0);
			resultR = false;
		}
		else
		{
			//motorR.setSpeed(max(2,((motorR.getDistance() - int(motorR.getPointerToEncoder()->getEncoderTicks()))
			//	* motorR.getInitialSpeed()) / (motorR.getInitialSpeed() * 15)));
			motorR.setSpeed(2);
		}
	}

	int PWML = motorL.calcPWM_val();
	int PWMR = motorR.calcPWM_val();
	
	int error = int(motorL.getPointerToEncoder()->getEncoderTicks() -
		motorR.getPointerToEncoder()->getEncoderTicks());
	SumError = SumError + error;
	int prevError = int(motorL.getPointerToEncoder()->getPrevEncoderTicks() -
		motorR.getPointerToEncoder()->getPrevEncoderTicks());
	int boost = (KP_CONST_SPEED * error) + (KD_CONST_SPEED * (error - prevError))
		+ (KI_CONST_SPEED * SumError);
	PWML = PWML - boost;
	PWMR = PWMR + boost;

	
	//if (motorL.getDistance() - int(motorL.getPointerToEncoder()->getEncoderTicks()) <= 0)
	//{
	//	PWML = 0;
	//	result = false;
	//}
	//else
	//{
	//	int errorL = motorL.getDistance() - int(motorL.getPointerToEncoder()->getEncoderTicks());
	//	PWML = min(PWML, 3*errorL + 95);
	//}
	
	//if (motorR.getDistance() - int(motorR.getPointerToEncoder()->getEncoderTicks()) <= 0)
	//{
	//	PWMR = 0;
	//	result = false;//Both engines should return false
 	//}
	//else
	//{
	//	int errorR = motorR.getDistance() - int(motorR.getPointerToEncoder()->getEncoderTicks());
	//	PWMR = min(PWMR, 3*errorR + 95);
	//}
	
	motorL.setPWM_val(PWML);
	motorR.setPWM_val(PWMR);
	return resultL || resultR;
	//Not satisfied with this function yet. When speed one engine is lower otherone also decreases!!!!!
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
	SumError = 0;
}