// Propulsion.h

#ifndef PROPULSION_H
#define PROPULSION_H
#include "Arduino.h"
#include "Motor.h"

#define KP_CONST_SPEED 6
#define KD_CONST_SPEED 5
#define KI_CONST_SPEED 1

class Propulsion
{
private:
	Motor motorL;
	Motor motorR;
	int SumError;
public:
	enum driveOptions { Forwards, Backwards };
	Propulsion();
	bool drive();
	void setForwards(int speed);
	void setBackwards(int speed);
	Motor* getPointerToMotorL();
	Motor* getPointerToMotorR();
	void resetSumError();
};

#endif

