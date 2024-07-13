#include "defs.h"

void viewEscape(char*);

/* CLIENT FUNCTION: */
/* top-level function for client process, given server IP address; */
/* sends connection request to server at given IP address, loops and
   waits for data that it prints out, until quit message is received */
void viewEscape(char* c){
   int mySocket;
   char buffer[MAX_BUFF];

   setupClientSocket(&mySocket, "127.0.0.1");

  while (1) {
   rcvData(mySocket, buffer);

   printf("%s\n", buffer);
      if(strcmp(buffer,"quit") == 0)
      break;
  }
}