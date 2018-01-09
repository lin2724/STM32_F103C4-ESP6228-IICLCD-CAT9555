#ifndef _STEP_MOTO_H_
#define _STEP_MOTO_H_
#include "type.h"
#define X_LIM_F_bit (1<<0)
#define X_LIM_B_bit (1<<1)
#define Y_LIM_F_bit (1<<2)
#define Y_LIM_B_bit (1<<3)


#define FOWARD 1
#define BACK 0
#define MOTO_ENABLE_LEVEL (0)
#define MOTO_DISABLE_LEVEL (1)

extern int G_sensor;
extern int G_zoom ;

extern u32 xmotostep(int dir, int step);
extern u32 ymotostep(int dir, int step);

extern void step_moto_init(void);
extern void SensorDetect(void);
extern void PlatAdjust(void);

extern void x_moto_enable(void);
extern void x_moto_disable(void);
extern void y_moto_enable(void);
extern void y_moto_disable(void);


void X_SetMotoRunBlock(u32 dir, u32 cnt, u32 speed);
void Y_SetMotoRunBlock(u32 dir, u32 cnt, u32 speed);
void X_SetMotoRunNonBlock(u32 dir, u32 cnt, u32 speed);
void Y_SetMotoRunNonBlock(u32 dir, u32 cnt, u32 speed);
void StartNonBlockStepMoto(void);
void EndNonBlockStepMoto(void);


extern void Step_Moto_TimerRunFunc(void);

#endif
