// Robot.h

#ifndef ROBOT_H
#define ROBOT_H
#include "Arduino.h"
#include "Timer.h"
#include "Motor.h"
#include "Oscilloscope.h"

#define POTPIN 5  //Pin where potentiometer is connected to
#define LOOPFREQ 10  //Frequency of main loop

class Robot
{
private:
	Timer timer;
	Motor motorL;
	Motor motorR;
	Oscilloscope oscilloscope;

	Motor* motorArray[2]; //TEMPERARY

public:
	Robot();
	void run();
	void initialize();
	Motor* getPointerToMotorL();
	Motor* getPointerToMotorR();
};

#endif

