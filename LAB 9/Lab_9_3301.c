/* 
 * File:   Lab_9_3301.c
 * Author: Danielle Johnson
 *
 * Created on July 24, 2023, 10:21 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Lab_9_3301.h"
#include "LiquidCrystal.h"


#define  _XTAL_FREQ  10000000

void __interrupt() adc_sample(void);

volatile unsigned int num;
volatile unsigned int voltage;

//you can use double instead of straight dividing otherwise you will get 0
int main() 
{
    
    // ALL ANx input are digital
    ADCON1 = 0x0E;
    TRISAbits.RA0 = 1; // setting up ADC
    
    ADCON2bits.ADCS = 0; // FOSC/2
    ADCON2bits.ACQT = 1; // ACQT = 2 TAD
    ADCON2bits.ADFM = 1; // Right justified
    
    ADCON0bits.CHS = 0; 
    
    ADCON0bits.ADON = 1;
    
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    IPR1bits.ADIP = 1; 
    RCONbits.IPEN = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    // Data pins connected to PORTC
    TRISC = 0x00;  
    
    // RS = RD0
    // RW = RD1
    // E  = RD2 
    TRISD = 0x00;
    
    TRISB = 0x00; //connected to decoders
    
    // connect the LCD pins to the appropriate PORT pins
    pin_setup(&PORTC, &PORTD);
    
    // initialize the LCD to be 16x2 (this is what I have, yours might be different)
    begin(16, 2, LCD_5x8DOTS);
    
    while (1)
    {
        ADCON0bits.GO = 1;
        home();
        print("RAW:");
        print_int(num);
        print("    ");
        setCursor(0, 1);
        
        voltage = (50 * num) / 1023; 
    
        int num1 = voltage/10; //lower 
        print("N1:");
        print_int(num1);
        print(",  ");
 
        int num2 = voltage%10; //upper
        print("N1:");
        print_int(num2);
        print("  ");

        
        PORTB = ((num1 << 4) & 0xF0) | (num2 & 0x0F);
    }   
    return 0;

}

void __interrupt() adc_sample(void)
{
    
    // ADC Interrupt
    if (PIR1bits.ADIF && PIE1bits.ADIE)
    {
      
        PIR1bits.ADIF = 0;
        
        num = (ADRESH << 8) | ADRESL;

    }
}

