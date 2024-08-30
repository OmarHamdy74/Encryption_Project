#include "TMR_interface.h"

void TMR_init()
{
	TMOD = 0x01;
}

void TMR_delay(char PreloadValue_H, char PreloadValue_L, char No_Iterations)
{
	char i = 0;
	for (i = 0; i < No_Iterations; i++)
	{
		//Load The timer 
		TL0 = PreloadValue_L;
		TH0 = PreloadValue_H;

		//start TMR0
		TR0 = 1;
		while (TF0 != 1);
		//stop TMRo
		TR0 = 0;
		//clear TF0
		TF0 = 0;
	}


}