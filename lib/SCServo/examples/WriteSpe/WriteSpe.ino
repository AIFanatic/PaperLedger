#include <SCServo.h>

SCServo SERVO;

void setup()
{
	Serial1.begin(1000000);
  SERVO.pSerial = &Serial1;
	delay(500);
	SERVO.wheelMode(1);
	SERVO.EnableTorque(1, 1);
}

void loop()
{
  SERVO.WriteSpe(1, 511);
	delay(5000);
  SERVO.WriteSpe(1, 0);
	delay(2000);
	SERVO.WriteSpe(1, -511);
	delay(5000);
	SERVO.WriteSpe(1, 0);
	delay(2000);
}
