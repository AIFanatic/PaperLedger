#include <SCServo.h>

SCServo SERVO;
int LEDpin = 13;

void setup()
{
	pinMode(LEDpin,OUTPUT);
	digitalWrite(LEDpin, HIGH);
	Serial1.begin(1000000);
  SERVO.pSerial = &Serial1;
	delay(500);
	SERVO.EnableTorque(1, 0);
	SERVO.EnableTorque(2, 1);
}

void loop()
{
	int pos = SERVO.ReadPos(1);
	if(pos!=-1)
	{
	  digitalWrite(LEDpin, LOW);
		SERVO.WritePos(2, pos, 0);
    delay(10);
	}
	else
	{
		digitalWrite(LEDpin, HIGH);
    delay(2000);
	}
}
