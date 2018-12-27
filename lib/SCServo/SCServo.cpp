/*
 * SCServo.cpp
 * 硬件通信接口
 * 日期: 2016.8.9
 * 作者: 谭雄乐
 */


#include "SCServo.h"

SCServo::SCServo()
{
	IOTimeOut = 2;
	pSerial = NULL;
}

int SCServo::readSCS(unsigned char *nDat, int nLen)
{
	int Size = 0;
	int ComData;
	unsigned long t_begin = millis();
	unsigned long t_user;
	while(1){
		ComData = pSerial->read();
		if(ComData!=-1){
			if(nDat){
				nDat[Size] = ComData;
			}
			Size++;
			t_begin = millis();
		}
		if(Size>=nLen){
			break;
		}
		t_user = millis() - t_begin;
		if(t_user>IOTimeOut){
			break;
		}
	}
	return Size;
}

int SCServo::writeSCS(unsigned char *nDat, int nLen)
{
	if(nDat==NULL){
		return 0;
	}
	return pSerial->write(nDat, nLen);
}

int SCServo::writeSCS(unsigned char bDat)
{
	return pSerial->write(&bDat, 1);
}

void SCServo::flushSCS()
{
	while(pSerial->read()!=-1);
}
