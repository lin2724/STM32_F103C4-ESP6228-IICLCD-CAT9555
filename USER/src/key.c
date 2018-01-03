#include "key.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "led.h"

int KeyStat = 0;

void KeyInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(KEY_APB, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = KEY_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(KEY_IO, &GPIO_InitStruct);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource4);

	EXTI_InitStruct.EXTI_Line = EXTI_Line0|EXTI_Line1|EXTI_Line4;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn|EXTI1_IRQn|EXTI4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
}

//key1
void EXTI0_IRQHandler(void)
{
	EXTI_ClearFlag(EXTI_Line0);
//	KeyStat|=KEY1;
//	if(ReadLedStat(LED1))LedCmd(LED1,OFF);
//	else LedCmd(LED1,ON);
}
//key2
void EXTI1_IRQHandler(void)
{
	EXTI_ClearFlag(EXTI_Line1);
//	KeyStat|=KEY2;
//	if(ReadLedStat(LED2))LedCmd(LED2,OFF);
//	else LedCmd(LED2,ON);
}
//key4
void EXTI4_IRQHandler(void)
{
	EXTI_ClearFlag(EXTI_Line4);
//	KeyStat|=KEY3;
//	if(ReadLedStat(LED))LedCmd(LED3,OFF);
//	else LedCmd(LED3,ON);
}




