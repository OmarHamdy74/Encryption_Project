#include "UART.h"

/*$PAGE*/
/*
*********************************************************************************************************
*                                      UART initialization
*
* Description: This function use to enable UART peripheral and set the parameters.
*			   Setup the serial port for 9600 baud at 11.0592MHz.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/
void uart_init()
{
    TMOD |= 0x20;               /* TMOD: timer 1, mode 2, 8-bit reload        */
    SCON  = 0x50;		        /* SCON: mode 1, 8-bit UART, enable rcvr      */
    TH1   = 0xFD;                /* TH1:  reload value for 9600 baud @ 11.0592MHz   */
    TR1   = 1;                  /* TR1:  timer 1 run                          */
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                      UART send data
*
* Description: This function use to send passed data via UART peripheral.
*
* Arguments  : mad		is a character will send in Tx pin.
*
* Returns    : None
*********************************************************************************************************
*/
void uart_data(unsigned char mad)
{
    SBUF=mad;
    while(TI==0);
    TI=0;
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                      UART send string
*
* Description: This function use to send array of char via UART peripheral.
*
* Arguments  : mad		is a point to the 1st element of string.
*
* Returns    : None
*********************************************************************************************************
*/
void uart_string(unsigned char mad[])
{
    unsigned int j;

    for(j=0; mad[j]!='\0'; j++)
        uart_data(mad[j]);
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                      UART get data
*
* Description: This function use to data from UART peripheral
*
* Arguments  : None.
*
* Returns    : ch	   is a character will receive data.
*********************************************************************************************************
*/
unsigned char uart_rx()
{
    unsigned char ch;
    while(RI==0);
    ch=SBUF;
    RI = 0;
    return (ch);
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                      UART get string
*
* Description: This function use to receive data and put it into array of characters
*
* Arguments  : None.
*
* Returns    : output	is a point to the 1st element of string.
*********************************************************************************************************
*/
char* uart_getstring(void) reentrant
{
    static char output[26];
    char* str = output;
    do
    {
        str++;
        *str = uart_rx();
    }
    while(*str != '\r');
    *str = '\0';
    return output+1;
}

