#include "timer.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "led.h"
#include "steering_engine.h"
#include "step_moto.h"
/******************
* @brief:用于风扇速度
* @param:
* @date:2015.7.21
* @aulther: zzl
* @other:
 *******************/

void Timer2Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  //enable clock  36M
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, ENABLE);  //tim2 ch1 PA8
		
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;  //??whats this?
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 10;//ms once 0x7d0
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72;//72M/36 = 1M  100us once
//	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = valid only for TIM1 and TIM8
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	TIM_CounterModeConfig(TIM2, TIM_CounterMode_Up);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	


	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM2, ENABLE);

}

void Timer3Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //enable clock  36M
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA, ENABLE);  //tim2 ch1 PA8
		
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;  //??whats this?
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 250;//ms once 0x7d0
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72;//72M/36 = 1M  100us once
//	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = valid only for TIM1 and TIM8
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	TIM_CounterModeConfig(TIM3, TIM_CounterMode_Up);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	


	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM3, ENABLE);

}

void TIM3_IRQHandler(void)
{
	TIM_ClearITPendingBit( TIM3, TIM_IT_Update);
	Step_Moto_TimerRunFunc();
}

#define CountMax 40
unsigned int LedColor=0;



u8 RedPwm=0;
u8 GrePwm=0;
u8 BluPwm=0;

unsigned int G_StatCount=0;
unsigned int StatPwm=0;


void TIM2_IRQHandler(void)
{
	static u32 u32Tic = 0;
	static u32 u32SteeringEngineTic = 0;
	
	TIM_ClearITPendingBit( TIM2, TIM_IT_Update);
	
	u32Tic += 1;

	if (u32Tic % 5000 == 0)
	{
		LedCmd(LED1,ON);
	}
	if (u32Tic % 10000 == 0)
	{
		LedCmd(LED1,OFF);
	}
	ST_ENG_TimerRunFunc();

	
//	TIM_Cmd(TIM2, DISABLE);

}
