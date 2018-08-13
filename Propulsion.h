// Propulsion.h

#ifndef PROPULSION_H
#define PROPULSION_H
#include "Arduino.h"
#include "Motor.h"

class Propulsion
{
private:
	Motor motorL;
	Motor motorR;
public:
	enum driveOptions { Forwards, Backwards };
	Propulsion();
	bool drive();
	void setForwards(int speed);
	Motor* getPointerToMotorL();
	Motor* getPointerToMotorR();
};

#endif

