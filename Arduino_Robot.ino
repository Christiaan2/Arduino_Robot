/* Name:			Christiaan Reurslag
*  Date:			7 August 2018
*  Description:		Program to control a robot using an Arduino Uno
*  Connections:		D2: Encoder left
					D3: Encoder right
					D4: Direction left
					D5: Speed left
					D6: Speed right
					D7: Direction right
					D8: Button for oscilloscope
					A5: Potentiometer to set speed
* Functionality:	Drive constant speed, drive certain distance ...
*/
#include "CollisionAvoidance.h"
#include "Propulsion.h"
#include "Robot.h"

Robot robot;

void setup() {
	robot.initialize();
	attachInterrupt(digitalPinToInterrupt(2), handleLeftEncoderWrapper, CHANGE);
	attachInterrupt(digitalPinToInterrupt(3), handleRightEncoderWrapper, CHANGE);
}

void loop() {
	robot.run();
}

void handleLeftEncoderWrapper()
{
	static Encoder* _EncoderL = robot.getPointerToMotorL()->getPointerToEncoder();
	_EncoderL->updateEncoder();
}

void handleRightEncoderWrapper()
{
	static Encoder* _EncoderR = robot.getPointerToMotorR()->getPointerToEncoder();
	_EncoderR->updateEncoder();
}
