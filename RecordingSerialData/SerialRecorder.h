#ifndef _SERIAL_RECORDER_
#define _SERIAL_RECORDER_

#include "Arduino.h"

//Variable definitios
#define BUFFER_NUM_CHARS 57 // 1(Command family char)+5(CommandNumber int)+1(nparams int)+5x8(params int)+10 (sep characters)
#define BUFFER_NUM_PARAMS 8
#define CORRUPT_COMMAND 0

//Library definitios
void SerialRecorderInit(int);
void recvWithEndMarker( char,char );

void showNewData( void );
bool RecieveBufferIsFull( void );
void resetBuffer(void);

bool CommadInterpreter(void);
char GetCommandFamily( void );
int GetCommandNum( void );
int GetCommandParams( byte );
int GetParamsQty( void );

#endif // _SERIAL_RECORDER_
