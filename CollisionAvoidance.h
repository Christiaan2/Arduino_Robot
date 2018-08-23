// CollisionAvoidance.h

#ifndef COLLISIONAVOIDANCE_H
#define COLLISIONAVOIDANCE_H
#include "Arduino.h"
#include <Servo.h>
#include <NewPing.h>
#include "Propulsion.h"
#include "Timer.h"

#define VeryClose 25
#define Close 50
#define FREQ  1000

class CollisionAvoidance
{
private:
	 Servo servo;
	 NewPing sonar;
	 bool flagVeryClose;
	 bool flagClose;
	 Propulsion* propulsion;
	 Timer timer;
public:
	CollisionAvoidance(int trigPin, int echoPin, int maxDistance, Propulsion* propulsion);

	void run();

	void initialize(int servoPin);

	void avoidObstical();
};

#endif

