// 
// 
// 

#include "Encoder.h"

Encoder::Encoder(int encoderPin)
	: encoderPin(encoderPin), encoderTicks(0), prevEncoderTicks(0)
{
	pinMode(encoderPin, INPUT);
}

void Encoder::updateEncoder(bool direction)
{
	direction ? encoderTicks++ : encoderTicks--;
}

int Encoder::calcSpeed()
{
	speed = int(encoderTicks - prevEncoderTicks);
	prevEncoderTicks = encoderTicks;
	return speed;
}

int Encoder::getSpeed()
{
	return speed;
}