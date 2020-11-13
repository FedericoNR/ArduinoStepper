
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


//Symbol definitions
#ifndef STRING_RECORDER_H
#define STRING_RECORDER_H

//Variables definitions
#define BUFFERSIZE 30


class StrRecord{
	public: 
		//Methods
		
		StrRecord(); //Class constructor declaration
		~StrRecord();//Class destructor declaration
		void beguin();
		bool IsBufferFull();
		void listen(char incomingChar);
		String bufferGet();
		int getMesgSize();
		//Variables
	private:
		//Methods
		
		//Varibles
		String icommingStr;
		int  mesgSize;
		bool bufferState;	
};


#endif