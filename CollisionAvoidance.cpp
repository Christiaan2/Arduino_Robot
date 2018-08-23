// 
// 
// 

#include "CollisionAvoidance.h"

CollisionAvoidance::CollisionAvoidance(int trigPin, int echoPin, int maxDistance, Propulsion* propulsion)
	: sonar(trigPin, echoPin, maxDistance), flagVeryClose(false), flagClose(false), propulsion(propulsion), timer(FREQ)
{//trigPin and echoPin can be the same
}

void CollisionAvoidance::run()
{
	if (flagVeryClose || flagClose)
	{
		avoidObstical();
	}
	else
	{
		unsigned int distance = sonar.convert_cm(sonar.ping_median());
		if (distance <= VeryClose && distance != 0)
		{
			flagVeryClose = true;
		}
		else if (distance <= Close && distance != 0)
		{
			flagClose = true;
		}
		else
		{
			propulsion->setForwards();
		}
	}
}

void CollisionAvoidance::avoidObstical()
{
	static int distanceL;
	static int distanceR;
	switch (propulsion->getProgress()) {
	case 0:
		propulsion->setAllowSpeedControl(false);
		propulsion->setSpeed(2);
		servo.write(175);
		timer.setTimer(500);
		propulsion->incrementProgress();
		break;
	case 1:
		if (timer.fire())
		{
			distanceR = sonar.convert_cm(sonar.ping_median());
			servo.write(5);
			timer.setTimer(800);
			propulsion->incrementProgress();
		}
		break;
	case 2:
		if (timer.fire())
		{
			distanceL = sonar.convert_cm(sonar.ping_median());
			servo.write(90);
			propulsion->reset();
			timer.setTimer(800);
			propulsion->incrementProgress();
		}
		break;
	case 3:
		if (flagVeryClose) 
		{
			propulsion->setBackwards(40);
		}
		else
		{
			propulsion->incrementProgress();
		}
		break;
	case 4:
		if (distanceL >= distanceR && distanceR != 0)
		{
			//turn 120 degrees to left
			propulsion->setLeftRotation(18);
		}
		else
		{
			propulsion->setRightRotation(18);
		}
		break;
	case 5:
		timer.setTimer(100);
		propulsion->incrementProgress();
		break;
	default:
		if (timer.fire())
		{
			propulsion->setProgress(0);
			propulsion->setForwards();
			flagVeryClose = false;
			flagClose = false;
		}
	}
}

void CollisionAvoidance::initialize(int servoPin)
{ // Can't use attach inside constructor
	servo.attach(servoPin);
	servo.write(90);
	delay(500);//TEMP
}