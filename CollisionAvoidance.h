// CollisionAvoidance.h

#ifndef COLLISIONAVOIDANCE_H
#define COLLISIONAVOIDANCE_H
#include "Arduino.h"
#include "Servo/src/Servo.h"
#include "NewPing/NewPing.h"

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
	CollisionAvoidance(int servoPin, int trigPin, int echoPin, int maxDistance);

	void run(Propulsion* propulsion, int speed);
};

#endif

