#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "key.h"
#include "led.h"
#include "wifi_test.h"
#include "timer.h"
#include "steering_engine.h"
#include "step_moto.h"
#include "2d_method.h"
 int main(void)
 {		
 	signed int t=0;
	signed char point = 1;
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart2_init(9600);	 //串口初始化为9600
	uart1_init(9600);	 //串口初始化为9600
	LedInit();
	WifiIoInit();
	Timer2Init();
	Timer3Init();
	SteeringEngine_init();
	step_moto_init();
	while(1)
	{
		StartNonBlockStepMoto();
		X_SetMotoRunNonBlock(FOWARD, 50000, 100);
		Y_SetMotoRunNonBlock(FOWARD, 50000, 50);
		EndNonBlockStepMoto();
		StartNonBlockStepMoto();
		X_SetMotoRunNonBlock(BACK, 50000, 100);
		Y_SetMotoRunNonBlock(BACK, 50000, 50);
		EndNonBlockStepMoto();
		//AdjustPlatForm();
	}
	while(1)
	{
		xmotostep(1, 50);
		ymotostep(0, 50);
		delay_ms(1000);
		xmotostep(1, 50);
		ymotostep(1, 50);
		delay_ms(1000);
	}
	
	while(1){

		for(t=0; t<=180; t+=10)
		{
				StEngSetDegree(t);
				delay_ms(40);
		}
		for(t=180; t>=0; t-=10)
		{
				StEngSetDegree(t);
				delay_ms(40);
		}
		continue;
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

