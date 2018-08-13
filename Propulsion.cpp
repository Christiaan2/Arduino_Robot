// 
// 
// 

#include "Propulsion.h"

Propulsion::Propulsion()
	:motorL(4, 5, 2, 2.5, 1.5), motorR(7, 6, 3, 2.5, 1.5)
{
}

void Propulsion::setForwards(int speed)
{
	motorL.setDirection(true);
	motorR.setDirection(true);
	motorL.setSpeed(speed);
	motorR.setSpeed(speed);
	//motorL.getPointerToEncoder()->reset();
	//motorR.getPointerToEncoder()->reset();
}

bool Propulsion::drive()
{
	int PWML = motorL.calcPWM_val();
	int PWMR = motorR.calcPWM_val();
	
	int error = int(motorL.getPointerToEncoder()->getEncoderTicks() -
		motorR.getPointerToEncoder()->getEncoderTicks());
	int prevError = int(motorL.getPointerToEncoder()->getPrevEncoderTicks() -
		motorR.getPointerToEncoder()->getPrevEncoderTicks());
	int boost = int((10 * error) + (8 * (error - prevError)));
	motorL.setPWM_val(PWML - boost);
	motorR.setPWM_val(PWMR + boost);
	return true;
}

Motor* Propulsion::getPointerToMotorL()
{
	return motorL.getPointer();
}

Motor* Propulsion::getPointerToMotorR()
{
	return motorR.getPointer();
}