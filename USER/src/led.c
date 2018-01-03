#include "led.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


/******************
* @brief:
* @param:
* @date:2015.8.13
* @aulther: zzl
* @other:
 *******************/

void LedInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(LED_APB, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = LED_PIN1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(LED_IO1, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED_PIN2;
	GPIO_Init(LED_IO2, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED_PIN3;
	GPIO_Init(LED_IO3, &GPIO_InitStruct);
}

/******************
* @brief:
* @param:combaition of LED1 LED2 LED3
				cmd : ON or OFF
* @date:2015.8.13
* @aulther: zzl
* @other:
 *******************/
void LedCmd(int arg, int cmd)
{
	if(cmd)
	{
		if(arg&LED1)LED1_ON;
		if(arg&LED2)LED2_ON;
		if(arg&LED3)LED3_ON;
	}else
		{
			if(arg&LED1)LED1_OFF;
			if(arg&LED2)LED2_OFF;
			if(arg&LED3)LED3_OFF;
		}
}

char ReadLedStat(int arg)
{
	if(arg&LED1)return LED1_STAT;
	if(arg&LED2)return LED2_STAT;
//	if(arg&LED3)return LED3_STAT;
	return 0;
}

signed char LedCount=0;
void LedTask(void)
{
	if(LedCount<=0)return;
	if(LedCount<=1)LedCmd(LED1,OFF);
	LedCmd(LED1,ON);
	LedCount--;
	
}
