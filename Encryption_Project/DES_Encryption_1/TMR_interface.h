#ifndef TMR_INTERFACE_H
#define TMR_INTERFACE_H

#include <reg52.h>

void TMR_init();
void TMR_delay(char PreloadValue_H , char PreloadValue_L, char No_Iterations);

#endif