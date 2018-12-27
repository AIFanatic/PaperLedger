#include <SCServo.h>

SCServo SERVO;
int LEDpin = 13;

void setup()
{
	pinMode(LEDpin,OUTPUT);
	digitalWrite(LEDpin, HIGH);
	Serial.begin(1000000);//init Serial baudrate
	delay(500);
	SERVO.EnableTorque(1, 1);
}

void loop()
{
	int Load = SERVO.ReadLoad(1);//read Servo ID:1 Load
	if(abs(Load) > 50)
         {
           //SERVO.EnableTorque(1, 0);
           digitalWrite(LEDpin, LOW);
	}
       else
       {
           //SERVO.EnableTorque(1, 1);
           digitalWrite(LEDpin, HIGH);
	}
	delay(50);
}
