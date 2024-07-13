#include "defs.h"

void spawnFlyer(EscapeType*, char, int, int, int);
void addFlyer(FlyerArrayType*, FlyerType*);
void moveFlyer(FlyerType*, EscapeType*);
int  flyerIsDone(FlyerType*);

/* dynamically allocates and initializes one flyer, and 
   adds it to escape's flyer collection */
void spawnFlyer(EscapeType *hollow, char a, int row, int col, int str){
    FlyerType *tmpFlyer;

    tmpFlyer = malloc(sizeof(FlyerType));
    tmpFlyer->partInfo.avatar = a;
    tmpFlyer->partInfo.pos.row = row;
    tmpFlyer->partInfo.pos.col = col;
    tmpFlyer->strength = str;

    hollow->flyers.elements[hollow->flyers.size] = tmpFlyer;
    hollow->flyers.size++;
}

/* adds flyer to escape's flyer collection */
void addFlyer(FlyerArrayType *arr, FlyerType *flyer){
    arr->elements[arr->size] = flyer;
    arr->size++;
}

/* computes flyer's next move in accordance to instruction 3.4, 
   updates flyer's position, and deals with collisions with heroes */
void moveFlyer(FlyerType *flyer, EscapeType *hollow){
    int randInt;
    int row = flyer->partInfo.pos.row;
    int col = flyer->partInfo.pos.col;
    int closestHero;
    HeroType *hero;

    if (flyer->partInfo.avatar == 'v'){
        row--;
        randInt = randomInt(2);

        if (randInt == 1){
            col += DIR_LEFT;
        }else if (randInt == 2){
            col += DIR_RIGHT;
        }
    }else if (flyer->partInfo.avatar == 'v'){
        randInt = randomInt(7);
        randInt = randInt - 3;
        row -= randInt;

        randInt = randomInt(2);
        randInt++;
        
        computeHeroDir(hollow, flyer, &closestHero);
        if (col > closestHero) randInt = 0-randInt;
        if (col != closestHero) col += randInt;
    }
    setPos(&flyer->partInfo.pos, row, col);


    if (row == -MAX_ROW){
        for (int i=0;i<hollow->heroes.size;i++){
            hero = *hollow->heroes.elements+i;
            if (hero->partInfo.pos.col == col){
                incurDamage(hollow->heroes.elements[i], flyer);
            }
        }
    }
}

/* determines if a flyer has reached the ground */
int  flyerIsDone(FlyerType *flyer){
    if (flyer->partInfo.pos.row == -MAX_ROW){
        return C_TRUE;
    }
    return C_FALSE;
}