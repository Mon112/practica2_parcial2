#include <18F4620.h>
#include <stdio.h>
#include <stdlib.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, /*NOMCLR,*/ STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(e)
signed long results=0;
//#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O

#ifdef __DEBUG_SERIAL__
#define TX_232        PIN_C6
#use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1)
#use fast_io(c)
#endif

void main(void) {
   setup_oscillator(OSC_16MHZ);
   set_tris_a(0xc0);
   set_tris_b(0xf0);
   set_tris_c(0x3f);
   set_tris_d(0xff);
   set_tris_e(0x08);
#ifdef __DEBUG_SERIAL__ //Deberiamos de proteger nuestras depuraciones de esta forma o usar una macro ya protegida.
   printf("Hola Mundo\n"); //Puedes usar putc o printf. Revisa la documentación de CCS para ver que mas puedes hacer.
#endif
while (1) {
   if(input(PIN_B4)==0){
      results=(long)input_d()+(long)input_c();
   }
   if(input(PIN_B5)==0){
      results=(long)input_d()-(long)input_c();
   }
   if(input(PIN_B6)==0){
      results=(long)input_d()*(long)input_c();
   }
}
       output_a(results);
       output_b(results>>6);
       output_e(results>>10);
}
   

