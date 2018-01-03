#include "ESP8226.h"
#include "stdlib.h"
#include "delay.h"
#include "type.h"
#ifdef USING_STDLIB
#include "string.h"
#include "stdio.h"
#endif
typedef struct ESP_CmdTable
{
	u8 cmd;
	char* string;
}T_ESP_CmdTable;
typedef struct IP_Message
{
	u8 ch;
	u32 len;
	char* buf;
	struct IP_Message* next;
}T_IP_Message;


T_ESP_CmdTable G_EspCmdTables[] = 
{
	{0,NULL},
	{1,"RST"},
	{2,"GMR"},
	{3,"CWMODE"},
	{4,"CWJAP"},
	{5,"CWLAP"},
	{6,"CWQAP"},
	{7,"CWSAP"},
	{8,"CWLIF"},
	{9,"CIPSTATUS"},
	{10,"CIPSTART"},
	{11,"CIPSEND"},
	{12,"CIPCLOSE"},
	{13,"CIFSR"},
	{14,"CIFMUX"},
	{15,"CIPSERVER"},
	{16,"CIPMODE"},
	{17,"CIPSTO"},
	{18,"CIPUPDATE"},
};

int AddMsgQueue(char* msg,unsigned int len)
{
	char* tmp=NULL;
	T_MsgSq* tmpq=NULL;
	int i;
	if(len>=MAX_REV_LEN){printf("ERROR add queue out of limit %d bytes",MAX_REV_LEN);return ERROR;}
	if(0 == len){printf("ERROR pass 0 len to addmsgqueue\n");return ERROR;}
	tmp = ESP_malloc(MAX_REV_LEN);
	if(tmp == NULL){printf("ERROR malloc mem\n");return ERROR;}
	for(i=0;i<len;i++)
	{
		tmp[i] = msg[i];
	}
	ERROR_CLEAN:
	ESP_free(tmp);
	ESP_free(tmpq);
}

void FreeMsgQueue(T_MsgSq* msgq)
{
	T_MsgSq* tmpq;
	while(msgq)
	{
		tmpq = msgq;
		ESP_free(msgq);
		msgq = tmpq->next;
	}
}

T_MsgSq* GetMsgQueue(T_MsgSq* msgq,int id)
{
	int i;
	for(i=0;i<=id;i++)
	{
		
	}
}

T_MsgSq* ESPSeprateMsg(char* msg,int len)
{
	return NULL;
}

int StringCompare(char* str1,char* str2,u8 num)
{
		return 0;
}
int GetNumByString(char* str,u8 num)
{
	return 0;
}
void* ESP_malloc(u32 size)
{
	return NULL;
}
void ESP_free(void* ptr)
{
	return ;
}
void ESP_WriteChar(char dat)
{
	return;
}
u8 ESP_WriteCmd(u8 cmd,char* arg)
{
	char buf[100];//应该没有超过100那么长的命令吧
	int i;
	for(i=0;i<sizeof(buf);i++){buf[i]=0;}//清0
#ifdef USING_STDLIB
	memset((void*)buf,sizeof(buf),0);
	sprintf(buf,"AT+%s",G_EspCmdTables[cmd].string);
	if(arg != NULL)
	{
		sprintf(buf,"AT+%s%s\r\n",G_EspCmdTables[cmd].string,arg);
	}
	for(i=0;i<strlen(buf);i++)
	{
		ESP_WriteChar(buf[i]);
	}
#endif
	return 0;
}
u8* IP_RevBuf;
u8* CMD_RevBuf;
u8 ESP_ReadPoint=0;
u8 ESP_WritePoint=0;
void ESP_Init(void)
{
	IP_RevBuf = ESP_malloc(MAX_REV_LEN);
	CMD_RevBuf = ESP_malloc(MAX_REVCMD_LEN);
	if(IP_RevBuf && CMD_RevBuf)
	{
		printf("ESP init ok\n");
	}else{
		while(1)
		{
			printf("ERROR ESP init fail\n");
			delay_ms(500);
		}
	}
}

#define MSG_TYPE_IP 1
#define MSG_TYPE_CMD 2
void ESP_ReceiveHandle(char dat)
{
	static char RBuf[MAX_REV_LEN];
	static u32 CurPoint=0;
	static u8 CheckEnd=0;
	static u8 EndPoint;
	static u8 MsgType=0;
	static u8 MaohaoReceived=0;
	static u8 EnterReceived=0;
	T_MsgSq* tmpqHeader = NULL;
	T_MsgSq* tmpq = NULL;
	u32 i;
	if(!IP_RevBuf)
	{
		IP_RevBuf = ESP_malloc(MAX_REV_LEN);
		if(!IP_RevBuf){printf("ERROR malloc RBuf fail\n");return;}
		printf("ESP Receive Buf init,received %d byte maximum once\n",MAX_REV_LEN);
	}
	RBuf[CurPoint++] = dat;
	if(dat == ':'){MaohaoReceived=1;}
	if(dat == 'n'){EnterReceived=1;}
	if(CurPoint==4)
	{
		if(0==StringCompare(RBuf,"+IPD",4))
		{
			MsgType = MSG_TYPE_IP;
			printf("IP Msg header get\n");
		}else
		{
			MsgType = MSG_TYPE_CMD;
			printf("CMD Msg header get\n");
		}
	}
	if(MsgType==MSG_TYPE_IP && MaohaoReceived)
	{
		tmpqHeader = ESPSeprateMsg(RBuf,CurPoint);
		if(tmpqHeader)
		{
			tmpq = GetMsgQueue(tmpqHeader,2);
			if(tmpq)
			{
				EndPoint = GetNumByString(tmpq->buf,tmpq->len);
			}else
			{
				printf("ERROR cant find ip msg's data len\n");
				goto EXIT_CLEAN;
			}
		}
	}
	
	
	return;
	EXIT_CLEAN:
	return;
	
	#if 0
	if(CheckEnd==1)
	{
		if(dat==*"O"){CheckEnd=2;}
		else{CheckEnd=0;}
		return;
	}
	if(CheckEnd==2)
	{
		CheckEnd=0;
		if(dat==*"K")
		{
			if(RevSq[ESP_WritePoint]==NULL)
			{
				RevSq[ESP_WritePoint] = ESP_malloc(point);
			}
			for(i=0;i<MAX_RECEIVE_SQ;i++)
			{
				if(RevSq[i]==NULL)
				{
					RevSq[i] = ESP_malloc(point);
					if(RevSq[i] == NULL)
					{
						printf("ERROR malloc RBuf fail\n");
						return;
					}
					break;
				}
			}
			if(i>=MAX_RECEIVE_SQ)
			{
				printf("Warning Receive sq full\n");
			}
			
		}
	}
	#endif
}

u8 ESP_reset(void)
{
	
}








