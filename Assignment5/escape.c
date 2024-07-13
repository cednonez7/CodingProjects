#include "defs.h"

void runEscape();
int escapeIsOver(EscapeType*);
void initEscape(EscapeType*);
void handleEscapeResult(EscapeType*);
void cleanupEscape(EscapeType*);

/* top-level function for server process; */
/* initializes the escape, contains game loop, handles escape result, cleans up */
void runEscape(){
    EscapeType hollow;
    volatile int gameloop = C_TRUE;
    int randInt;
    int str;
    HeroType hero;

    initEscape(&hollow);

    while (gameloop == C_TRUE){

        randInt = randomInt(10); // bird spawn rate
        str = randomInt(3) + 3;
        if (randInt > 2){ 
            spawnFlyer(&hollow, 'v', randomInt(5), randomInt(MAX_COL), str);
        }

        randInt = randomInt(10); // monkey spawn rate
        str = randomInt(4) + 8;
        if (randInt > 4){ 
            spawnFlyer(&hollow, '@', randomInt(15), randomInt(MAX_COL), str);
        }

        for (int i=0;i<hollow.flyers.size;i++){
            if (hollow.flyers.elements[i]->partInfo.pos.row == -MAX_ROW){
                hollow.flyers.elements[i]->partInfo.avatar = ' ';
                continue;
            }
            moveFlyer(hollow.flyers.elements[i], &hollow);
        }
        for (int i=0;i<hollow.heroes.size;i++){
            hero = *hollow.heroes.elements[i];
            if (hero.dead || hero.partInfo.pos.col == MAX_COL) continue;
            moveHero(hollow.heroes.elements[i], &hollow);
        }

        if (escapeIsOver(&hollow) == C_TRUE)
            gameloop = C_FALSE;
    }
    handleEscapeResult(&hollow);
    cleanupEscape(&hollow);
}

/* determines if both heroes are dead or have escaped */
int escapeIsOver(EscapeType *hollow){
    int escaped = 0;
    int dead = 0;
    HeroType *hero;

    for (int i=0;i<hollow->heroes.size;i++){
        hero = *hollow->heroes.elements + i;
        if (heroIsSafe(hero) == C_TRUE){
            escaped++;
        }else if (hero->dead == C_TRUE){
            dead++;
        }
    }
    if (escaped + dead == hollow->heroes.size) return C_TRUE;
    return C_FALSE;
}

/* initializes escape, including seeding PRNG, initializing the hero and flyer arrays,
   allocating and initializing both heroes and adding them to the heroes array, 
   initializing sockets and blocking until client connection request is received */
void initEscape(EscapeType *hollow){
    
    HeroArrayType  *heroArr;

    HeroType *Timmy;
    HeroType *Harold;

    int myListenSocket, clientSocket;

    srand((unsigned)time( NULL));

    heroArr = calloc(MAX_ARR, sizeof(HeroType*));
    hollow->heroes = *heroArr;
    hollow->heroes.size = 0;

    hollow->flyers.size = 0;
    
    int tim = randomInt(5);
    int har = randomInt(5);
    while (har == tim){
        har = randomInt(5);
    }

    initHero(&Timmy, 'T', tim, "Timmy");
    initHero(&Harold, 'H', har, "Harold");

    hollow->heroes.elements[0] = Timmy;
    hollow->heroes.elements[1] = Harold;

    hollow->listenSocket = myListenSocket;
    hollow->viewSocket = clientSocket;

    setupServerSocket(&myListenSocket);
    acceptConnection(myListenSocket, &clientSocket);
}

/* prints out and sends to client the outcome of the escape */
void handleEscapeResult(EscapeType *hollow){
    char *buffer[MAX_BUFF];
    
    for (int i=0;i<hollow->heroes.size;i++){
        if (hollow->heroes.elements[i]->partInfo.pos.col == MAX_COL){
            printf("%6s ESCAPED!!!", hollow->heroes.elements[i]->name);

            strcat(*buffer, hollow->heroes.elements[i]->name);
            strcat(*buffer, "ESCAPED!!!");

        }else if (hollow->heroes.elements[i]->dead == C_TRUE){
            printf("%6s IS DEAD...", hollow->heroes.elements[i]->name);

            strcat(*buffer, hollow->heroes.elements[i]->name);
            strcat(*buffer, "IS DEAD...");
        }
    }
    sendData(hollow->viewSocket, *buffer);
}

/* cleans up escape, including deallocating required memory, sending termination
   (quit) message to client, and closing sockets */
void cleanupEscape(EscapeType *hollow){
    char *buffer[10];
    
    for (int i=0;i<hollow->flyers.size;i++){
        free(hollow->flyers.elements[i]);
    }
    for (int i=0;i<hollow->heroes.size;i++){
        free(hollow->heroes.elements + i);
    }
    free(hollow->heroes.elements);

    strcpy(*buffer, "quit");
    sendData(hollow->viewSocket, *buffer);

  close(hollow->listenSocket);
  close(hollow->viewSocket);
}