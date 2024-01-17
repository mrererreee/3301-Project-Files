/* 
 * File:   midter.c
 * Author:  heat 
 *
 * Created on July 4, 2023, 11:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
/*
 * 
 */
# define _XTAL_FREQ 1000000 
# define PATTERN1 PORTDbits.RD0
# define PATTERN2 PORTDbits.RD1


int main() {
    // char offsseg[10] = {0xFF, 0xCF, 0x92, 0x86, 0xCC, 0xA4, 0xA0, 0x8F, 0x80, 0x84};
    char csseg[6] = {0xBD, 0x9F, 0xCF, 0xE7, 0xF3, 0xF9};
    char ccsseg[6] = {0x9F, 0xBD, 0xF9, 0xF3, 0xE7, 0xCF};
    
    ADCON1 = 0xFF;
    // output is in port A
    //seg a should be connected to RA6, b RA5, c RA4...
    // dip switches are input, at PORTD, at RD0 and RD1
    // output is in port A
    //seg a should be connected to RA6, b RA5, c RA4...
    // dip switches are input, at PORTD, at RD0 and RD1
    TRISD = 0xFF;
    TRISA = 0x00;
    
int counter1 = 0;
    while (1)
    {
        if(PORTD == 0) {
            PORTA = 0xFF;
        }
        else if(PORTD == 1) {
            PORTA = 0xFE;
            __delay_ms(500); 
            PORTA = 0xFF;
            __delay_ms(500);
        }
        
        else if (PORTD == 2) {
            PORTA = csseg[counter1 % 6];
            counter1 = (counter1 + 1) % 6;
            __delay_ms(500); 
        }
        
        else if(PORTD == 3) {
            PORTA = ccsseg[counter1 % 6];
            counter1 = (counter1 + 1) % 6;
            __delay_ms(500); 
           
        }
          
        
    }
    
return (EXIT_SUCCESS);

}
