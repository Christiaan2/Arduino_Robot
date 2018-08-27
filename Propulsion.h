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
	int progress;
	bool allowSpeedControll;
public:
	enum driveOptions { Forwards, Backwards };
	Propulsion();
	bool drive();
	void setForwards(int distance = 0);
	void setBackwards(int distance = 0);
	void setLeftRotation(int distance);
	void setRightRotation(int distance);
	Motor* getPointerToMotorL();
	Motor* getPointerToMotorR();
	void setSpeed(int speed);
	void setAllowSpeedControl(bool allowSpeedControll);
	bool getAllowSpeedControll();
	void resetSumError();
	void reset();
	void stopMotors();
	void setProgress(int progress);
	int getProgress();
	void incrementProgress();
};

#endif

