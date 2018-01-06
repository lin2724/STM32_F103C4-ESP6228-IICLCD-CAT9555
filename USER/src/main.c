#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "key.h"
#include "led.h"
#include "wifi_test.h"
#include "timer.h"
#include "steering_engine.h"
 int main(void)
 {		
 	u8 t=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart2_init(9600);	 //���ڳ�ʼ��Ϊ9600
	uart1_init(9600);	 //���ڳ�ʼ��Ϊ9600
	LedInit();
	WifiIoInit();
	Timer2Init();
	SteeringEngine_init();
	while(1){
		LedCmd(LED1|LED2|LED3,OFF);
		StEngSetDegree(0);
		delay_ms(500);
		StEngSetDegree(60);
		//LedCmd(LED1,ON);
		delay_ms(500);
		StEngSetDegree(90);
				//LedCmd(LED2,ON);
		delay_ms(500);
		StEngSetDegree(180);
				//LedCmd(LED3,ON);
		delay_ms(500);
//	printf("t:%d\n",t);
//	LedCmd(LED1,ON);
//USART_SendData(USART2, 'f');
//	delay_ms(50);
//	LedCmd(LED1,OFF);
//	delay_ms(50);
	t++;
	}
 }

