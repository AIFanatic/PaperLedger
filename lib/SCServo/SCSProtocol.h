/*
 * SCSProtocol.h
 * SCS���ж��Э�����
 * ����: 2016.8.25
 * ����: ̷����
 */

#ifndef _SCSPROTOCOL_H
#define _SCSPROTOCOL_H

typedef		char			s8;
typedef		unsigned char	u8;	
typedef		unsigned short	u16;	
typedef		short			s16;
typedef		unsigned long	u32;	
typedef		long			s32;

class SCSProtocol{
public:
	SCSProtocol();
	int genWrite(u8 ID, u8 MemAddr, u8 *nDat, u8 nLen);//��ͨдָ��
	int regWrite(u8 ID, u8 MemAddr,u8 *nDat, u8 nLen);//�첽дָ��
	void snycWrite(u8 ID[], u8 IDN, u8 MemAddr, u8 *nDat, u8 nLen);//ͬ��дָ��
	int writeByte(u8 ID, u8 MemAddr, u8 bDat);//д1���ֽ�
	int writeWord(u8 ID, u8 MemAddr, u16 wDat);//д2���ֽ�
	int EnableTorque(u8 ID, u8 Enable);//Ť������ָ��
	int WritePos(u8 ID, u16 Position, u16 Time, u16 Speed = 0);//��ͨдλ��ָ��
	int RegWritePos(u8 ID, u16 Position, u16 Time, u16 Speed = 0);//�첽дλ��ָ��
	void RegWriteAction();//ִ���첽дָ��
	void SyncWritePos(u8 ID[], u8 IDN, u16 Position, u16 Time, u16 Speed = 0);//ͬ��дλ��ָ��
	int WriteSpe(u8 ID, s16 Speed);//��Ȧ����ָ��
	int Read(u8 ID, u8 MemAddr, u8 *nData, u8 nLen);//��ָ��
	int readByte(u8 ID, u8 MemAddr);//��1���ֽ�
	int readWord(u8 ID, u8 MemAddr);//��2���ֽ�
	int ReadPos(u8 ID);//��λ��
	int ReadVoltage(u8 ID);//����ѹ
	int ReadTemper(u8 ID);//���¶�
	int Ping(u8 ID);//Pingָ��
	int wheelMode(u8 ID);//��Ȧ����ģʽ
	int joinMode(u8 ID, u16 minAngle=0, u16 maxAngle=1023);//��ͨ�ŷ�ģʽ
	int Reset(u8 ID);//��λ�������ΪĬ��ֵ
public:
	u8	Level;//������صȼ�
	u8	End;//��������С�˽ṹ
protected:
	virtual int writeSCS(unsigned char *nDat, int nLen) = 0;
	virtual int readSCS(unsigned char *nDat, int nLen) = 0;
	virtual int writeSCS(unsigned char bDat) = 0;
	virtual void flushSCS() = 0;
private:
	void writeBuf(u8 ID, u8 MemAddr, u8 *nDat, u8 nLen, u8 Fun);
	int writePos(u8 ID, u16 Position, u16 Time, u16 Speed, u8 Fun);
	void Host2SCS(u8 *DataL, u8* DataH, int Data);//1��16λ�����Ϊ2��8λ��
	int	SCS2Host(u8 DataL, u8 DataH);//2��8λ�����Ϊ1��16λ��
	int	Ack(u8 ID);//����Ӧ��

	#define		B_1M		0
	#define		B_0_5M		1
	#define		B_250K		2
	#define		B_128K		3
	#define		B_115200	4
	#define		B_76800		5
	#define		B_57600		6
	#define		B_38400		7

	//register Address
	#define P_VERSION_L 3
	#define P_VERSION_H 4
	#define P_ID 5
	#define P_BAUD_RATE 6
	#define P_RETURN_DELAY_TIME 7
	#define P_RETURN_LEVEL 8
	#define P_MIN_ANGLE_LIMIT_L 9
	#define P_MIN_ANGLE_LIMIT_H 10
	#define P_MAX_ANGLE_LIMIT_L 11
	#define P_MAX_ANGLE_LIMIT_H 12
	#define P_LIMIT_TEMPERATURE 13
	#define P_MAX_LIMIT_VOLTAGE 14
	#define P_MIN_LIMIT_VOLTAGE 15
	#define P_MAX_TORQUE_L 16
	#define P_MAX_TORQUE_H 17
	#define P_ALARM_LED 19
	#define P_ALARM_SHUTDOWN 20
	#define P_COMPLIANCE_P 21
	#define P_PUNCH_L 24
	#define P_PUNCH_H 25
	#define P_CW_DEAD 26
	#define P_CCW_DEAD 27

	#define P_TORQUE_ENABLE 40
	#define P_LED 41
	#define P_GOAL_POSITION_L 42
	#define P_GOAL_POSITION_H 43
	#define P_GOAL_TIME_L 44
	#define P_GOAL_TIME_H 45
	#define P_GOAL_SPEED_L 46
	#define P_GOAL_SPEED_H 47
	#define P_LOCK 48

	#define P_PRESENT_POSITION_L 56
	#define P_PRESENT_POSITION_H 57
	#define P_PRESENT_SPEED_L 58
	#define P_PRESENT_SPEED_H 59
	#define P_PRESENT_LOAD_L 60
	#define P_PRESENT_LOAD_H 61
	#define P_PRESENT_VOLTAGE 62
	#define P_PRESENT_TEMPERATURE 63
	#define P_REGISTERED_INSTRUCTION 64
	#define P_MOVING 66

	//Instruction:
	#define INST_PING 0x01
	#define INST_READ 0x02
	#define INST_WRITE 0x03
	#define INST_REG_WRITE 0x04
	#define INST_ACTION 0x05
	#define INST_RESET 0x06
	#define INST_SYNC_WRITE 0x83
};
#endif
