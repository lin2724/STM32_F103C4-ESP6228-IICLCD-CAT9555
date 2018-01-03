#ifndef _KEY_H_
#define _KEY_H_


/***********
PA0 -key1
PA1 -key2
PA4 -key3
*************/

#define KEY_APB (RCC_APB2Periph_GPIOA)
#define KEY_IO	GPIOA
#define KEY_PIN (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4)

#define KEY1 (1<<1)
#define KEY2 (1<<2)
#define KEY3 (1<<3)
extern void KeyInit(void);

#endif
