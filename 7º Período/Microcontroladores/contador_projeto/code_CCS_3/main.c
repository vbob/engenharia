#include <main.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define TM1637_I2C_COMM1    0x40
#define TM1637_I2C_COMM2    0xC0
#define TM1637_I2C_COMM3    0x80

uint8_t digitToSegment[] = {
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

#define pinClk PIN_B0
#define pinDIO PIN_B1
void initDisplay();
void bitDelay();
void setSegments(uint8_t segments[], uint8_t length, uint8_t pos);
int writeByte(uint8_t b);
void stop();
void start();

void main()
{
  start();
   writeByte(TM1637_I2C_COMM1);
   stop();
   
   start();
   writeByte(0b00111001);

   stop();
   
   start();
   writeByte(TM1637_I2C_COMM3 + (0x7 & 0x0f));
   stop();
   while(TRUE)
   {
      //TODO: User Code
   }

}

void start()
{
 output_low(pinDIO);
  bitDelay();
}

void stop() {
 output_low(pinDIO);
   bitDelay();
    output_high(pinDIO);
   bitDelay();
    output_high(pinDIO);
   bitDelay();
}

void bitDelay() {
   delay_us(100);
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
   writeByte(TM1637_I2C_COMM3 + (0x7 & 0x0f));
   stop();
}

int writeByte(uint8_t b)
{
  uint8_t data = b;

  // 8 Data Bits
  for(uint8_t i = 0; i < 8; i++) {
    // CLK low
    output_low(pinDIO);
    bitDelay();

   // Set data bit
    if (data & 0x01) {
      output_high(pinDIO);
    }
    else {
      output_low(pinDIO);
    }

    bitDelay();

   // CLK high
    output_high(pinClk);
    bitDelay();
    data = data >> 1;
  }

  // Wait for acknowledge
  // CLK to zero
  output_low(pinClk);
   output_high(pinDIO);
  bitDelay();

  // CLK to high
  output_high(pinClk);
  bitDelay();
  uint8_t ack = input(pinDIO);
  if (ack == 0)
    output_low(pinDIO);


  bitDelay();
  output_low(pinClk);
  bitDelay();

  return ack;
}
