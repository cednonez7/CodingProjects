#include "defs.h"

void initResvList(ResvListType *list);
void initResvTime(ResvTimeType **rt, int yr, int mth, int day, int hr, int min);
void initResv(ResvType **r, PatronType *p, ResvTimeType *rt);
int lessThan(ResvTimeType *r1, ResvTimeType *r2);
void addResv(ResvListType *list, ResvType *r);
void printReservation(ResvType *r);
void printReservations(ResvListType *list);
void cleanupResvList(ResvListType *list);

/*
  Function:   initResvList
   Purpose:   Initializes both fields of the given list parameter to default values
in and out:   Pointer to the ResvListType instance that is to be initiated
   */
void initResvList(ResvListType *list)
{
    list->head = NULL;
    list->nextId = RES_IDS;
}

/*
  Function:   initResvTime
   Purpose:   Dynamically allocates memory for a ResvTimeType structure, initializes its
              fields to the given parameters, and “returns” this new structure using the 
              rt parameter.
in and out:   Pointer to a ResvTimeType instance
        in:   Year value to be initialized
        in:   Month value to be initialized
        in:   Day value to be initialized
        in:   Hour value to be initialized
        in:   Minute value to be initialized
   */
void initResvTime(ResvTimeType **rt, int yr, int mth, int day, int hr, int min)
{
    ResvTimeType *tmpRt;

    tmpRt = malloc(sizeof(ResvListType));

    tmpRt->year = yr;
    tmpRt->month = mth;
    tmpRt->day = day;
    tmpRt->hours = hr;
    tmpRt->minutes = min;

    *rt = tmpRt;
}

/*
  Function:   initResv
   Purpose:   Dynamically allocates memory for a ResvType structure, initializes its patron
              and reservation time fields to the given parameters, and “returns” this new 
              structure using the r parameter.
in and out:   ResvType instance to be initiated
        in:   The patron that made the reservation
        in:   The time of the reservation
   */
void initResv(ResvType **r, PatronType *p, ResvTimeType *rt)
{
    ResvType *tmpRes;

    tmpRes = malloc(sizeof(ResvType));

    tmpRes->id = 0;
    tmpRes->patron = p;
    tmpRes->resvTime = rt;

    *r = tmpRes;
}

/*
  Function:   lessThan
   Purpose:   Compares two reservation times, and returns the constant associated with true
              if the first reservation begins earlier in date and time than the second one, 
              and the constant for false otherwise.
        in:   Time of the first reservation
        in:   Time of the second reservation
   */
int lessThan(ResvTimeType *r1, ResvTimeType *r2)
{
    // year
    if (r1->year < r2->year){
        return C_TRUE;
    }else if(r1->year < r2->year){
        return C_FALSE;
    }
    // month
    if (r1->month < r2->month){
        return C_TRUE;
    }else if(r1->month < r2->month){
        return C_FALSE;
    }
    // day
    if (r1->day < r2->day){
        return C_TRUE;
    }else if(r1->day < r2->day){
        return C_FALSE;
    }
    // hours
    if (r1->hours < r2->hours){
        return C_TRUE;
    }else if(r1->hours < r2->hours){
        return C_FALSE;
    }
    // minutes
    if (r1->minutes < r2->minutes){
        return C_TRUE;
    }else if(r1->minutes < r2->minutes){
        return C_FALSE;
    }
    return C_FALSE;
}

/*
  Function:   addResv
   Purpose:   Adds the reservation r in its correct position in the given list, so that the 
              list remains ordered in ascending (increasing) order by reservation time.
in and out:   Pointer to the ResvListType instance to be added to the restaurant list.
        in:   Reservation to be added to the given list
   */
void addResv(ResvListType *list, ResvType *r)
{
    NodeType *newNode;
    NodeType *currNode;
    NodeType *prevNode;

    newNode = malloc(sizeof(NodeType));
    newNode->data = r;
    newNode->next = NULL;
    newNode->prev = NULL;
    int counter = 0;

    currNode = list->head;
    prevNode = NULL;
    
    while (currNode != NULL){
        counter++;
        currNode = currNode->next;
    }
    newNode->data->id = RES_IDS + counter;
    currNode = list->head;

    while (currNode != NULL){

        if (lessThan(newNode->data->resvTime,currNode->data->resvTime) == C_TRUE){
            break;
        }

        prevNode = currNode;
        currNode = currNode->next;
    }
    
    if (prevNode == NULL) {
        list->head = newNode;
    }else {
        prevNode->next = newNode;
        newNode->prev  = prevNode;
    }

    newNode->next  = currNode;

    if (currNode != NULL) {
        currNode->prev = newNode;
    }
}
/*  
  Function:   printReservation
   Purpose:   Prints out all the details of the given reservation
in and out:   Reservation to be printed
   */
void printReservation(ResvType *r)
{
    // Reservation ID :: year-month-day @ hour:minute :: patron name
    printf("%04d :: %04d-%02d-%02d @ %02d:%02d :: %s\n", 
            r->id, r->resvTime->year, r->resvTime->month, r->resvTime->day, r->resvTime->hours, 
            r->resvTime->minutes, r->patron->name);
}

/*
  Function:   printReservations
   Purpose:   Prints out the details of every reservation in the given list
        in:   List of reservations to be printed to the screen
   */
void printReservations(ResvListType *list)
{
    NodeType *currNode = list->head;
    NodeType *prevNode = NULL;
    
    printf("\nFORWARD:\n");
    while (currNode != NULL) {
        printReservation(currNode->data);
        prevNode = currNode;
        currNode = currNode->next;
  }

  printf("\nBACKWARD:\n");
  currNode = prevNode;
  while (currNode != NULL) {
    printReservation(currNode->data);
    currNode = currNode->prev;
  }
}

/*
  Function:   cleanupResvList
   Purpose:   deallocates all the required dynamically allocated memory for the given list
in and out:   Pointer to the ResvListType to be deallocated
   */
void cleanupResvList(ResvListType *list)
{
    NodeType *currNode = list->head;
    NodeType *nextNode;

    while (currNode != NULL) {
    nextNode = currNode->next;
    free(currNode);
    currNode = nextNode;
  }
}