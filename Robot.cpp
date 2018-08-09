// 
// 
// 

#include "Robot.h"

Robot::Robot()
	:timer(1000/LOOPFREQ), motor(4,5,3,2.5,1.5), oscilloscope(7)
{
}

void Robot::run()
{
	oscilloscope.checkButton();
	if (timer.fire())
	{
		int motorSpeed = analogRead(POTPIN) / 25;
		motor.driveConstantSpeed(motorSpeed);

		if (oscilloscope.getSampling_on())
		{
			noInterrupts();
			oscilloscope.setSensorReading(0, motor.getSpeed_req());
			oscilloscope.setSensorReading(1, motor.getSpeed());
			oscilloscope.setSensorReading(2, motor.getPWM_val());
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

void Robot::handleEncoder()
{
	motor.handleEncoder();
}

