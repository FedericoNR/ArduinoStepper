#include "StringRecorder.h"

//Member functions and definitions

StrRecord::StrRecord(){
 
}

StrRecord::~StrRecord(void){	
}


void StrRecord::beguin(){
	bufferState=false;
	icommingStr="\0";
	mesgSize=0;
}

void StrRecord::listen(char incomingChar){
	if ((incomingChar == '\n') || (incomingChar == '\r') ){
		bufferState=true;
	}
	else{	//Check if buffer is not full
		mesgSize+=1;
		icommingStr+=incomingChar;
	}

}

bool StrRecord::IsBufferFull(){
	return(bufferState);
}

 String StrRecord::bufferGet(){
    String Output;
	bufferState=false;
	Output =icommingStr;
	icommingStr="\0";
	mesgSize+=1;
	return(Output);
	
}

int StrRecord::getMesgSize(){
		return(mesgSize);
}
