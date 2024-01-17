/* 
 * File:   Lab_8_3301.c
 * Author: danie
 *
 * Created on July 18, 2023, 2:06 PM
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "Lab_8_3301.h"


/*
 * 
 */

#define _XTAL_FREQ 10000000
#define  COMP PORTBbits.RB1
#define  oput PORTDbits.RD1  
void __interrupt(high_priority) LED(void);
int count = 0;
int main() 
{ 
    ADCON1 = 0x0F;
    TRISD = 0x00;//portD is an output
    TRISB  = 0xFF;
    COMP = 1;    // portB is an input
    INTCONbits.GIE = 1;  //enable global interrupts
    INTCONbits.GIEH = 1; // making this high priority 
    
    INTCON3bits.INT1IE =1;  //enable external interrupt
    INTCON3bits.INT1IF = 0; // reset INT1 flag 
    INTCON2bits.INTEDG1 = 1; //rising edge, = 0 for falling edge 
   
    while(1) 
    {
    
        
    }
    
    
    
    return (EXIT_SUCCESS);
}
// this is called when INT1 is 1 --> Vx > Vy
void __interrupt(high_priority) LED(void)
{
    if(INTCON3bits.INT1IE && INTCON3bits.INT1IF)
    { 
        INTCON3bits.INT1IF = 0;
         oput = COMP;
    }
}
 

