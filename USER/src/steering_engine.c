#include "stm32f10x_gpio.h"
#include "steering_engine.h"
#include "io.h"
#include "timer.h"

u32 gSteEngPwmUs = 0;
void SteeringEngineIO_CMD(u32 cmd)
{
	if (cmd)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_14);
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);
	}
}

u32 gTimerPeriodSet = 1;

void TimerPeriodSetUs(u32 u32SetTimerPeriod)
{
		gTimerPeriodSet = u32SetTimerPeriod;
}

void SteeringEngine_init()
{
	SteeringEngineIO_Init();
	SteeringEngineIO_CMD(0);
	TimerPeriodSetUs(TIMER1_PERIOD_US);
}

void StEngSetDegree(u32 u32Degree)
{
		if (u32Degree > 180)
		{
				u32Degree = 180;
		}
		//gSteEngPwmUs = u32Degree/180*5*1000 + 500;
		gSteEngPwmUs = u32Degree*5*1000/180 + 500;
}


void ST_ENG_TimerRunFunc(void)
{
	static u32 u32StEngTic = 0;
	u32StEngTic += gTimerPeriodSet;
	if(u32StEngTic >= STE_ENG_PERIOD_US)
	{
		u32StEngTic = 0;
		if (0 != gSteEngPwmUs)
		{
			SteeringEngineIO_CMD(1);
		}
	}
	
	if(u32StEngTic > gSteEngPwmUs)
	{
		SteeringEngineIO_CMD(0);
	}
}










