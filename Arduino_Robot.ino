/* Name:			Christiaan Reurslag
*  Date:			7 August 2018
*  Description:		Program to control a robot using an Arduino Uno
*  Connections:		D2:
					D3:...
* Functionality:	Drive constant speed, drive certain distance ...
*/
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
	static Motor* _MotorL = robot.getPointerToMotorL();
	_MotorL->handleEncoder();
}

void handleRightEncoderWrapper()
{
	static Motor* _MotorR = robot.getPointerToMotorR();
	_MotorR->handleEncoder();
}
