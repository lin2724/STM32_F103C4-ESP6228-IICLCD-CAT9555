#ifndef _LED_H_
#define _LED_H_





/***********
PB5 -led1
PE6 -led2
//PA7 -led3
*************/

#define LED_APB (RCC_APB2Periph_GPIOB)
#define LED_IO1	GPIOB
#define LED_PIN1 (GPIO_Pin_1)
#define LED_IO2	GPIOA
#define LED_PIN2 (GPIO_Pin_6)
#define LED_IO3	GPIOA
#define LED_PIN3 (GPIO_Pin_7)

#define LED1_ON (GPIO_ResetBits( GPIOB, GPIO_Pin_1))
#define LED1_OFF (GPIO_SetBits( GPIOB, GPIO_Pin_1))
#define LED2_ON (GPIO_ResetBits( GPIOA, GPIO_Pin_6))
#define LED2_OFF (GPIO_SetBits( GPIOA, GPIO_Pin_6))
#define LED3_ON (GPIO_ResetBits( GPIOA, GPIO_Pin_7))
#define LED3_OFF (GPIO_SetBits( GPIOA, GPIO_Pin_7))

#define LED1_STAT (!GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_1))
#define LED2_STAT (!GPIO_ReadInputDataBit( GPIOA, GPIO_Pin_6))
#define LED3_STAT (!GPIO_ReadInputDataBit( GPIOA, GPIO_Pin_7))

#define LED1 (1<<1)
#define LED2 (1<<2)
#define LED3 (1<<3)

#define ON 1
#define OFF 0


extern char ReadLedStat(int arg);
extern void LedCmd(int arg, int cmd);
extern void LedInit(void);

#endif
