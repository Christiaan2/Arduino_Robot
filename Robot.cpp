// 
// 
// 

#include "Robot.h"

Robot::Robot()
	:timer(1000 / LOOPFREQ), oscilloscope(8), collisionAvoidance(11, 12, 100), progress(0)
{
}

void Robot::run()
{
	oscilloscope.checkButton();

	if (timer.fire())
	{
		int motorSpeed = analogRead(POTPIN) / 45;
		//Serial.println(motorSpeed);
		if (motorSpeed <= 1)
		{
			propulsion.reset();
			progress = 0;
		}

		//collisionAvoidance.run(&propulsion, motorSpeed);
		if (progress == 0)
		{
			propulsion.setForwards(motorSpeed,540);
		}
		else if (progress == 1)
		{
			propulsion.setBackwards(motorSpeed,540);
		}
		else if (progress == 2)
		{
			propulsion.setLeftRotation(motorSpeed,100);
		}
		else if (progress == 3)
		{
			propulsion.setRightRotation(motorSpeed, 100);
		}
		else
		{
			delay(500);
		}
	
		if (!propulsion.drive())
		{
			progress++;
			propulsion.reset();
		//	propulsion.getPointerToMotorL()->getPointerToEncoder()->reset();
		//	propulsion.getPointerToMotorR()->getPointerToEncoder()->reset();
		//	propulsion.resetSumError();
		//	delay(500);
		}

		if (oscilloscope.getSampling_on())
		{
			noInterrupts();
			oscilloscope.setSensorReading(0, int(propulsion.getPointerToMotorL()->getPointerToEncoder()->getEncoderTicks()));
			oscilloscope.setSensorReading(1, int(propulsion.getPointerToMotorR()->getPointerToEncoder()->getEncoderTicks()));
			oscilloscope.setSensorReading(2, propulsion.getPointerToMotorL()->getPWM_val());
			oscilloscope.setSensorReading(3, propulsion.getPointerToMotorR()->getPWM_val());
			oscilloscope.setSensorReading(4, propulsion.getPointerToMotorL()->getSpeed());
			oscilloscope.setSensorReading(5, propulsion.getPointerToMotorL()->getPointerToEncoder()->getSpeed());
			oscilloscope.setSensorReading(6, propulsion.getPointerToMotorR()->getPointerToEncoder()->getSpeed());
			oscilloscope.setTime();
			interrupts();
			oscilloscope.sendData();
		}
	}
}

void Robot::initialize()
{
	oscilloscope.initializeSerial();
	collisionAvoidance.initialize(9);
}

Motor* Robot::getPointerToMotorL()
{
	return propulsion.getPointerToMotorL();
}

Motor* Robot::getPointerToMotorR()
{
	return propulsion.getPointerToMotorR();
}