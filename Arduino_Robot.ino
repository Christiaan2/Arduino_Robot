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
	attachInterrupt(digitalPinToInterrupt(3), handleEncoderWrapper, CHANGE);
}

void loop() {
	robot.run();
}

void handleEncoderWrapper()
{
	robot.handleEncoder();
}
