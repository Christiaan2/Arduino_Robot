// Motor.h

#ifndef MOTOR_H
#define MOTOR_H
#include "Arduino.h"
#include "Encoder.h"
#include "Pid.h"

class Motor
{
private:
	int directionPin;
	int enablePin;
	Encoder encoder;
	Pid pid;
	bool mDirection;  //True is forwards, false is backwards
	int speed;   //Desired speed of the motor
	int PWM_val;  //PWM value 
public:
	//enum for direction??
	Motor(int directionPin, int enablePin, int encoderPin, float Kp, float Kd);
	
	void setDirection(bool direction); //true is forwards, false is backwards

	void setSpeed(int speed);

	void handleEncoder();

	Motor* getPointer();

	void setPWM_val(int PWM_val);

	void driveConstantSpeed(int speed_req);

	int calcPWM_val();

	int getSpeed();

	Encoder* getPointerToEncoder();

	int getPWM_val();
	
	//void driveDistance(int distance, int mSpeed)
	//{
		//Here was I
	//}
};

#endif