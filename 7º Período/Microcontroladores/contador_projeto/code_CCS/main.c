#include <16F628A.h>
#include <stdint.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20000000)

#define TCLK PIN_B0 
#define TDIO PIN_B1

uint8_t m_brightness = 0;

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

void setBrightness(uint8_t brightness, int on) {
   m_brightness = (brightness & 0x7) | (on? 0x08 : 0x00);
}

void bitDelay() {
   delay_us(100);
}

void start() {
   output_low(TDIO);
   bitDelay();
}

void stop() {
   output_low(TDIO);
   bitDelay();
   output_high(TCLK);
   bitDelay();
   output_high(TDIO);
   bitDelay();
}

int writeByte(uint8_t b)
{
  uint8_t data = b;

  // 8 Data Bits
  for(uint8_t i = 0; i < 8; i++) {
    // CLK low
    output_low(TCLK);
    bitDelay();

   // Set data bit
    if (data & 0x01) {
      output_high(TDIO);
    }
    else {
      output_low(TDIO);
    }

    bitDelay();

   // CLK high
    output_high(TCLK);
    bitDelay();
    data = data >> 1;
   }
   
     output_low(TCLK);
  output_high(TDIO);
  bitDelay();

  // CLK to high
  output_high(TCLK);
  bitDelay();
  uint8_t ack = input(TDIO);
  if (ack == 0)
    output_low(TDIO);


  bitDelay();
  output_high(TCLK);
  bitDelay();

  return ack;
}

void setSegments(uint8_t segments[], uint8_t length, uint8_t pos) {
   start();
}

void main()
{

   output_low(TCLK);
   output_low(TDIO);
   
     start();
     writeByte(digitToSegment[3]);
     stop();
     
     start();
     setBrightness(0x7, 1);
     stop();
   
   while(TRUE)
   {
      //TODO: User Code
   }

}
