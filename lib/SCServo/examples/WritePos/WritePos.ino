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
  SERVO.WritePos(1, 1023, 4000);// Servo ID:1, rotate to the position:0x2FF
  SERVO.WritePos(2, 1023, 4000);// Servo ID:2, rotate to the position:0x2FF
  delay(4000); 
  SERVO.WritePos(1,0x0000, 3000);// Servo ID:1, rotate to the position:0x000
  SERVO.WritePos(2, 0x0000, 3000);// Servo ID:1, rotate to the position:0x000
  delay(3000);
  SERVO.WritePos(1, 1023, 2000);// Servo ID:1, rotate to the position:0x2FF
  SERVO.WritePos(2, 1023, 2000);// Servo ID:2, rotate to the position:0x2FF
  delay(2000);
  SERVO.WritePos(1, 0x0000, 1000);// Servo ID:1, rotate to the position:0x000
  SERVO.WritePos(2, 0x0000, 1000);// Servo ID:2, rotate to the position:0x000
  delay(1000);
}
