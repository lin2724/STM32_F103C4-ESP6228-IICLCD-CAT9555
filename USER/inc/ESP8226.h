#ifndef _ESP8226_H_
#define _ESP8226_H_
#define USING_STDLIB 1
#include "type.h"



#define CMD_AT 							(0)
#define CMD_RESET 					(1)
#define CMD_VERSION 				(2)
#define CMD_MODE 						(3)
#define CMD_JOIN_IP 				(4)
#define CMD_LIST_IP 				(5)
#define CMD_QUIT_IP 				(6)
#define CMD_SET_IP 					(7)
#define CMD_LIST_CLIENT 		(8)
#define CMD_IP_STATUS 			(9)
#define CMD_START_IP 				(10)
#define CMD_SEND_DAT 				(11)
#define CMD_IP_DISCONNECT 	(12)
#define CMD_GET_LOCALIP 		(13)
#define CMD_SET_MUX 				(14)
#define CMD_SET_SERVER 			(15)
#define CMD_SET_IPMODE 			(16)
#define CMD_SET_TIMEOUT 		(17)
#define CMD_UPDATE 					(18)


#define MAX_REV_LEN 1024
#define MAX_REVCMD_LEN 1024

typedef struct MsgSq
{
	unsigned int len;
	char* buf;
	struct MsgSq* next;
}T_MsgSq;

void* ESP_malloc(u32 size);
void ESP_free(void* ptr);
T_MsgSq* ESPSeprateMsg(char* msg,int len);
T_MsgSq* GetMsgQueue(T_MsgSq* msgq,int id);
int GetNumByString(char* str,u8 num);
void FreeMsgQueue(T_MsgSq* msgq);
int AddMsgQueue(char* msg,unsigned int len);
#endif
