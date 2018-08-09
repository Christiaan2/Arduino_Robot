/* Name:			Christiaan Reurslag
*  Date:			7 August 2018
*  Description:		Program to control a robot using an Arduino Uno
*  Connections:		D2:
					D3:...
* Functionality:	Drive constant speed, drive certain distance ...
*/

//#define NCHANNELS 3   //Number of channels for oscilloscope
#include "Robot.h"

//volatile bool timer_go = false;  //variable to run into the timed loop
/*
//Class to handle a motor(DC motor and encoder)
class Motor
{
private:
	//Connectios
	int directionPin;
	int enablePin;
	int encoderPin;
	bool mDirection;  //True is forwards, false is backwards
	int mSpeed_req;   //Desired speed of the motor
	int mSpeed_act;   //Actual speed of the motor
	int PWM_val = 0;  //PWM value 
	volatile long encoderTicks = 0; //Keeps track of the amount of rotations of the wheel
	long prevEncoderTicks = 0;      //Previous encoderTicks, needed for pid controller
	int A; //Constant to go from encoder ticks to distance
		   //Constants for Pid controller
	float Kp = 2.5;//0.7;//0.4
	float Kd = 1.5;//1
	int prevError = 0;
public:
	Motor() {} //Empty constructor
	Motor(int directionPin, int enablePin, int encoderPin)
	{
		setPins(directionPin, enablePin, encoderPin);
	}
	void setPins(int directionPin, int enablePin, int encoderPin)
	{
		this->directionPin = directionPin;
		this->enablePin = enablePin;
		this->encoderPin = encoderPin;
		pinMode(this->directionPin, OUTPUT);
		setDirection(true);
		pinMode(this->enablePin, OUTPUT);
		analogWrite(this->enablePin, PWM_val);
		pinMode(this->encoderPin, INPUT);
	}
	void setDirection(bool mDirection) //true is forwards, false is backwards
	{
		this->mDirection = mDirection;
		digitalWrite(directionPin, this->mDirection);
	}
	void handleEncoder()
	{
		if (mDirection)
		{
			encoderTicks++;
		}
		else
		{
			encoderTicks--;
		}
	}
	void setPWM_val(int PWM_val)
	{
		this->PWM_val = PWM_val;
		analogWrite(enablePin, PWM_val);
	}
	void driveConstantSpeed(int speed_req)
	{
		this->mSpeed_req = speed_req;
		getSpeed_act();
		updatePID();
		analogWrite(enablePin, PWM_val);
	}
	void driveDistance(int distance, int mSpeed)
	{
		//Here was I
	}
	void updatePID()
	{
		if (mSpeed_req <= 1)
		{
			PWM_val = 0;
		}
		else
		{
			int error = abs(mSpeed_req) - abs(mSpeed_act);
			float pidTerm = (Kp * error) + (Kd * (error - prevError));
			prevError = error;
			PWM_val = constrain(PWM_val + int(pidTerm), 0, 255);
		}
	}
	void getSpeed_act()
	{
		mSpeed_act = (encoderTicks - prevEncoderTicks);
		prevEncoderTicks = encoderTicks;
	}
	long getEncoderTicks() {
		return encoderTicks;
	}
	int returnMSpeed_act() {
		return mSpeed_act;
	}
	int returnPWM_val() {
		return PWM_val;
	}
	int returnMSpeed_req() {
		return mSpeed_req;
	}
	int returnPrevError() {
		return prevError;
	}
};
*/
/*
class Button
{
private:
	int Pin;
	const int shortPress = 5;
	const int longPress = 1000;
	bool state;
	bool prevState = false;
	unsigned long timePressed = 0; //Time when button is pressed(Used for filtering debouncing)
public:
	enum buttonResult { unchangedPressed, unchangedNotPressed, changedPressed, shortPressed, longPressed, debounce };
	Button() {}
	Button(int Pin)
	{
		setPin(Pin);
	}
	void setPin(int Pin)
	{
		this->Pin = Pin;
		pinMode(this->Pin, INPUT);
	}
	buttonResult input()
	{
		state = (digitalRead(Pin) == HIGH);
		if (state == prevState)
		{
			if (state) { return unchangedPressed; }
			else { return unchangedNotPressed; }
		}
		else
		{
			prevState = state;
			if (state) {
				timePressed = millis();
				return changedPressed;
			}
			else {
				unsigned long timeReleased = millis();
				if (timeReleased - timePressed > longPress) //long press?
				{
					return longPressed;
				}
				else if (timeReleased - timePressed > shortPress) //short press?
				{
					return shortPressed;
				}
				else
				{
					return debounce;
				}
			}
		}
	}
};
*/
/*
class Oscilloscope
{
private:
	bool sampling_on = false;  //True when sampling is on
	bool timeOffset_go = false; //First timestamp is used to remove time offset
	unsigned long Time;
	unsigned long timeOffset = 0; //Time offset (Time = millis() - timeOffset)
	Button button;
	int NChannels = 3;
	int SensorReading[3];
	const byte stop_message[2] = { 255, 253 };
	const byte pause_message[2] = { 255, 254 };
	const byte start_message[2] = { 255, 255 };
public:
	Oscilloscope() {}
	Oscilloscope(int buttonPin, int NChannels)
	{
		initiate(buttonPin);//, NChannels);
	}
	void initiate(int buttonPin)//, int NChannels)
	{
		button.setPin(buttonPin);
		//this->NChannels = NChannels;

		//SensorReading = new int[this->NChannels];

		//Initialize serial communication
		Serial.begin(115200);
		Serial.setTimeout(1000);

		//Small led on the Arduino, LED is on when sampling is active
		pinMode(13, OUTPUT);
		digitalWrite(13, sampling_on);
	}
	void checkButton()
	{
		switch (button.input()) {
		case Button::longPressed:
		{//Stop Sampling and MATLAB script
			Serial.write(stop_message, 2);
			sampling_on = false;
			digitalWrite(13, sampling_on);
		}
		break;
		case Button::shortPressed:
		{
			if (sampling_on)
			{ //Stop sampling
				Serial.write(pause_message, 2);
				sampling_on = false;
				digitalWrite(13, sampling_on);
			}
			else
			{ //Start sampling
				timeOffset_go = true;
				Serial.write(start_message, 2);
				sampling_on = !sampling_on;
				digitalWrite(13, sampling_on);
			}
		}
		break;
		}
	}
	void setTime() {
		Time = millis(); //Time when sample was taken
		if (timeOffset_go) //First sample?
		{ //Yes, save time offset
			timeOffset = Time;
			timeOffset_go = false;
		}
		Time = Time - timeOffset; //Remove time offset
	}
	void setSensorReading(int channel, int value) {
		SensorReading[channel] = value;
	}
	void sendData() {
		for (int i = 0; i < NChannels; i++)
		{
			byte SensorReading_byte[2] = { SensorReading[i], SensorReading[i] >> 8 };
			Serial.write(SensorReading_byte, 2); //Send sensor value to pc
		}
		byte Time_byte[4] = { Time, Time >> 8, Time >> 16, Time >> 24 };
		Serial.write(Time_byte, 4); //Send time to pc
	}
	bool getSampling_on() {
		return sampling_on;
	}
};
*/
Robot robot;

