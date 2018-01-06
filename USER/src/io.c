#include "io.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
void SteeringEngineIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

}



u8 ShockCount = 0;
u8 ShockFlag = 0;
void EXTI15_10_IRQHandler(void)
{
	EXTI_ClearFlag(EXTI_Line11);
	if(!GPIO_ReadInputDataBit( GPIOA,  GPIO_Pin_11))
	{
		return;
	}
	if(0==ShockCount)
	{
		TIM_SetCounter( TIM2, 0);
		TIM_Cmd(TIM2, ENABLE);
	}
	
		ShockCount++;
	
}
