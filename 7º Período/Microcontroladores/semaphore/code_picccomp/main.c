#include <main.h>

// This program controls two semaphores:
// S1 -> Semaphore 1 (Cars)
// S2 -> Semaphore 2 (Pedestrians)

// When the pedestrian button is pressed, S1 closes and S2 opens

// PINOUT DEFINITION
#define PEDESTRIAN_BUTTON   PIN_B0
#define S1_RED   PIN_D0
#define S1_YELLOW   PIN_D1
#define S1_GREEN   PIN_D2
#define S2_RED   PIN_D3
#define S2_GREEN   PIN_D4

// CYCLE DEFINITION
#define S2_TIME 5000
#define ATTENTION_TIME 1000
#define BLINK_NUMBER 4

// GLOBAL VARIABLES
int S1_STOP = 0;
int COUNTER = 0;
int CYCLE_COUNTER = 0;

// SIGNATURES
void loop();
void checkPedestrianButton();

// PROGRAM START
void main()
{
   // INITIAL STATE
   output_low(S1_RED);
   output_low(S1_YELLOW);
   output_high(S1_GREEN);
   
   output_high(S2_RED);
   output_low(S2_GREEN);

   // OPERATION
   while(TRUE) {      
      loop();
   }
}

void loop() {
   checkPedestrianButton();
   
   if (S1_STOP) {
      // S1 GREEN -> YELLOW
      Delay_ms(ATTENTION_TIME);
      output_low(S1_GREEN);
      output_high(S1_YELLOW);   
      
      // S1 YELLOW -> RED
      Delay_ms(ATTENTION_TIME);
      output_low(S1_YELLOW);
      output_high(S1_RED); 
      
      // S2 RED -> GREEN
      Delay_ms(ATTENTION_TIME);
      output_low(S2_RED);
      output_high(S2_GREEN); 
       
      Delay_ms(S2_TIME);
      
      // BLINK S2 RED
      output_low(S2_GREEN);
       for (COUNTER = 0; COUNTER < BLINK_NUMBER; COUNTER++) {
            output_high(S2_RED);
            Delay_ms(ATTENTION_TIME/2);
            output_low(S2_RED);
            Delay_ms(ATTENTION_TIME/2);
       }
       
      output_high(S2_RED);
      
      // S1 RED -> GREEN
      Delay_ms(ATTENTION_TIME);
      output_low(S1_RED);
      output_high(S1_GREEN); 
      
      S1_STOP = 0;
      CYCLE_COUNTER = 0;
   }
   
   CYCLE_COUNTER++;
}

void checkPedestrianButton() {
     if (input_state(PEDESTRIAN_BUTTON) == 1)
        S1_STOP = 1;
}