//Motor motor;
//Oscilloscope oscilloscope;

void setup() {
	//Initialize motor
	//*motor.setPins(4, 5, 3);
	attachInterrupt(digitalPinToInterrupt(3), handleEncoderWrapper, CHANGE);
	//Initialize oscilloscope
	//*oscilloscope.initiate(7);//,1);
	Serial.begin(115200);
							 //Initialize timer1 
	//noInterrupts();           //Disable all interrupts
	//TCCR1A = 0;
	//TCCR1B = 0;
	//TCNT1 = 0;
	//--OCR1A = 16000000/8/LOOPFREQ;            //Compare match register 16MHz/8/100Hz (20000)
	//OCR1A = 16000000 / 256 / LOOPFREQ - 1;
	//TCCR1B |= (1 << WGM12);   //CTC mode
	//TCCR1B |= (1 << CS12);    //prescaler of 256
	//TIMSK1 |= (1 << OCIE1A);  //Enable timer compare interrupt
	//interrupts();             //Enable all interrupts
}

void loop() {
	robot.run();
}

/*
ISR(TIMER1_COMPA_vect)          //Timer compare interrupt service routine
{ //This function is called with a frequency of 10Hz
	timer_go = true;
}*/

void handleEncoderWrapper()
{
	robot.handleEncoder();
}
