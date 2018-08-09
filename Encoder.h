// Encoder.h

#ifndef ENCODER_H
#define ENCODER_H
#include "Arduino.h"

class Encoder
{
private:
	int encoderPin;
	long encoderTicks;
	long prevEncoderTicks;
	int speed;
public:
	Encoder(int encoderPin);
	void updateEncoder(bool direction);
	int calcSpeed();
	int getSpeed();
};
#endif

