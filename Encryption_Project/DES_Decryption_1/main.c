#include <REG52.H>                
#include <stdio.h>                
#include "datatypes.h"
#include "DES.h"
#include "UART.h"

/*
**************************************
*                                               VARIABLES
**************************************
*/


#define INT0_INTERUPT_INDEX 0
unsigned int i;
unsigned char Key_was_set = 0;
volatile unsigned char cipher_was_set = 0;
volatile signed char counter = -1;
unsigned char Key[8];
unsigned char Plain_Text[8];
unsigned char Cipher_Text[8];
sbit INT_BIT = P3^2;



/*
**************************************
*                                                MAIN
**************************************
*/

void main (void)
{
	P2 = 0xFF; 		  // Set P2.1 to 0 (clear the bit)
	INT_BIT = 1;
    EA = 1;           // Enable global interrupts
    EX0 = 1;          // Enable external interrupt 0 (INT0)
    IT0 = 1;          // Set INT0 to be edge-triggered (falling edge)


	uart_init();
    uart_string("welcome");

	uart_string("\rEnter Key: ");
	for(i = 0; i < 8; i++){
		unsigned char x = uart_rx();
		Key[i] = x;
	}
	Key_was_set = 1;
	uart_string("\rKey was set ! ");
	uart_string("\r");

    while (1)
    {
		if(cipher_was_set && Key_was_set){
			uart_string("\rCipher_Text Received Is: ");
			for(i = 0; i < 8; i++){
				uart_data(Cipher_Text[i]);
			}
			decrypt(Plain_Text , Cipher_Text , Key);

			uart_string("\rPlain Text is: ");
			for(i = 0; i < 8; i++){
				uart_data(Plain_Text[i]);
			}
			cipher_was_set = 0;
			uart_string("\r");
		}	
    }
}


void INT_ISR() interrupt INT0_INTERUPT_INDEX {
	if (counter == -1)
	{counter++;}
	else
	{
	Cipher_Text[counter] = P2;
	counter++;
	if(counter == 8)
	{
		cipher_was_set = 1;
		counter = -1;
	}
	}		    
}
