// Robot.h

#ifndef ROBOT_H
#define ROBOT_H
#include "Arduino.h"
#include "Timer.h"
#include "Propulsion.h"
#include "Oscilloscope.h"
#include "CollisionAvoidance.h"

#define POTPIN 5  //Pin where potentiometer is connected to
#define DRIVEFREQ 10  //Frequency of main loop
#define SCOOPFREQ 100
#define ACSFREQ 25

class Robot
{
private:
	Timer timerDrive;
	Timer timerScoop;
	Timer timerACS;
	Oscilloscope oscilloscope;
	Propulsion propulsion;
	CollisionAvoidance collisionAvoidance;
public:
	Robot();
	void run();
	void initialize();
	Motor* getPointerToMotorL();
	Motor* getPointerToMotorR();
};

#endif

