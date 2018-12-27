/*
 * SCServo.h
 * Ӳ��ͨ�Žӿ�
 * ����: 2016.8.25
 * ����: ̷����
 */

#ifndef _SCSERVO_H
#define _SCSERVO_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SCSProtocol.h"

class SCServo : public SCSProtocol
{
public:
	SCServo(void);
	virtual int writeSCS(unsigned char *nDat, int nLen);//���nLen�ֽ�
	virtual int readSCS(unsigned char *nDat, int nLen);//����nLen�ֽ�
	virtual int writeSCS(unsigned char bDat);//���1�ֽ�
	virtual void flushSCS();//ˢ�½ӿڻ�����
public:
	unsigned long int IOTimeOut;//���������ʱ
	HardwareSerial *pSerial;//����ָ��
};

#endif