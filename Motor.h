// Motor.h

#ifndef MOTOR_H
#define MOTOR_H
#include "Arduino.h"
#include "Encoder.h"
#include "SpeedController.h"

class Motor
{
private:
	int directionPin;
	int enablePin;
	Encoder encoder;
	SpeedController speedController;
	bool mDirection;  //True is forwards, false is backwards
	int speed;   //Desired speed of the motor
	int distance;
	int PWM_val;  //PWM value 
public:
	//enum for direction??
	Motor(int directionPin, int enablePin, int encoderPin, float Kp, float Kd);
	
	void setDirection(bool direction); //true is forwards, false is backwards

	void setSpeed(int speed);

	void setDistance(int distance);

	Motor* getPointer();

	void setPWM_val(int PWM_val);

	void driveConstantSpeed(int speed_req);

	int calcPWM_val();

	int getSpeed();

	Encoder* getPointerToEncoder();

	int getPWM_val();

	int getDistance();

	void reset();
};

#endif