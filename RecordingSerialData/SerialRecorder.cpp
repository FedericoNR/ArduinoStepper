/*
Get incomming serial data from the serial port and basic method to recieve 
commands and parameters through it



Main functionalities taken from:
https://forum.arduino.cc/index.php?topic=288234.0


*/

#include "SerialRecorder.h"
#include "Arduino.h"


//Variable declarations and initialization
char receivedChars[BUFFER_NUM_CHARS];    // an array to store the received data
char foo[BUFFER_NUM_CHARS];
int  recievedParams[BUFFER_NUM_PARAMS];
char commandFamily;
int  commandNum;
int  nparams;

boolean newData = false;
boolean BufferOvflFlag=false;

//---------------------------------------------
void SerialRecorderInit(int BaudRate ){
 /*
 Initialization function
 */
 Serial.begin(BaudRate);
 Serial.println("Arduino connected");
}

//---------------------------------------------
void recvWithEndMarker( char startMarker, char endMarker ) { 
 /*
 function to poll data from the serial port. 

 Records incoming characters in receivedChars. The max beffer length is given by BUFFER_NUM_CHARS.
 If the buffer Overflows, last incomming data is stored in the last character and BufferOvflFlag is set.
 Data is only stored in the buffer if it is sent between satartMarker and endMarker characters. All other 
 data is neglected
 */
 static boolean recieveInProgress = false;
 static byte ndx = 0;
 char rc;

 while (Serial.available() > 0 && newData == false) {
   rc = Serial.read();            //Get data from serial buffer
   if( recieveInProgress == true ){ //If a new character is being expected
     if (rc != endMarker) {         //Check if end marker was sent
      receivedChars[ndx] = rc;      //Add char to buffer
      ndx++;                        //Increase index
      if (ndx >= BUFFER_NUM_CHARS ) {
        BufferOvflFlag=true;              //If buffer overflows, set Ovfl flag
        ndx = BUFFER_NUM_CHARS - 1;       //Decrease index (last character will be overlapped)
      }
     }
     else { //If endcharacter was recieved
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;                   // reset index
      newData = true;            // Set newData flag so the user can acces data
      recieveInProgress=false;   // Dont reload buffer untill usert states so
     }
   }
   else if( rc == startMarker ){
    recieveInProgress = true; //If a starter mark is recieved, start loading the buffer
   }
 }
}
//------------------------------------
bool RecieveBufferIsFull( void ){
  return(newData); 
}
//------------------------------------
void resetBuffer(void){
  BufferOvflFlag=false;
  newData = false; 
}
//------------------------------------
void showNewData() {
  /*
  Simple debug print funtion
  */
 if (newData == true) {
 if(BufferOvflFlag){
  Serial.println("Warning, buffer ovf"); 
 }
 Serial.print("Recieved ... ");
 Serial.println(receivedChars);
 newData = false;
 BufferOvflFlag= false;
 }
}

//------------------------------------
/*
Command structure
suppose that '<' , '>'  are used as startMarker, endMarker.

 
Command frame: '<A;XXX;n;param1;param2;...;paramn>'   (n=<8)
    A: is a char that identifies the command family
      XXX: is an int that identifies the command family num
        n: is an int with the total number of parameters present in the command
          paramn: is a specific parameter (unsigned int for the moment)

    ie: <M;003;3;122;1655;598>
*/
//------------------------------------
bool CommadInterpreter(  void ){
  char * strtokIndx; // this is used by strtok() as an index
 
  if(BufferOvflFlag== true){
    return(false);
  }
  strtokIndx = strtok(receivedChars,";"); // Get a pointer to the substring tokens     
  strcpy(foo, strtokIndx);                // Copy substring into foo variable
  commandFamily = foo[0];

  strtokIndx = strtok(NULL, ";"); // This continues where the previous call left off
  strcpy(foo, strtokIndx);        // Copy substring into foo variable
  commandNum = atoi(foo);         // convert the next part to an integer

  strtokIndx = strtok(NULL, ";"); // this continues where the previous call left off
  strcpy(foo, strtokIndx);        // Copy substring into foo variable
  nparams = atoi(foo);            // convert the next part to an integer and cast to int

  for(int i=0;i<=(nparams-1);i++){ //nparams is the int that specifies the number of parameters comming, so we expect to break the string and convert nparam times.
    strtokIndx = strtok( NULL , ";" );       // this continues where the previous call left off
    strcpy(foo, strtokIndx);                 // Copy substring into foo variable
    recievedParams[i] = atoi( foo );         // convert the next part to an integer and cast int
    if(i>= 7){ //A number of 7 parameters was chosen 
      return(false);
    }
  }
 return(true);
//True if the command is valid, false otherwise  
}
//------------------------------------
char GetCommandFamily(void){
  return(commandFamily);
}
//------------------------------------
int GetCommandNum(void){
  return(commandNum);
} 
//------------------------------------
int GetParamsQty( void ){
  return(nparams); 
}
//------------------------------------
int GetCommandParams( byte indx ){
  return(recievedParams[indx]); 
}




 
