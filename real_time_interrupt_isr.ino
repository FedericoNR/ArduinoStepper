// For Interrupts and registers deffinitions.
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>



int N = 10;
int n=0;
int Ledstate=0;

void setup(){
/************************************** Timer configuration ****************************************/ 
  cli(); //Desabilitar interrupciones globales mientras configuramos el timer
  TCCR1A=0x00;  //Ver Pagina 96 del datasheet.
  TCCR1B=0x00;  //Ver Pagina 98 del datasheet.
  TIMSK1  |=(1<<TOIE1); //Ver pagina 72 del datasheet y definicion de mascaras en la libreria.
  TCCR1B |= (1<<CS10); //Ver pagina 98 del datasheet y definicion de mascaras en la libreria.
  sei();  //Habliltar interrupciones globales
/*********************************************************************************************** ***/
  Ledstate=0;
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop(){
  
  



}

void toogleled(void){
 n++;
 if (n>N){
   if(Ledstate==0){
     digitalWrite(LED_BUILTIN, HIGH);
     Ledstate=1;
   }
   else{
     digitalWrite(LED_BUILTIN, LOW);
     Ledstate=0;
   }
   n=0;  
 }
}

/************************************** Real Time Interrupt ****************************************/
ISR(TIMER1_OVF_vect){
  //Code for ISR 's goes here
  toogleled();
}
/************************************** Real Time Interrupt ****************************************/
