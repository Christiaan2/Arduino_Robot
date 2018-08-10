// 
// 
// 

#include "Robot.h"

Robot::Robot()
	:timer(1000/LOOPFREQ), motorL(4,5,2,2.5,1.5), motorR(7,6,3,2.5,1.5), oscilloscope(8)
{
	pinMode(9, INPUT);	//TEMPERARY
	motorArray[0] = &motorL;
	motorArray[1] = &motorR;
}

void Robot::run()
{
	oscilloscope.checkButton();

	if (timer.fire())
	{
		int motorNumber; //TEMPERARY
		int motorSpeed = analogRead(POTPIN) / 25;

		if (digitalRead(9) == HIGH) //TEMPERARY
		{
			motorNumber = 0;
		}
		else
		{
			motorNumber = 1;
		}

		motorArray[motorNumber]->driveConstantSpeed(motorSpeed);

		if (oscilloscope.getSampling_on())
		{
			noInterrupts();
			oscilloscope.setSensorReading(0, motorArray[motorNumber]->getSpeed_req());
			oscilloscope.setSensorReading(1, motorArray[motorNumber]->getSpeed());
			oscilloscope.setSensorReading(2, motorArray[motorNumber]->getPWM_val());
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
	return motorL.getPointer();
}

Motor* Robot::getPointerToMotorR()
{
	return motorR.getPointer();
}