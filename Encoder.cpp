// 
// 
// 

#include "Encoder.h"

Encoder::Encoder(int encoderPin)
	: encoderPin(encoderPin), encoderTicks(0), prevEncoderTicks(0)
{
	pinMode(encoderPin, INPUT);
}

void Encoder::updateEncoder()
{
	encoderTicks++;
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

Encoder* Encoder::getPointer()
{
	return this;
}

void Encoder::reset()
{
	encoderTicks = 0;
	prevEncoderTicks = 0;
}

long Encoder::getEncoderTicks()
{
	return encoderTicks;
}

long Encoder::getPrevEncoderTicks()
{
	return prevEncoderTicks;
}