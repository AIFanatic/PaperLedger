/*
 * SCServo.h
 * 硬件通信接口
 * 日期: 2016.8.25
 * 作者: 谭雄乐
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
	virtual int writeSCS(unsigned char *nDat, int nLen);//输出nLen字节
	virtual int readSCS(unsigned char *nDat, int nLen);//输入nLen字节
	virtual int writeSCS(unsigned char bDat);//输出1字节
	virtual void flushSCS();//刷新接口缓冲区
public:
	unsigned long int IOTimeOut;//输入输出超时
	HardwareSerial *pSerial;//串口指针
};

#endif