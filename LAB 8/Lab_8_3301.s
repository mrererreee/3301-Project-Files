config OSC = INTIO2
config BOR = OFF    ;Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
config STVREN = OFF ;Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
config WDT = OFF    ;Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
config MCLRE = ON   ;MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

    #include <xc.inc>
    psect code 
psect	IntCodeHi, class = CODE, reloc = 2
bcf	INTCON, 1, a
ORG	0x00
goto	main
 
ORG	0x00100
 
main:
    setf    ADCON1, a
    movlw   0x10
    clrf    TRISD, a
    bsf	    TRISB, 1, a
    setf    PORTD, a
    
    movlw   10010000B
    movwf   INTCON, 6, a
    bcf	    INTCON3, INT1IF, a
    bsf	    INTCON, INT1IE, a
    
wait:
    bra	    wait
    bra	    main
ORG	0x000008

interrupt:
    movff   PORTB, PORTD, a
    bcf	    INTCON, 1, a
    
    retfie 
    
end
    
    
