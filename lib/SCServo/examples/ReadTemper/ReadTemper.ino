#include <SCServo.h>

SCServo SERVO;

int LEDpin = 13;
void setup()
{
  pinMode(LEDpin,OUTPUT);
  digitalWrite(LEDpin, HIGH);
	Serial1.begin(1000000);
  Serial.begin(115200);
  SERVO.pSerial = &Serial1;
	delay(500);
}

void loop()
{
  int T = SERVO.ReadTemper(1);
	if(T!=-1)
	{
    digitalWrite(LEDpin, LOW);
    Serial.println(T, DEC);
    delay(10);
  }
  else
  {
    digitalWrite(LEDpin, HIGH);
    delay(2000);    
  }
}
