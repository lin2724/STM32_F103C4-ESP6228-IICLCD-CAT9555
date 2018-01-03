#include "wifi_test.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "delay.h"


//PB0 1
void WifiIoInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_SetBits( GPIOB, GPIO_Pin_0);
	GPIO_SetBits( GPIOB, GPIO_Pin_1);//复位管脚
	delay_ms(100);
	GPIO_ResetBits( GPIOB, GPIO_Pin_1);
	delay_ms(500);
	GPIO_SetBits( GPIOB, GPIO_Pin_1);//复位管脚
}

