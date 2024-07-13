#include "defs.h"

void initHero(HeroType**, char, int, char*);
void addHero(HeroArrayType*, HeroType*);
void moveHero(HeroType*, EscapeType*);
int heroIsSafe(HeroType*);
void incurDamage(HeroType*, FlyerType*);
void computeHeroDir(EscapeType*, FlyerType*, int*);

/*
Function:   initHero
   Purpose:   dynamically allocates and initializes one hero
       out:   hero to be allocated
        in:   char of the hero
        in:   col where the hero spawns
        in:   name of the hero
    */
void initHero(HeroType **hero, char a, int col, char *name){
    HeroType *tmpHero;

    tmpHero = malloc(sizeof(HeroType));
    tmpHero->dead = C_FALSE;
    tmpHero->health = MAX_HEALTH;
    strcpy(tmpHero->name,name);
    tmpHero->partInfo.avatar = a;
    setPos(&tmpHero->partInfo.pos, -MAX_ROW, col);

    *hero = tmpHero;    
}

/*
  Function:   addHero
   Purpose:   adds hero to escape's hero collection 
in and out:   the hero collection to be modified
        in:   the hero to be added to the array
    */
void addHero(HeroArrayType *heroArr, HeroType *hero){
    for (int i=0;i<heroArr->size; i++){
        if (heroArr->elements + i == NULL){
            heroArr->elements[i] = hero;
        }
    }
}

/*
  Function:   moveHero
   Purpose:   computes hero's next move in accordance to instruction 3.4, and updates
              hero's position
       out:   the hero  to be moved
        in:   the escape instance that holds all the data from the program 
    */
void moveHero(HeroType *hero, EscapeType *hollow){
    int randInt = randomInt(10);
    int col = hero->partInfo.pos.col;

    if (strcmp(hero->name,"Timmy") == 0){
        if (randInt < 5){ // Fast walk
            col += 2* DIR_RIGHT;
        }else if(randInt > 8){// Slide
            col += DIR_LEFT;
        }else{// Slow walk
            col += DIR_RIGHT;
        }
    }else if (strcmp(hero->name,"Harold") == 0){
        if (randInt < 1){// Big hop
            col += 5* DIR_RIGHT;
        }else if(randInt > 2){// Big slide
            col += 4* DIR_LEFT;
        }else if(randInt > 6){// Small hop
            col += 3* DIR_RIGHT;
        }else if(randInt > 8){// Small slide
            col += 2* DIR_LEFT;
        }
    }
    setPos(&hero->partInfo.pos, hero->partInfo.pos.row, col);
}

/*
  Function:   heroIsSafe
   Purpose:   determines if a hero has successfully escaped the Hollow
        in:   pointer to the hero instance 
    */
int heroIsSafe(HeroType *hero){
    if (hero->partInfo.pos.col == MAX_COL){
        return C_TRUE;
    }
    return C_FALSE;
}

/* decreases hero's health by flyer's strength (if health gets negative, reset to 0);
   if hero dies, its avatar is changed */
/*
  Function:   incurDamage
   Purpose:   decreases hero's health by flyer's strength (if health gets negative, reset to 0);
              if hero dies, its avatar is changed
        in:   pointer to the hero instance 
    */
void incurDamage(HeroType *hero, FlyerType *flyer){
    
    hero->health -= flyer->strength;

    if (hero->health >= 0){
        hero->health = 0;
        hero->partInfo.avatar = '+';
        hero->dead = C_TRUE;
    }
}

/* computes direction (-1 for left, +1 for right, 0 for same) of closest hero
   that is still alive and participating; direction is returned using parameter  */
void computeHeroDir(EscapeType *hollow, FlyerType *flyer, int *closestHero){
    HeroType *hero; 

    for (int i=0;i<hollow->heroes.size; i++){
        hero = *hollow->heroes.elements + i;

        if (abs(abs(hero->partInfo.pos.col) - 
        abs(flyer->partInfo.pos.col)) > *closestHero){
            closestHero = &hero->partInfo.pos.col;
        }
    }
}