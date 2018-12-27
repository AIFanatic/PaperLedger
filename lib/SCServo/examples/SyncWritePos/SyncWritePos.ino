#include <SCServo.h>

SCServo SERVO;
byte ID[2];
void setup()
{
  Serial1.begin(1000000);
  SERVO.pSerial = &Serial1;
  delay(500);
  SERVO.EnableTorque(1, 1);
  SERVO.EnableTorque(2, 1);
  ID[0] = 1;
  ID[1] = 2;
}

void loop()
{
	SERVO.SyncWritePos(ID, 2, 0, 4000);
	delay(4000);
	SERVO.SyncWritePos(ID, 2, 1023, 4000);
	delay(4000);
}
