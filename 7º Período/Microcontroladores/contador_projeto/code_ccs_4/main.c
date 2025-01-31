#include <main.h>

#include <float.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

uint8_t digitToSegment[] = {
  // XGFEDCBA
  0b00111111, // 0 0x3f
  0b00000110, // 1 0x06
  0b01011011, // 2 0x5b
  0b01001111, // 3 0x4f
  0b01100110, // 4 0x66
  0b01101101, // 5 0x6d
  0b01111101, // 6 0x7d
  0b00000111, // 7 0x07
  0b01111111, // 8 0x7f
  0b01101111, // 9 0x6f
  0b01110111, // A 0x77
  0b01111100, // b 0x7c
  0b00111001, // C 0x39
  0b01011110, // d 0x5e
  0b01111001, // E 0x79
  0b01110001 // F 0x71
};

#define ADDR_AUTO 0x40 // 0b01000000
#define STARTADDR 0xc0 // 0b11000000
#define BRIGHTADD 0x80 // 0b10000000

#define pinClk PIN_B2
#define pinDIO PIN_B3
#define pinAdd PIN_B5
#define pinRst PIN_B4

void start();
void bitDelay();
void writeBit(uint8_t value);
uint8_t readAck();
uint8_t writeByte(uint8_t value);
void stop();
uint8_t encodeDigit(uint8_t digit);
void setSegments(uint8_t segments[], uint8_t length, uint8_t pos);
void writeDigits(uint32_t value);

uint16_t counter = 0;

void main()
{
   port_B_pullups(0xFF);
   uint8_t data[] = {
      0b00111111,
      0b00111111,
      0b00111111,
      0b00111111
   };
   
   setSegments(data, 4, 0);
   
   while(TRUE)
   {
      if (input(pinAdd) == 0) {
         counter++;
         writeDigits(counter);
         while(input(pinAdd) == 0);
      }
      
      if (input(pinRst) == 0) {
         counter = 0;
         writeDigits(counter);
         while(input(pinRst) == 0);
      }
   }
}

void writeDigits(uint32_t value) {
   int units = value%10;
   int tenths = ((value-units)%100)/10;
   int thousands = value/1000;
   int hundreds = (value/100) - (thousands*10);  
   
   
    uint8_t data[] = {
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000
   };
   
   data[0] = digitToSegment[thousands];

   data[1] = digitToSegment[hundreds];
   data[2] =  digitToSegment[tenths];
   data[3] = digitToSegment[units];
   setSegments(data, 4, 0);
}

void setSegments(uint8_t segments[], uint8_t length, uint8_t pos) {
   start();
   writeByte(ADDR_AUTO);
   stop();

   // Write COMM2 + first digit address
   start();
   writeByte(STARTADDR + (pos & 0x03));

   // Write the data bytes
   for (uint8_t k=0; k < length; k++)
     writeByte(segments[k]);

   stop();

   // Write COMM3 + brightness
   start();
   writeByte(0b10001111);
   stop();
}

void start() {
   output_low(pinDIO);
   bitDelay();
}

void bitDelay() {
   delay_us(100);
}

void writeBit(uint8_t value) {
   output_low(pinClk);
   
   if (value) {
      output_high(pinDIO);
   } else {
      output_low(pinDIO);
   }
   
   bitDelay();
   output_high(pinClk);
   bitDelay();
}

uint8_t readAck() {
   output_low(pinClk);
   uint8_t readPro = input(pinDIO);
   
   output_high(pinClk);
   bitDelay();
   output_low(pinClk);
   
   return readPro;
}

uint8_t writeByte(uint8_t value) {
   uint8_t b = value;
   
   for (uint8_t i = 0; i< 8; i++) {
      writeBit(b & 0x01);
      b = b >> 1;
   }
   
   return readAck();
}

void stop() {
   output_low(pinDIO);
   bitDelay();
   output_high(pinClk);
   bitDelay();
   output_high(pinDIO);
   bitDelay();
}

uint8_t encodeDigit(uint8_t digit)
{
   return digitToSegment[digit & 0x0f];
}
