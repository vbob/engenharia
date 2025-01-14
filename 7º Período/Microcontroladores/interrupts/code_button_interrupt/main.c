#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES BROWNOUT

#use delay(crystal=20000000)
#use FIXED_IO( D_outputs=PIN_D1 )

#INT_EXT
void  EXT_isr(void) 
{
 output_toggle(PIN_D1);
}

void main()
{
   enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);

   ext_int_edge(L_TO_H); 

   while(TRUE)
   {
   }
}
