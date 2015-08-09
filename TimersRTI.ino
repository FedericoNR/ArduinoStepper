/*********************************************************************************************************/
https://www.youtube.com/watch?v=x7knaKxkpCM
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
TIMSK  |=(1<<TOIE1); //Ver pagina 72 del datasheet y definicion de mascaras en la libreria.
TCCR1B |= (1<<CS10); //Ver pagina 98 del datasheet y definicion de mascaras en la libreria.
sei();  //Habliltar interrupciones globales
/********************************************************************************************************/


//Variable linitializations goes here....

}

void loop(){
//Infinite loop goes here...
}




/**************************************** RTI ***********************************************************/
ISR(TIMER1_OVF_vect){
// ISR codes goes here

}
/********************************************************************************************************/