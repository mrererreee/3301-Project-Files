/* 
 * File:   Lab_7_3301.c
 * Author: danie
 *
 * Created on July 18, 2023, 11:19 AM
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "Lab_7_3301.h"

/*
 * 
 */
//#define _XTAL_FREQ 10000000
#define     led1    PORTDbits.RD1
#define     oput    PORTBbits.RB1

int main()  
{ 
    ADCON1= 0x0F;
    TRISB = 0xFF; //input
    TRISD = 0x00; //output
    PORTD = 0xFF;
    
    while(1) 
    {
        
        led1 = oput;
        
    }
    
    return (EXIT_SUCCESS);
}
    
