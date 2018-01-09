#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stdio.h"
#include "sys.h"

#include "delay.h"
#include "step_moto.h"


/*
**LEFT_CTL1 PC5
**LEFT_CTL2 PB7
**
**RIGHT_CTL1 PG14
**RIGHT_CTL2 PG15
*/



#ifndef FOWARD
#define FOWARD (1)
#define BACK (0)
#endif

#define X_EN_IO PAout(7)
#define X_DIR_IO PBout(0)
#define X_STEP_IO PBout(11)

/*F为远端 B为近端*/
#define X_LIMTE_F_IO PBin(5)
#define X_LIMTE_B_IO PBin(6)

#define Y_EN_IO PAout(11)
#define Y_DIR_IO PAout(12)
#define Y_STEP_IO PBout(12)

#define Y_LIMTE_F_IO PBin(7)
#define Y_LIMTE_B_IO PCin(13)

void x_moto_enable(void)
{
	X_EN_IO=MOTO_ENABLE_LEVEL;
}
void x_moto_disable(void) 
{
	X_EN_IO=MOTO_DISABLE_LEVEL;
}
void y_moto_enable(void)
{
	Y_EN_IO=MOTO_ENABLE_LEVEL;
}
void y_moto_disable(void)
{
	Y_EN_IO=MOTO_DISABLE_LEVEL;
}

int G_sensor = 0;
int G_zoom = 10;

volatile int CurPointX=0;
volatile int CurPointY=0;

/******************
* @brief:驱动电机控制io初始化
* @param:
* @date:2015.1.6
* @aulther: zzl
* @other:
 *******************/

void step_moto_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
//	NVIC_InitTypeDef NVIC_InitStruct;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
/**********					初始化马达控制io				**************/
	/************x轴************/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	/*************y轴***************/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	/******传感器的IO设置 上拉 有接触被拉低*******/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;//GPIO_Mode_IN_FLOATING
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStruct);//z轴限位开关
	/************/

	x_moto_disable();
	y_moto_disable();
}



#define DELAY 300
u32 xmotostep(int dir, int step)
{
	int i;
	u32 step_cnt = 0;
	X_DIR_IO=dir>0?0:1;//////////////////////

	for(i=0;i<step*G_zoom;i++)
	{
			SensorDetect();
			if(dir>0)
			{
				if(G_sensor&(X_LIM_F_bit))
				{
					break;
				}
			}else
			{
				if(G_sensor&(X_LIM_B_bit))
				{
					break;
				}
			}
			
		//X_STEP_IO=1;
		//delay_us(DELAY);
		X_STEP_IO=0;
		delay_us(DELAY);
		X_STEP_IO=1;
			delay_us(DELAY);
			step_cnt += 1;

	}
	
	
	if(dir>0)
	{
		CurPointX+=step_cnt;
	}
	else 
	{
		CurPointX-=step_cnt;
	}
	return step_cnt;
}

u32 ymotostep(int dir, int step)
{
	int i;
	u32 step_cnt = 0;
	Y_DIR_IO=dir>0?0:1;//////////////////////

	
	for(i=0;i<step*G_zoom;i++)
	{
			SensorDetect();
			if(dir>0)
			{
				if(G_sensor&(Y_LIM_F_bit))
				{
					break;
				}
			}else
			{
				if(G_sensor&(Y_LIM_B_bit))
				{
					break;
				}
			}
			
		//Y_STEP_IO=1;
		//delay_us(DELAY);
		Y_STEP_IO=0;
		delay_us(DELAY);
		step_cnt += 1;
		Y_STEP_IO=1;
			delay_us(DELAY);

	}

	
	if(dir>0)
	{
		CurPointY+=step_cnt;
	}
	else 
	{
		CurPointY-=step_cnt;
	}
	return step_cnt;
}


void SensorDetect(void)
{
	
	G_sensor = 0;

	/*没信号是高电平 可以进行 有接触变为低电平 不可移动*/
		if(X_LIMTE_F_IO)
			{
				G_sensor &= ~(X_LIM_F_bit);
			}else
				{
					G_sensor |= (X_LIM_F_bit);
				}
		
		if(X_LIMTE_B_IO)
			{
				G_sensor &= ~(X_LIM_B_bit);
			}else
				{
					G_sensor |= (X_LIM_B_bit);
				}
		
		if(Y_LIMTE_F_IO)
			{
				G_sensor &= ~(Y_LIM_F_bit);
			}else
				{
					G_sensor |= (Y_LIM_F_bit);
				}
		
		if(Y_LIMTE_B_IO)
			{
				G_sensor &= ~(Y_LIM_B_bit);
			}else
				{
					G_sensor |= (Y_LIM_B_bit);
				}
}
struct MotoCtl
{
	u32 set_speed;//100 max
	signed int cnt;
	u32 block;
	u32 tic_half;
	u32 tic_speed;//tic_speed = 100/set_speed
};

