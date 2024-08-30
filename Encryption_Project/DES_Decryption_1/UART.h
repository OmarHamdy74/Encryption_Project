#ifndef UART_h
#define UART_h

#include <REG52.H>

/*$PAGE*/
/*
*********************************************************************************************************
*                                       FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void uart_init(void);

void uart_data(unsigned char);

void uart_string(unsigned char []);

unsigned char uart_rx();

char* uart_getstring(void) reentrant;

#endif

