// Propulsion.h

#ifndef PROPULSION_H
#define PROPULSION_H
#include "Arduino.h"
#include "Motor.h"

#define KP 6
#define KD 5
#define KI 1

class Propulsion
{
private:
	Motor motorL;
	Motor motorR;
	int sumError;
public:
	enum driveOptions { Forwards, Backwards };
	Propulsion();
	bool drive();
	void setForwards(int speed);
	void setBackwards(int speed);
	void setRotation(int speed);
	Motor* getPointerToMotorL();
	Motor* getPointerToMotorR();
	void resetSumError();
};

#endif

