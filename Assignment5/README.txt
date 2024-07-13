
Cedric Nonez
101268510
Assignment 5 submission


Program purpose:

Included files:

main.c 
connect.c 
spectator.c 
view.c 
flyer.c 
escape.c 
hero.c
makefile

Instructions:

To compile files, use the following instruction:

make a5

to run files:

./a5

All functions used in my submission:

hero.c

void initHero(HeroType**, char, int, char*);
void addHero(HeroArrayType*, HeroType*);
void moveHero(HeroType*, EscapeType*);
int heroIsSafe(HeroType*);
void incurDamage(HeroType*, FlyerType*);
void computeHeroDir(EscapeType*, FlyerType*, int*);

flyer.c

void spawnFlyer(EscapeType*, char, int, int, int);
void addFlyer(FlyerArrayType*, FlyerType*);
void moveFlyer(FlyerType*, EscapeType*);
int  flyerIsDone(FlyerType*);

escape.c

void runEscape();
int escapeIsOver(EscapeType*);
void initEscape(EscapeType*);
void handleEscapeResult(EscapeType*);
void cleanupEscape(EscapeType*);

view.c

void outputHollow(EscapeType*);
void initHollow(EscapeType*, char[][MAX_COL]);
void serializeHollow(EscapeType*, char*);
void setPos(PositionType*, int, int);

spectator.c

void viewEscape(char*);

main.c

int main(int argc, char *argv[])
int randomInt(int max)


