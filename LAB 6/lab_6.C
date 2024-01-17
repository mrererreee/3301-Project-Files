#include <stdio.h>
#include <stdlib.h>
#include "config.h"
/*
 * 
 */
int main() 
    {
        char sseg[16] = {0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84, 0x88, 0xE0, 0xB1, 0xC2, 0xB0, 0xB8};
   //     char sseg1[8] = {0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F};
   //     char sseg2[8] = {0x81, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F};
    // Turn off ADC
        ADCON1 = 0xff;
    
    // PORTA is output (connected to 7segment display)
        TRISA = 0x00;
 
    // PORTB is input (connected to switches) wrong port
      //  TRISB = 0xff;
        
        TRISD = 0xff;
    
        while (1)
        {
           unsigned int num1 = PORTD & 0x07;
           unsigned int num2 = (PORTD >> 3) & 0x07;
           unsigned int SUM = num1 + num2;
           PORTA = sseg[SUM];
            
       // test for lower bits
      // PORTA = sseg1[PORTB & 0x07];
       //int num1 = PORTA;
       // test for upper bits to show on screen
      // PORTA = sseg2[{PORTB >> 3) & 0x07];
      // first attempted shift
       //     int shift = ((PORTB >> 5) & 0x07) | (PORTB & 0xFFF8));
       //   int num2 = PORTA;
       //  unsigned int SUM = num1 + num2;
       //   PORTA = sseg[SUM];
       
        }

    return (EXIT_SUCCESS);
}
