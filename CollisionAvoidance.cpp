// 
// 
// 

#include "CollisionAvoidance.h"

CollisionAvoidance::CollisionAvoidance(int servoPin, int trigPin, int echoPin, int maxDistance)
	: sonar(trigPin,echoPin,maxDistance), flagVeryClose(false), flagClose(false)
{ //trigPin and echoPin can be the same
	servo.attach(servoPin);
	servo.write(90);
}

void CollisionAvoidance::run(Propulsion* propulsion, int speed)
{
	static int distanceL;
	static int distanceR;
	if (flagVeryClose)
	{
		static int i = 0;
		switch (i) {
		case 0:
			propulsion->stopMotors();
			servo.write(5);
			i++;
			break;
		case 1:
			i++;
			break;
		case 2:
			distanceL = sonar.ping_cm();
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
			i++;
			break;
		case 6:
			servo.write(90);
			propulsion->reset();
			propulsion->setBackwards(speed, 40);
			if (!propulsion->drive())
			{
				i++;
				propulsion->stopMotors();
			}
			break;
		case 7:


		}
		
	}
	else if (flagClose)
	{

	}
	else
	{
		unsigned int distance = sonar.ping_cm();
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