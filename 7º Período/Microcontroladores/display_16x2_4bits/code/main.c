#include <16F877.h>
#device ADC=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20000000)
#use rs232(baud=9600, xmit=PIN_B5, ERRORS) 

#define LCD_DATA_PORT getenv("SFR:PORTD")
#define LCD_ENABLE_PIN   PIN_D0
#define LCD_RS_PIN               PIN_D1
#define LCD_RW_PIN             PIN_D2

#include <LCD.C>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>


 


void main()
{
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_32);
   set_adc_channel(0); 
   lcd_init();
   delay_us(20);
   printf(lcd_putc,"Gabriela e Vitor");
   float Temp = 0;       
   float r = 0;
   while(TRUE)
   { 
      r =read_adc();          
      Temp =  0.0005524*r*r-2.5*r+579.5;
      printf(lcd_putc,"\r\nLDR: %f          \n", Temp); 
      delay_ms(500);
   }

}
