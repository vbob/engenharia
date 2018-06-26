#include <16F877A.h>
#device ADC=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=16000000)
<<<<<<< HEAD
#use rs232(baud=1200,PARITY=E,UART1,stream=PORT1)
=======
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)
>>>>>>> 04dffb53f90e0b796bf1103439ba618814b1ef72


void main()
{
   setup_adc_ports(AN0_AN1_AN3);
   setup_adc(ADC_CLOCK_DIV_32);
   
   unsigned long value = 0;
   
   while(TRUE)
   {
      set_adc_channel(0);
      delay_ms(1);
      value=read_adc();
<<<<<<< HEAD
      fprintf(PORT1, "%Lu A \n\r", value);
      delay_ms(1);

      set_adc_channel(1);
      delay_ms(1);
      value=read_adc();
      fprintf(PORT1, "%Lu B \n\r", value);
      delay_ms(1);
=======
      putc(value);
      delay_ms(1000);
      
      set_adc_channel(1);
      delay_ms(1);
      value=read_adc();
      putc(value);
      delay_ms(1000);
>>>>>>> 04dffb53f90e0b796bf1103439ba618814b1ef72
   }
}
