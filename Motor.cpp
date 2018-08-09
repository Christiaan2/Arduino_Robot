// 
// 
// 

#include "Motor.h"

Motor::Motor(int directionPin, int enablePin, int encoderPin, float Kp, float Kd)
	: directionPin(directionPin), enablePin(enablePin), PWM_val(0), mDirection(true), encoder(encoderPin), pid(Kp, Kd)
{
	pinMode(this->directionPin, OUTPUT);
	pinMode(this->enablePin, OUTPUT);
	analogWrite(this->enablePin, PWM_val);
}

void Motor::setDirection(bool direction)
{
	mDirection = direction;
	digitalWrite(directionPin, mDirection);
}

void Motor::handleEncoder()
{
	encoder.updateEncoder(mDirection);
}

void Motor::setPWM_val(int PWM_val)
{
	this->PWM_val = PWM_val;
	analogWrite(enablePin, PWM_val);
}

void Motor::driveConstantSpeed(int speed_req)
{
	this->speed_req = speed_req;
	setPWM_val(pid.calcPidTerm(speed_req, encoder.calcSpeed()));
}

int Motor::getSpeed_req()
{
	return speed_req;
}

int Motor::getSpeed()
{
	return encoder.getSpeed();
}

int Motor::getPWM_val()
{
	return PWM_val;
}