
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char InputCode[22]="A;100;3;1256;1258;154";
char foo[20];
char CodeFamily;
int CodeNum;
char n;
int parameters[10];
char *strtokIndx; 

int main(){

    printf ("String \"%s\" \n",InputCode);
    
	strtokIndx = strtok(InputCode,";");      
    strcpy(foo, strtokIndx);    
    CodeFamily = foo[0];
    printf ("Code family \"%s\":\n",foo);
    
    strtokIndx = strtok(NULL,";");      
    strcpy(foo, strtokIndx);                 
    CodeNum = atoi(foo);
    printf ("Codenum obtainded \"%u\":\n",CodeNum);
    
    strtokIndx = strtok(NULL,";");      
    strcpy(foo, strtokIndx);                 
    n = atoi(foo);
    
    for( char i=0 ; i<=(n-1) ; i++ ){
        strtokIndx = strtok(NULL,";");      
        strcpy(foo, strtokIndx);                 
        parameters[i] = atoi(foo); 
        printf ("Parameter \"%u\" is \"%u\":\n",i,parameters[i]);
    }
    
    return(0);
    
}