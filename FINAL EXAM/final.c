#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "LiquidCrystal.h"

#define LED PORTCbits.RC1
#define _XTAL_FREQ 1000000
#define RED_LED PORTBbits.RB1 
// #define BUTTON PORTBbits.RB2

void __interrupt(low_priority) adc_timer(void);
void __interrupt(high_priority) emergency(void);

volatile long num_speed;
volatile long num_delay;
double num2;
double del2;


int main() 
{
    // input output setup/ LCD
    TRISD = 0x00;
    TRISE = 0x00;
    TRISB = 0x01; // changed 11:01

    PR2 =  249;

    pin_setup(&PORTD, &PORTE);
    begin(16,2, LCD_5x8DOTS);
    
    // timer 2 w/ fan
    T2CONbits.T2CKPS = 0b00; // Prescaler 1:1
    T2CONbits.TMR2ON = 1;
    TRISCbits.RC1 = 0;
    CCP2CONbits.CCP2M = 0b1100;
    
    
    // Setup the ADC
    
    ADCON1 = 0x0D;
    TRISAbits.RA0 = 1;
    TRISAbits.RA1 = 1;
    ADCON2bits.ADCS = 0; // FOSC/2
    ADCON2bits.ACQT = 1; // ACQT = 2 TAD
    ADCON2bits.ADFM = 0; // left justified
    ADCON0bits.CHS = 0; // Channel 0 (AN0)
    ADCON0bits.ADON = 1;
    
    // 2 - Configure A/D interrupt (if desired)
    // * Clear ADIF bit
    // * Set ADIE bit
    // * Select interrupt priority ADIP bit
    // * Set GIE bit
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    IPR1bits.ADIP = 0; // change  to 0, setting interrupt to low
    RCONbits.IPEN = 1; // enable priority levels
    INTCONbits.PEIE = 1; // enable peripheral interrupts
    INTCONbits.GIE = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;

    // timer 0 setup
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0x07;
    T0CONbits.T0CS = 0;
    T0CONbits.T08BIT = 1;
    T0CONbits.TMR0ON = 1;
    TMR0 = 101;
            
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    INTCON2bits.TMR0IP = 0;
    IPR1bits.TMR2IP = 0;

    //INT0 setup
    INTCONbits.INT0E = 1; // enable INT0 pin
    INTCONbits.INT0IF = 0; // clr interrupt flag
    INTCON2bits.INTEDG0 = 0;
    
    while(1)
    {
        // 4 - Start conversion: Set GO/DONE(bar) bit
        ADCON0bits.GO = 1;
        
        home();
        print("Max Speed: ");
    //    num2 = (num_speed * 4.011);
        print_int(num_speed);
        print("      "); 
        
        setCursor(0,1);
        print("Delay: ");
        del2 = (num_delay * 10);
        print_int(del2);
        print(" mS");
        print("      ");
        
    }
    
    return (EXIT_SUCCESS);
}

 void __interrupt(high_priority) emergency(void) 
{

    if ((INTCONbits.INT0IE && INTCONbits.INT0IF))
    { 
        __delay_ms(200);
     do 
     {
         CCPR2L = 0;
         CCP2CONbits.DC2B = 0b00;
         RED_LED = 1;
         home();
         print("    STOPPED!         ");
         setCursor(0,1);
         print("                            ");
         
     }
     while(PORTBbits.RB0 == 0);
     __delay_ms(200);
     RED_LED = 0;
     INTCONbits.INT0IF = 0;
    } 
   
    return;
 }


void __interrupt(low_priority) adc_timer(void)
{
    if (PIR1bits.ADIF && PIE1bits.ADIE)
    {
        PIR1bits.ADIF = 0;
        
        if (ADCON0bits.CHS == 0)
        {
           // num_speed = (ADRESL >> 8) | ADRESH;
            num_speed = (ADRESL >> 8) | (ADRESH << 2);
            ADCON0bits.CHS = 1;
            CCPR2L = ADRESH;
            CCP2CONbits.DC2B = ((ADRESL >> 6) | 0x03);
        }
        
        else if (ADCON0bits.CHS == 1) 
        {
            if (num_delay > 0) {
               INTCONbits.TMR0IF = 0; 
            }
            
            num_delay = (ADRESL >> 8) | (ADRESH << 2);
            ADCON0bits.CHS = 0;
        
    }
    }
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) 
    {
        INTCONbits.TMR0IF = 0;
        TMR0 = 105;
        CCPR2L = 0;
                
      
    }
  
    return;

    }