struct MotoCtl gXMotoCtl;
struct MotoCtl gYMotoCtl;

void X_SetMotoRunBlock(u32 dir, u32 cnt, u32 speed)
{
	x_moto_enable();
	while(gXMotoCtl.cnt)
	{
		delay_us(DELAY);
	}
	gXMotoCtl.set_speed = speed;
	gXMotoCtl.cnt = dir>0?cnt:-cnt;
	while(gXMotoCtl.cnt)
	{
		delay_us(DELAY*3);
	}
	x_moto_disable();
}
void X_SetMotoRunNonBlock(u32 dir, u32 cnt, u32 speed)
{
	gXMotoCtl.set_speed = speed;
	gXMotoCtl.cnt = dir>0?cnt:-cnt;
}

void Y_SetMotoRunBlock(u32 dir, u32 cnt, u32 speed)
{
	y_moto_enable();
	while(gYMotoCtl.cnt)
	{
		delay_us(DELAY);
	}
	gYMotoCtl.set_speed = speed;
	gYMotoCtl.cnt = dir>0?cnt:-cnt;
	while(gYMotoCtl.cnt)
	{
		delay_us(DELAY*3);
	}
	y_moto_disable();
}
void Y_SetMotoRunNonBlock(u32 dir, u32 cnt, u32 speed)
{
	gYMotoCtl.set_speed = speed;
	gYMotoCtl.cnt = dir>0?cnt:-cnt;
}

void StartNonBlockStepMoto(void)
{
	x_moto_enable();
	y_moto_enable();
}

void EndNonBlockStepMoto(void)
{
	while(gXMotoCtl.cnt || gYMotoCtl.cnt)
	{
		delay_us(DELAY*3);
	}
	x_moto_disable();
	y_moto_disable();
}

void Step_Moto_TimerRunFunc(void)
{
	u32 u32Dir = 0;
	SensorDetect();
	do
	{
		if(gXMotoCtl.cnt)
		{
			if(gXMotoCtl.cnt>0)
			{
				u32Dir = FOWARD;
				if(G_sensor&(X_LIM_F_bit))
				{
					gXMotoCtl.cnt = 0;
					break;
				}
			}
			else
			{
				u32Dir = BACK;
				if(G_sensor&(X_LIM_B_bit))
				{
					gXMotoCtl.cnt = 0;
					break;
				}
			}
			X_DIR_IO=u32Dir>0?0:1;
			if(0 == gXMotoCtl.tic_speed)
			{
				if(gXMotoCtl.tic_half)
				{
					gXMotoCtl.tic_half = 0;
					X_STEP_IO=1;
					gXMotoCtl.cnt += u32Dir>0?-1:1;
				}
				else
				{
					gXMotoCtl.tic_half = 1;
					X_STEP_IO=0;
				}
				gXMotoCtl.tic_speed = 0;//100/gXMotoCtl.set_speed;
			}
			else
			{
				gXMotoCtl.tic_speed -= 1;
			}
		}
	}while(0);
	
	do
	{
		if(gYMotoCtl.cnt)
		{
			if(gYMotoCtl.cnt>0)
			{
				u32Dir = FOWARD;
				if(G_sensor&(Y_LIM_F_bit))
				{
					gYMotoCtl.cnt = 0;
					break;
				}
			}
			else
			{
				u32Dir = BACK;
				if(G_sensor&(Y_LIM_B_bit))
				{
					gYMotoCtl.cnt = 0;
					break;
				}
			}
			Y_DIR_IO=u32Dir>0?0:1;
			if(0 == gYMotoCtl.tic_speed)
			{
				if(gYMotoCtl.tic_half)
				{
					gYMotoCtl.tic_half = 0;
					Y_STEP_IO=1;
					gYMotoCtl.cnt += u32Dir>0?-1:1;
				}
				else
				{
					gYMotoCtl.tic_half = 1;
					Y_STEP_IO=0;
				}
				gYMotoCtl.tic_speed = 0;//100/gYMotoCtl.set_speed;
			}
			else
			{
				gYMotoCtl.tic_speed -= 1;
			}
		}
	}while(0);
}

 


