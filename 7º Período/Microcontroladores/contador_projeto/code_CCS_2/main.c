#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES BROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20000000)
#use FIXED_IO( A_outputs=PIN_A1,PIN_A0 )
#use FIXED_IO( B_outputs=PIN_B1,PIN_B0 )

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define TM1637_I2C_COMM1    0x40
#define TM1637_I2C_COMM2    0xC0
#define TM1637_I2C_COMM3    0x80

#define PIN_CLK PIN_B1
#define PIN_DIO PIN_B2

uint8_t digitToSegment[] = {
 // XGFEDCBA
  0b00111111,    // 0
  0b00000110,    // 1
  0b01011011,    // 2
  0b01001111,    // 3
  0b01100110,    // 4
  0b01101101,    // 5
  0b01111101,    // 6
  0b00000111,    // 7
  0b01111111,    // 8
  0b01101111,    // 9
  0b01110111,    // A
  0b01111100,    // b
  0b00111001,    // C
  0b01011110,    // d
  0b01111001,    // E
  0b01110001     // F
};

uint8_t m_brightness; 

void initDisplay();
void setBrightness(uint8_t brightness, int on);
void start();
void stop();
void bitDelay();
int writeByte(uint8_t b);
uint8_t encodeDigit(uint8_t digit);
void setSegments(uint8_t segments[], uint8_t length, uint8_t pos);
void showNumberDecEx(int num, uint8_t dots, int leading_zero, uint8_t length, uint8_t pos);
void showNumberDec(int num, int leading_zero, uint8_t length, uint8_t pos);

void main()
{
   initDisplay();
   setBrightness(7, 1);
   setSegments(digitToSegment[2], 4, 0);
   while(TRUE)
   {
   }

}

void initDisplay() {
   output_high(PIN_CLK);
   output_high(PIN_DIO);
   output_low(PIN_CLK);
   output_low(PIN_DIO);
}

void setBrightness(uint8_t brightness, int on) {
   m_brightness = (brightness & 0x7) | (on? 0x08 : 0x00);
}

void start() {
   output_low(PIN_DIO);
   bitDelay();
}

void stop() {
   output_low(PIN_DIO);
   bitDelay();
   output_high(PIN_CLK);
   bitDelay();
   output_high(PIN_DIO);
   bitDelay();
}

void bitDelay() {
   delay_us(100);
}

int writeByte(uint8_t b) {
   uint8_t data = b;
   uint8_t mpinclk = PIN_CLK;
   uint8_t mpindio = PIN_DIO;
   for (uint8_t i = 0; i < 8; i++) {
      output_low(PIN_CLK);
      bitDelay();
      
      if (data & 0x01) {
         output_high(mpindio);
      } else {
         output_low(mpindio);
      }
      
      bitDelay();
      
      output_high(mpinclk);
      bitDelay();
      
      data = data >> 1;
   }
   
   output_low(mpinclk);
   output_high(mpindio);
   bitDelay();
   
   output_high(mpinclk);
   bitDelay();
   
   int ack = input(mpindio);
   if (ack == 0)
      output_low(mpindio);
   
   bitDelay();
   output_low(mpinclk);
   bitDelay();
   
   return ack;
}

uint8_t encodeDigit(uint8_t digit) {
   return digitToSegment[digit & 0x0f];
}

void setSegments(uint8_t segments[], uint8_t length, uint8_t pos) {
   start();
   writeByte(TM1637_I2C_COMM1);
   stop();

   // Write COMM2 + first digit address
   start();
   writeByte(TM1637_I2C_COMM2 + (pos & 0x03));

   // Write the data bytes
   for (uint8_t k=0; k < length; k++)
     writeByte(segments[k]);

   stop();

   // Write COMM3 + brightness
   start();
   writeByte(TM1637_I2C_COMM3 + (m_brightness & 0x0f));
   stop();
}

