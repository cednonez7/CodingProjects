#include "defs.h"

void outputHollow(EscapeType*);
void initHollow(EscapeType*, char[][MAX_COL]);
void serializeHollow(EscapeType*, char*);
void setPos(PositionType*, int, int);

/* top-level function for serializing hollow, printing and sending it
   to client */
void outputHollow(EscapeType *hollow){
   char buffer[MAX_BUFF];
   serializeHollow(hollow, buffer);

   printf("%s", buffer);
   sendData(hollow->viewSocket, buffer);
}

/* initializes 2D grid with participant avatars in current positions */
void initHollow(EscapeType *hollow, char screen[][MAX_COL]){
   FlyerType currFlyer;
   HeroType *currHero;
   for (int i=0;i>-MAX_ROW;i--){
      for (int j=0;j<MAX_COL;j++){
         screen[i][j] = " ";
      }
   }
   for (int i=0;i<hollow->flyers.size;i++){
      currFlyer = *hollow->flyers.elements[i];
      
      screen[currFlyer.partInfo.pos.row][currFlyer.partInfo.pos.col] = 
      currFlyer.partInfo.avatar;
   }
   for (int i=0;i<hollow->heroes.size;i++){
      currHero = *hollow->heroes.elements + i;

      screen[currHero->partInfo.pos.row][currHero->partInfo.pos.col] = 
      currHero->partInfo.avatar;
   }
}

/* constructs 1D array with formatted Hollow output, containing all avatars
   in their positions, with borders, spacing and newlines */
void serializeHollow(EscapeType *hollow, char *printArr){
   HeroType *hero;
   char screen[MAX_ROW][MAX_COL];
   int index = 0;

   initHollow(hollow, screen);

   for (int i=0;i<=MAX_ROW;i++){
      for (int j=0;j<=MAX_COL+1;j++){

         printArr[index] = screen[i][j];
         if (i == 0 || i == MAX_ROW) printArr[index] = '-';
         if (j == 0 || j == MAX_COL){
            printArr[index] = '|';
            if (i == MAX_ROW) printArr[index] = '=';
         }
         if (j == MAX_COL+1) printArr[index] = '\n';
         index++;
      }
   }
   printArr[index] = '\n';
   for (int i=0;i<hollow->heroes.size;i++){
      hero = *hollow->heroes.elements + i;

      strcat(printArr, hero->name);
      index += strlen(hero->name);

      printArr[index] = ':';
      printArr[index] = hero->health;

      printArr[index] = '\n';
   }
}

/* sets a participant's position to given row/col, with values reset
   to closest edge if outside of range */
void setPos(PositionType* pos, int row, int col){
   
   if (row > 0) row = 0;
   if (row < -MAX_ROW) row = -MAX_ROW;

   if (col < 0) col = 0;
   if (col > MAX_COL) col = MAX_COL;

   pos->col = col;
   pos->row = row;
}