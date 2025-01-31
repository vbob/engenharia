#include <16F877A.h>
#device ADC=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=16000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)


void main()
{
   long value;
      
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_32); 
   set_adc_channel(0);
   delay_ms(10);
   
   while(TRUE)
   {
      value=read_adc();
      fprintf(PORT1, "%Lu\n", value);
      delay_ms(1000);
   }

}
