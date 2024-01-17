#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "LiquidCrystal.h"

# define _XTAL_FREQ 1000000 
# define SWITCH1 PORTDbits.RD3
# define SWITCH2 PORTDbits.RD4
void __interrupt() adc_sample(void);
void addition();
void subtraction();
void multiplication();

volatile int num_pot;
volatile int num_pot2;

int main() 
{
    TRISB = 0x00;
    TRISD = 0x18;
    pin_setup(&PORTB, &PORTD);
    begin(16, 2, LCD_5x8DOTS);
    
    
    ADCON1 = 0x0D;
    TRISAbits.RA0 = 1;
    TRISAbits.RA1 = 1;
    ADCON2bits.ADCS = 0;
    ADCON2bits.ACQT = 1;
    ADCON2bits.ADFM = 1;
    ADCON0bits.CHS = 0;
    ADCON0bits.ADON = 1;
    
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    IPR1bits.ADIP = 1;
    RCONbits.IPEN = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    while (1) {
        ADCON0bits.GO = 1;
        home();
        if (SWITCH1 == 0 && SWITCH2 == 0) {
            clear();
        }
        else if (SWITCH1 == 1 && SWITCH2 == 0) {
            home();
            addition();
        }
        else if (SWITCH1 == 0 && SWITCH2 == 1) {
            home();
            subtraction();
        }
        else if (SWITCH1 == 1 && SWITCH1 == 1) {
            home();
            multiplication();
        } 
        
    }
    return 0;
}

void __interrupt() adc_sample(void) {
    if(PIR1bits.ADIF && PIE1bits.ADIE)
    {
        PIR1bits.ADIF = 0;
        
        if(ADCON0bits.CHS == 0) {
            num_pot = (ADRESH << 8) | ADRESL;
            ADCON0bits.CHS = 1;
        }
        else if (ADCON0bits.CHS == 1) {
            num_pot2 =(ADRESH << 8)| ADRESL;
            ADCON0bits.CHS = 0;
        }
    }
}

void addition() {
    int num1 = num_pot - 512;
    int num2 = num_pot2 - 512;
    int answer = num1 + num2;
    print("(");
        print_int(num1);
        print(")");
        print("+");
        print("(");
        print_int(num2);
        print(") = ");
        setCursor(0,1);
        print_int(answer);
        print("     ");
    
}

void subtraction() {
    int num1 = num_pot - 512;
    int num2 = num_pot2 - 512;
    int answer = num1 - num2;
    print("(");
        print_int(num1);
        print(")");
        print("-");
        print("(");
        print_int(num2);
        print(") = ");
        setCursor(0,1);
        print_int(answer);
        print("     ");
}

void multiplication() {
    long num1 = num_pot - 512;
    long num2 = num_pot2 - 512;
    long answer = (long) num1 * num2;
        print("(");
        print_long(num1);
        print(")");
        print("x");
        print("(");
        print_long(num2);
        print(") = ");
        setCursor(0,1);
        print_long(answer);
        print("     ");
}
