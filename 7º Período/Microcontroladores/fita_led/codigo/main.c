#include <16F877A.h>
#device ADC=8

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20000000)

// I2C Configuration: I2C1 == Default pins and use Hardware Interrupts
#use i2c(MASTER, I2C1)

// Color cache to see what user typed
// 16 bit because user can type up to 999
uint16_t rgb_buffer[3] = {0, 0, 0};

// Color to be writen on LED strip
uint16_t rgb_map[3] = {0, 0, 0};

// Cursor reference to write on 16x2
// Assuming it is on 2nd row
uint8_t cursor_map[3] = {1, 6, 11};

#include <16x2_pcf8574.c>
#include <4x4_keyboard.c>

#use FIXED_IO(B_outputs=PIN_B4, PIN_B5, PIN_B6, PIN_B7)
#use FIXED_IO(D_outputs=PIN_D0, PIN_D1, PIN_D2)

// count from 0 to 255
uint8_t counter = 0;

#INT_TIMER2
void  TIMER2_isr(void) 
{
   // it checks if the color value is greater than the pulse
   // ex: if 127, when counter < 127 it is on, if >= 127 it is off
   // do this for all leds and output_d
   output_d(0b00000000 | ((rgb_map[1]>counter)<<2) | ((rgb_map[0]>counter)<<1) | ((rgb_map[2]>counter)));
   counter++;
}


void main()
{
   // PIC uses 7 bit + R/W 
   // 0x4E = 0x27 << 7 
   initializeLCD(0x4E, 16, 2);
   
   port_B_pullups(0xFF);
   delay_ms(1000);
      
   char c[16] = "Escolha a cor: ";
   printstr(c);
   
   setCursor(0,1);
   
   char d[16] = "R000 G000 B000";
   printstr(d);
   
   setCursor(1,1);
   
   setup_timer_2(T2_DIV_BY_4,5,13);      // 4,8 us overflow, 62,4 us interrupt
   enable_interrupts(INT_TIMER2);
   enable_interrupts(GLOBAL);   
   
   while(TRUE) scanPorts();
}

