#include <xc.inc>
    org 0x100
   num_AL equ 0x20
   num_AM equ 0x21
   num_AH equ 0x22
 
   num_BL equ 0x50
   num_BM equ 0x51
   num_BH equ 0x52
  
   num_CL equ 0x50
   num_CM equ 0x51
   num_CH equ 0x52
 
 ; AL = f1
 movlw 0xB5
 movwf num_AL, f, a
 ;BL=04
 movlw 0x04
 movwf num_BL, f, a
 
 ;AM=91
 movlw 0x91
 movwf num_AM, f, a
 ;BM=A2
 movlw 0xA2
 movwf num_BM, f, a
 
 ;AH=F1
 movlw 0xF1
 movwf num_AH, f, a
 ;BH=A2
 movlw 0x07
 movwf num_BH, f, a
 
 ;clrf wreg
 
 ; sum the low bytes 
 movwf num_AL, w, a 
 addwf num_BL, w, a
 
 ;move to freg
  movwf num_CL, f, a
 
 ; sum the middle bytes 
 movwf num_AM, w, a 
 addwf num_BM, w, a
 
 ; move to freg
 movwf num_CM, f, a
 
 ; sum the high bytes 
 movwf num_AH, w, a 
 addwfc num_BH, w, a
 
 ;result may have a carry 
 ;before we add the upper bytes, we have to figure out if there is a carry 
 ;and store it in the freg
 
 movwf num_CH, f, a
 
    end

