// For Interrupts and registers deffinitions.
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>


#define ISR1_FREC  10
int isr1_counter = 0;

bool ledstate = false ;

void setup(){
  /************************************** Timer configuration ****************************************/ 
  cli(); //Desabilitar interrupciones globales mientras configuramos el timer
  TCCR1A=0x00;  //Ver Pagina 96 del datasheet.
  TCCR1B=0x00;  //Ver Pagina 98 del datasheet.
  TIMSK1  |=(1<<TOIE1); //Ver pagina 72 del datasheet y definicion de mascaras en la libreria.
  TCCR1B |= (1<<CS10); //Ver pagina 98 del datasheet y definicion de mascaras en la libreria.
  sei();  //Habliltar interrupciones globales
/***************************************************************************************************/
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
// Loop code goes here.

  //Nothing in the main loop yet.  
}

/************************************** Sample fnc ****************************************/

void ToogleBuiltinLed(void){
//Toogles builtin Led
  digitalWrite( LED_BUILTIN,  ledstate );
  ledstate = ~ledstate;
}

/************************************** Real Time Service 1 ****************************************/
void Isr1(void){
//Simple ISR. ISR routines running on the periodic iterrupt routine must always 
//be void fnc.
// This example toogles the builtin every ISR1_FREC times  
 isr1Counter++;
 if ( isr1Counter > ISR1_FREC ){
   ToogleBuiltinLed();
   isr1Counter=0;  
 }
}

/************************************** Real Time Interrupt ****************************************/
ISR(TIMER1_OVF_vect){
  //Code for ISR 's goes here
  Isr1();
}
/************************************** Real Time Interrupt ****************************************/
