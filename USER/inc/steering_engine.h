#ifndef _STEERING_ENGINE_H_
#define _STEERING_ENGINE_H_
#include "type.h"

#define STE_ENG_PERIOD_US (20000)  //20 ms period

extern void IntIoInit(void);
extern void ST_ENG_TimerRunFunc(void);
extern u32 gSteEngPwmUs;

extern void SteeringEngineIO_CMD(u32 cmd);
extern void StEngSetDegree(u32 u32Degree);
extern void SteeringEngine_init();
#endif