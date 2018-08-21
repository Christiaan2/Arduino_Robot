// CollisionAvoidance.h

#ifndef COLLISIONAVOIDANCE_H
#define COLLISIONAVOIDANCE_H
#include "Arduino.h"
#include <Servo.h>
#include <NewPing.h>
#include "Propulsion.h"

#define VeryClose 25
#define Close 60

class CollisionAvoidance
{
private:
	 Servo servo;
	 NewPing sonar;
	 bool flagVeryClose;
	 bool flagClose;
public:
	CollisionAvoidance(int trigPin, int echoPin, int maxDistance);

	void run(Propulsion* propulsion, int speed);

	void initialize(int servoPin);
};

#endif

