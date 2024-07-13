#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defs.h"

void initPatronArray(PatronArrayType *arr);
void addPatron(PatronArrayType *arr, char *n);
int findPatron(PatronArrayType *arr, int id, PatronType **p);
void printPatrons(PatronArrayType *arr);
void cleanupPatronArray(PatronArrayType *arr);

/*
  Function:   initPatronArray
   Purpose:   Initializes every field of the given patron collection to default values
in and out:   Pointer to a PatronArrayType instance
   */
void initPatronArray(PatronArrayType *arr)
{
    arr->numPat = 0;
    arr->nextId = 0;
    arr->elements = calloc(MAX_CAP, sizeof(PatronType));
}

/*
  Function:   addPatron
   Purpose:   Adds a new patron to the back of the given patron collection
in and out:   Pointer to the PatronArrayType instance that is being updated
        in:   Name of the patron being added to the list
   */
void addPatron(PatronArrayType *arr, char *n)
{
    
    if (arr->numPat >= MAX_CAP){
        printf("Patron limit reached.\n");
        return;
    }
    
    PatronType newPatron;
    strcpy(newPatron.name, n);
    newPatron.id = PATRON_IDS + arr->numPat;
    
    arr->elements[arr->numPat] = newPatron;
    arr->numPat++;
}

/*
  Function:   findPatron
   Purpose:   Searches through the given patron collection to find the patron with the given id
        in:   Pointer to a PatronArrayType instance
        in:   Id of the patron we are searching for
       out:   The patron, if found
    return:   An error flag if the patron is not found, or a success flag otherwise
   */
int findPatron(PatronArrayType *arr, int id, PatronType **p)
{
    for (int i=0;i<arr->numPat;i++){
        if (id < PATRON_IDS){
            return C_NOK;
        }
        for (int i=0;i<arr->numPat;i++){
            if (arr->elements[i].id == id){
                *p = &arr->elements[i];
            }
        }
    }

    return C_OK;
}

/*
  Function:   printPatrons
   Purpose:   Prints out to the screen all the details of every patron in the given patron collection
        in:   Pointer to a PatronArrayType instance
   */
void printPatrons(PatronArrayType *arr)
{
    PatronType *index;
    for (int i=0; i < arr->numPat;i++){
        index = &arr->elements[i];
        printf("Patron #%4d %s\n",index->id, index->name);
    }
}

/*
  Function:   cleanupPatronArray
   Purpose:   Deallocates all the required dynamically allocated memory for the given patron collection
in and out:   Pointer to a PatronArrayType instance
   */
void cleanupPatronArray(PatronArrayType *arr)
{
    for (int i=0; i > arr->numPat;i++){
        free(arr->elements + i);
    }
    
    free(arr->elements);
}