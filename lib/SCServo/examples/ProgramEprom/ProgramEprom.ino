#include <SCServo.h>

int LEDpin = 13;
SCServo SERVO;

void setup()
{
  pinMode(LEDpin, OUTPUT);
  Serial1.begin(1000000);
  SERVO.pSerial = &Serial1;
  digitalWrite(LEDpin, LOW);
  SERVO.writeByte(0xfe, P_LOCK, 0);//打开EPROM保存功能
  SERVO.writeByte(0xfe, P_ID, 0);//ID
  delay(50);
  SERVO.writeWord(0xfe, P_MIN_ANGLE_LIMIT_L, 0);
  delay(50);
  SERVO.writeWord(0xfe, P_MAX_ANGLE_LIMIT_L, 1023);
  delay(50);
  SERVO.writeWord(0xfe, P_MAX_TORQUE_L, 1023);
  delay(50);
  SERVO.writeWord(0xfe, P_PUNCH_L, 50);
  delay(50);
  SERVO.writeByte(0xfe, P_CW_DEAD, 2);
  delay(50);
  SERVO.writeByte(0xfe, P_CCW_DEAD, 2);
  delay(50);
  SERVO.writeByte(0xfe, P_COMPLIANCE_P, 15);
  delay(50);
  SERVO.writeByte(0xfe, P_BAUD_RATE, B_1M);//BaundRate=1Mbit/s
  delay(50);
  SERVO.writeByte(0xfe, P_LOCK, 1);//关闭EPROM保存功能�
  digitalWrite(LEDpin, HIGH);
}

void loop()
{

}
