config OSC = INTIO2
config BOR = OFF    ;Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
config STVREN = OFF ;Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
config WDT = OFF    ;Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
config MCLRE = ON   ;MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
    
    
#include <xc.inc>
ORG	0x00
goto main  
ORG	0x100
    psect code
 
main:
    setf    ADCON1, a
    clrf    TRISD, a 
    movlw   0x0F
    bsf	    TRISB, 1, a
    movwf   ADCON1, a
    setf    PORTD, a
begin:
    bcf	    PORTD, 1, a

check:	
    btfss   PORTB, 1, a
    bra	    begin
    bsf	    PORTD, 1, a
    bra	    check
   
end