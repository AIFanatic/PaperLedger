#include <SCServo.h>

SCServo SERVO;

void setup()
{
  Serial1.begin(1000000);
  SERVO.pSerial = &Serial1;
  delay(500);
  SERVO.EnableTorque(0xfe,1);
  SERVO.WritePos(0xfe, 0, 1000);
  delay(1000);        
}

void loop()
{
  int i;
  for(i = 0; i<1024; i++)
  {
    SERVO.WritePos(0xfe,i,20);//All Servo(broadcast) rotate to the position:i
    delay(20);
  }
  for(i = 1023; i > 0; i--)
  {
    SERVO.WritePos(0xfe,i,10);//All Servo(broadcast) rotate to the position:i
    delay(10);
  }
}
