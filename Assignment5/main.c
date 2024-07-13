#include "defs.h"

int main(int argc, char *argv[])
{
   if (argc == 0){ // server process
      runEscape();
   }else if (argc > 0) // client process
      viewEscape(*argv);
   return(0);
}

int randomInt(int max)
{
   return(rand() % max);
}
