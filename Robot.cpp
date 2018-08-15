// 
// 
// 

#include "Robot.h"

Robot::Robot()
	:timer(1000/LOOPFREQ), oscilloscope(8)
{
}

void Robot::run()
{
	oscilloscope.checkButton();

	if (timer.fire())
	{
		int motorSpeed = analogRead(POTPIN) / 45;

		if (motorSpeed <= 1)
		{
			propulsion.getPointerToMotorL()->getPointerToEncoder()->reset();
			propulsion.getPointerToMotorR()->getPointerToEncoder()->reset();
			propulsion.resetSumError();
		}

		propulsion.setForwards(motorSpeed);
		propulsion.drive();		

		if (oscilloscope.getSampling_on())
		{
			noInterrupts();
			//oscilloscope.setSensorReading(0, int(propulsion.getPointerToMotorL()->getPointerToEncoder()->getEncoderTicks()));
			//oscilloscope.setSensorReading(1, int(propulsion.getPointerToMotorR()->getPointerToEncoder()->getEncoderTicks()));
			
			oscilloscope.setSensorReading(0, int(propulsion.getPointerToMotorL()->getPointerToEncoder()->getEncoderTicks()));
			oscilloscope.setSensorReading(1, int(propulsion.getPointerToMotorR()->getPointerToEncoder()->getEncoderTicks()));
			oscilloscope.setSensorReading(2, propulsion.getPointerToMotorL()->getPWM_val());
			oscilloscope.setSensorReading(3, propulsion.getPointerToMotorR()->getPWM_val());
			oscilloscope.setSensorReading(4, propulsion.getPointerToMotorL()->getSpeed());
			oscilloscope.setSensorReading(5, propulsion.getPointerToMotorL()->getPointerToEncoder()->getSpeed());
			oscilloscope.setSensorReading(6, propulsion.getPointerToMotorR()->getPointerToEncoder()->getSpeed());
			//oscilloscope.setSensorReading(0, motorArray[motorNumber]->getSpeed_req());
			//oscilloscope.setSensorReading(1, motorArray[motorNumber]->getSpeed());
			//oscilloscope.setSensorReading(2, motorArray[motorNumber]->getPWM_val());
			oscilloscope.setTime();
			interrupts();
			oscilloscope.sendData();
		}
	}
}

void Robot::initialize()
{
	oscilloscope.initializeSerial();
}

Motor* Robot::getPointerToMotorL()
{
	return propulsion.getPointerToMotorL();
}

Motor* Robot::getPointerToMotorR()
{
	return propulsion.getPointerToMotorR();
}