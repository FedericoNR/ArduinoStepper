/*********************************************************************************************************/
//https://www.youtube.com/watch?v=x7knaKxkpCM
#include <avr/io.h>
#include <avr/interrupt.h>

/*La libreria se encuentra en el directrio:
     C:\Program Files (x86)\Arduino\hardware\tools\avr\avr\include\avr
       |
       +-->    io.h (Llama a cada libreria para compatibilidad)
       |          |
       |          +--> iom8.h (para ATMEGA8)
       |
       +-->    interrupt.h
**En la primera libreria se ecuentran todos los registros que hay definidos para el ATMEGA8
**En la segunda libreria se encuentran definiciones para manejar las interrupciones
*/
/*********************************************************************************************************/


//Variables and functions allocations goes here....




void setup(){
/**************************************** TIMER *********************************************************/
cli(); //Desabilitar interrupciones globales mientras configuramos el timer
TCCR1A=0x00;  //Ver Pagina 96 del datasheet.
TCCR1B=0x00;  //Ver Pagina 98 del datasheet.
TIMSK  |=(1<<TOIE1); //HABILITO INTERRUPCION DEL TIMER. Ver pagina 72 del datasheet y definicion de mascaras en la libreria.
TCCR1B |= (1<<CS10); //SELECCIONO PRESCALER. Ver pagina 98 del datasheet y definicion de mascaras en la libreria.
//TCCR1B |= (1<<CS11);
//TCCR1B |= (1<<CS12);
OCR1A = 1000 ;          //REGISTRO DE COMPARACION DEL TIMER, para comparacion para el overflow. Ver pagina 99 del datasheet.
TCCR1B |= ( 1<<WGM12 ); //HABILITO MODULO DE COMPARACION EN EL TIMER. Ver pagina 97 del datasheet
sei();  //Habliltar interrupciones globales
/********************************************************************************************************/
//Variable linitializations and programm inizialization goes here....

}

void loop(){
//Infinite loop goes here...

}




/**************************************** RTI ***********************************************************/
ISR(TIMER1_CMPA_vect){
// ISR codes goes here

}
/********************************************************************************************************/