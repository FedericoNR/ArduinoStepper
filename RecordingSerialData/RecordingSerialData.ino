
#include "SerialRecorder.h"
const int analogInPin = A0;
int sensorValue = 0;        

void setup() {
  SerialRecorderInit(9600);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  //Recieve incomming stream with <,> as start and end of frame
  recvWithEndMarker('<','>');

  //If a mesage was recieved in the buffer
  if( RecieveBufferIsFull() ){
    if( CommadInterpreter() ){ //Decode command and verifies if it is correctly recieved
      CommandSelector( GetCommandFamily() , GetCommandNum() );
    }
    else{
      //Command does not meet command format
      Serial.println("Invalid command format");
    }
  resetBuffer();
  }
}
  
//-------------------------------------------------------------

 void CommandSelector( char CommandFmly, int CommandNum  ){  
  /*
  //Debug
  Serial.print("Code family:"); 
  Serial.print(CommandFmly);  
  Serial.print(" Code num:");
  Serial.println(CommandNum);
  */
  
  switch(CommandFmly){
    case 'A':
      AcommandFamilySelector( CommandNum  );
      break;
    /*
    case 'B':
      BcommandFamilySelector( CommandNum  );
      break;
    .
    .
    .
    */
    default:
      Serial.println("Command family not implemented");
      break;
    }
}

//------------------------------------------------------------- 
 void AcommandFamilySelector(byte CommandNum){
  switch(CommandNum){
    case 100:
      A_Action_100(GetParamsQty());
      break;
    case 101:
      A_Action_101(GetParamsQty());
      break;
    case 102:
      A_Action_102(GetParamsQty());
      break;
    /*
    case 1:
      A_Action_1();
      break;
    .
    .
    .
    */
    default:
      Serial.println("Command number not implemented");
      break;
    }
 }

//-------------------------------------------------------------
void A_Action_100( int n ){
  /*
  Simple poorly implemented echo function. Used mainly for command sender debug.
  
  <A;100;n;Y1;...;Yn> makes the arduino to return the n values over serial port.
  */
  int param[n];
  for(int i=0;i<=(n-1);i++){
    param[i]=GetCommandParams(i);
    Serial.print("Parameter:");
    Serial.print(i+1);
    Serial.print(" Value:");
    Serial.println(param[i]);
  }
  Serial.println("A100;OK");
}

//-------------------------------------------------------------
void A_Action_101( int n ){
  /*
  Simple poorly implemented blink action. Used mainly for command sender debug.
  
  <A;101;2;X;Y> makes the builtin led to blink X times spaced by delay(Y) time
  */
  int param[n];
  //param[0] is number of blinks
  //param[1] is miliseconds per blink
  
  for( int i=0; i<=(n-1) ; i++ ){
    param[i]=GetCommandParams(i);
  }
  for( int i=0 ; i<=(param[0]) ; i++ ){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(param[1]);
    digitalWrite(LED_BUILTIN, LOW);
    delay(param[1]);
  }
  Serial.println("A101;OK");
}

//-------------------------------------------------------------
void A_Action_102( int n ){
    /*
  Simple poorly implemented action. Used mainly for command sender debug.
  
  <A;102;2;X;Y> makes arduino to get analog 0 pin valueby delay(Y) time and send it over serial port
  */
  int param[n];
  for(int i=0;i<=(n-1);i++){
    param[i]=GetCommandParams(i);
  }
  for(int i=0;i<=(param[0]);i++){
    sensorValue = analogRead(analogInPin);
    Serial.print("pin A0:");
    Serial.println(sensorValue);
    delay(param[1]);
  }
  Serial.println("A102;OK");
}
