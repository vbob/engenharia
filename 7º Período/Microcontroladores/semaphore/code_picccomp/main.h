#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=20000000)
#use FIXED_IO( D_outputs=PIN_D4,PIN_D3,PIN_D2,PIN_D1,PIN_D0 )



