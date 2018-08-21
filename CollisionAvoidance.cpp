// 
// 
// 

#include "CollisionAvoidance.h"

CollisionAvoidance::CollisionAvoidance(int trigPin, int echoPin, int maxDistance)
	: sonar(trigPin, echoPin, maxDistance), flagVeryClose(false), flagClose(false)
{//trigPin and echoPin can be the same
}

void CollisionAvoidance::run(Propulsion* propulsion, int speed)
{
	if (flagVeryClose || flagClose)
	{
		static int i = 0;
		static int distanceL;
		static int distanceR;
		switch (i) {
		case 0:
			propulsion->setForwards(2,0);
			servo.write(5);
			i++;
			break;
		case 1:
			i++;
			break;
		case 2:
			distanceL = sonar.ping_cm();
			if (distanceL == 0)
			{
				distanceL = 101;
			}
			i++;
			break;
		case 3:
			servo.write(175);
			i++;
			break;
		case 4:
			i++;
			break;
		case 5:
			distanceR = sonar.ping_cm();
			if (distanceR == 0)
			{
				distanceR = 101;
			}
			i++;
			break;
		case 6:
			servo.write(90);
			propulsion->reset();
			i++;
			break;
		case 7:
			i++;
			break;
		case 8:
			if (flagVeryClose) {
				propulsion->setBackwards(speed, 40);
				if (!propulsion->drive())
				{
					i++;
					propulsion->reset();
				}
				return;
			}
			else
			{
				i++;
			}
			break;
		case 9:
			if (distanceL >= distanceR)
			{
				//turn 120 degrees to left
				propulsion->setLeftRotation(speed, 33);
			}
			else
			{
				propulsion->setRightRotation(speed, 33);
			}
			if (!propulsion->drive())
			{
				i++;
				propulsion->reset();
			}
			return;
		default:
			i = 0;
			propulsion->setForwards(speed, 0);
			flagVeryClose = false;
			flagClose = false;
		}
		
	}
	else
	{
		unsigned int distance = sonar.ping_cm();
		if (distance == 0)
		{
			distance = 101;
		}
		if (distance <= VeryClose)
		{
			flagVeryClose = true;
		}
		else if (distance <= Close)
		{
			flagClose = true;
		}
		else
		{
			propulsion->setForwards(speed, 0);
		}
	}
	propulsion->drive();
}

void CollisionAvoidance::initialize(int servoPin)
{ // Can't use attach inside constructor
	servo.attach(servoPin);
	servo.write(90);
}