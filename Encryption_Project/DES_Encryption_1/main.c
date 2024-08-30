#include <REG52.H>                
#include <stdio.h>                
#include "datatypes.h"
#include "DES.h"
#include "UART.h"
#include "TMR_interface.h"

/*
**************************************
*                                               VARIABLES
**************************************
*/
unsigned int i;
unsigned char Key[8];
unsigned char Plain_Text[8];
unsigned char temp[8];
unsigned char Cipher_Text[8];
sbit INT_BIT = P1^0;

/*
**************************************
*                                                MAIN
**************************************
*/

void main (void)
{
	TMR_init();
    uart_init();
    uart_string("welcome");

	P2 = 0x00; 		  // Set P2.1 to 0 (clear the bit)
	P1 = 0x00;  
	P1 &= ~(1 << 0);


	uart_string("\rEnter Key: ");
	for(i = 0; i < 8; i++){
		unsigned char x = uart_rx();
		Key[i] = x;
	}
	uart_string("\r");

    while (1)
    {
		uart_string("\rEnter Plain_Text: ");
		for(i = 0; i < 8; i++){
			unsigned char x = uart_rx();
			Plain_Text[i] = x;
		}
        
		encrypt(Cipher_Text , Plain_Text, Key);

		uart_string("\rCipher_Text is: ");
		for(i = 0; i < 8; i++){
			uart_data(Cipher_Text[i]);
		}

		P2 = 0xFF;
		INT_BIT = 0;
		TMR_delay(0xA5, 0xFF, 5);
		INT_BIT = 1;
		for (i = 0; i < 8; i++)
		{
			P2 = Cipher_Text[i];
			INT_BIT = 0;
			TMR_delay(0xA5, 0xFF, 5);
			INT_BIT = 1;			
		}										  
		uart_string("\r");						 	
	}
}	
