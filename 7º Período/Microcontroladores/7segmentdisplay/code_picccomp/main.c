// This program writes a number on a 7 segment display

#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES BROWNOUT

#use delay(crystal=20000000)

#use FIXED_IO(B_outputs=PIN_B3,PIN_B4)
#use FIXED_IO(C_outputs=PIN_C0,PIN_C1,PIN_C2)
#use FIXED_IO(D_outputs=PIN_D7,PIN_D4,PIN_D2)


#define LED_A_PORT PIN_B3
#define LED_B_PORT PIN_B4
#define LED_C_PORT PIN_C0
#define LED_D_PORT PIN_C1
#define LED_E_PORT PIN_C2
#define LED_F_PORT PIN_D2
#define LED_G_PORT PIN_D4
#define LED_H_PORT PIN_D7

#define BUTTON PIN_B0

// Number to Led Map
// On format ABCDEFGH
unsigned char led_map [] = {
   0b11111100, // 0
   0b01100000, // 1
   0b11011010, // 2
   0b11110010, // 3 
   0b01100110, // 4
   0b10110110, // 5
   0b10111110, // 6
   0b11100000, // 7
   0b11111110, // 8
   0b11110110, // 9
   0b11101110, // A
   0b00111110, // b
   0b10011100, // C
   0b01111010, // d
   0b10011110, // E
   0b10001110  // F
};

// Pins Map
unsigned char pins[] = {LED_A_PORT,
                        LED_B_PORT,
                        LED_C_PORT,
                        LED_D_PORT,
                        LED_E_PORT,
                        LED_F_PORT,
                        LED_G_PORT,
                        LED_H_PORT};
                       
// Turn off all leds
void clear() {
   output_low(LED_A_PORT);
   output_low(LED_B_PORT);
   output_low(LED_C_PORT);
   output_low(LED_D_PORT);
   output_low(LED_E_PORT);
   output_low(LED_F_PORT);
   output_low(LED_G_PORT);
   output_low(LED_H_PORT);
}

void writeOnDisplay(int number) {
   unsigned char leds = led_map[number];
   clear();
   for (int i =0; i < 8; i++) {
      // Moves the map one bit to the right and compares to 1
      if ((leds >> i) & 0x01)
         output_high(pins[7-i]);
   }
}

// Global vars
int now_number = 1;
int incrementing = 1;

void loop() {   
   if (input_state(BUTTON) == 1) {

      writeOnDisplay(now_number);
      if (incrementing) {
         now_number++;
         if (now_number == 15)
            incrementing = 0;
      } else if (!incrementing) {
         now_number--;
         if (now_number == 0)
            incrementing = 1;
      }
      // If not have delay, it may increment 
      // more than 1 time at each press
      delay_ms(50);
   }
}

void main() {
   clear();
   writeOnDisplay(0);
   while(TRUE)
   {
      loop();
   }
}




