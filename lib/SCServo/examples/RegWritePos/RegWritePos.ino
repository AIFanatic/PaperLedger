#include <SCServo.h>

SCServo SERVO;

void setup()
{
  Serial1.begin(1000000);
  SERVO.pSerial = &Serial1;
	delay(500);
	SERVO.EnableTorque(1, 1);
	SERVO.EnableTorque(2, 1);
}

void loop()
{
	SERVO.RegWritePos(1, 1023, 2000);
	SERVO.RegWritePos(2, 1023, 2000);
	SERVO.RegWriteAction();
	delay(2000);
  
	SERVO.RegWritePos(1, 0, 3000);
	SERVO.RegWritePos(2, 0, 3000);
	SERVO.RegWriteAction();
	delay(3000);
}
