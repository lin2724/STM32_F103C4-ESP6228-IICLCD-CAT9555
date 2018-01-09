#include "type.h"
#include "2d_method.h"
#include "step_moto.h"


void AdjustPlatForm(void)
{
	u32 u32xMax = 0;
	u32 u32yMax = 0;
	SensorDetect();
	
	x_moto_enable();
	y_moto_enable();
	while(!(G_sensor&(Y_LIM_F_bit)) || !(G_sensor&(X_LIM_F_bit)))
	{
		xmotostep(FOWARD, 10);
		ymotostep(FOWARD, 10);
	}
	while(!(G_sensor&(Y_LIM_B_bit)) || !(G_sensor&(X_LIM_B_bit)))
	{
		xmotostep(BACK, 1);
		if(!G_sensor&(X_LIM_B_bit))
		{
			u32xMax += 1;
		}
		ymotostep(BACK, 1);
		if(!G_sensor&(Y_LIM_B_bit))
		{
			u32yMax += 1;
		}
	}
	x_moto_disable();
	y_moto_disable();
}

