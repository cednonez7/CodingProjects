#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defs.h"

void initRestaurant(RestaurantType *r, char *n);
int validateResvTime(int yr, int mth, int day, int hr, int min);
void createResv(RestaurantType *r, int pId, int yr, int mth, int day, int hr, int min);
void printResByPatron(RestaurantType *r, int id);
void cleanupRestaurant(RestaurantType *r);

/*
  Function:   initRestaurant
   Purpose:   Initializes the three fields of the given restaurant structure
in and out:   pointer to the Restaurant instance to be initiated  
        in:   Name of the restaurant
   */
void initRestaurant(RestaurantType *r, char *n)
{  
   strcpy(r->name, n);

   initResvList(r->reservations);
   initPatronArray(&r->patrons);
   
}

/*
  Function:   validateResvTime
   Purpose:   Checks that the parameters represent a valid date and time
        in:   The year to be verified
        in:   The month to be verified
        in:   The day to be verified
        in:   The hour to be verified
        in:   The minute  to be verified
   */
int validateResvTime(int yr, int mth, int day, int hr, int min)
{
   //year
   if (yr < 2023 || yr > 2024)
         return C_NOK;
      
   // month
   if (mth < 1 || mth > 12)
      return C_NOK;
   
   // day
   if (day < 1 || day > 31)
      return C_NOK;
   
   // hours
   if (hr < 0 || hr > 23)
      return C_NOK;
   
   // minutes
   if (min < 0 || min > 59)
      return C_NOK;
   
   return C_OK;
}

/*
  Function:   createResv
   Purpose:   Creates a new reservation and adds it to the given restaurant
in and out:   Pointer to a RestaurantType instance
        in:   Name of the club being initiated
   */
void createResv(RestaurantType *r, int pId, int yr, int mth, int day, int hr, int min)
{
   PatronType *patron;
   ResvTimeType *newRestTime;
   ResvType *newResv;

   int rc = validateResvTime(yr, mth, day, hr, min);
   if (rc == C_NOK){
      printf("Invalid time parameters.\n");
      return;
   }

   rc = findPatron(&r->patrons, pId, &patron);

   if (rc == C_NOK){
      printf("The Patron ID was not found within the current restaurant list.\n");
      return;
   }

   initResvTime(&newRestTime, yr, mth, day, hr, min);

   initResv(&newResv, patron, newRestTime);

   addResv(r->reservations, newResv);
}

/*
  Function:   printResByPatron
   Purpose:   Prints out the restaurant name and the details of every reservation made by the patron with
              the given id.
in and out:   Pointer to the Restaurant instance from which the patron has made reservations.
        in:   Id of the patron
   */
void printResByPatron(RestaurantType *r, int id)
{
   NodeType *currNode = r->reservations->head;

    printf("\nRESERVATIONS BY PATRON at %s:\n", r->name);
   while (currNode != NULL) {
      if (currNode->data->patron->id == id){
         printReservation(currNode->data);
      }
    currNode = currNode->next;
  }
}

/*
  Function:   cleanupRestaurant
   Purpose:   Cleans up all the dynamically allocated memory for the given restaurant r.
in and out:   Pointer to the RestaurantType instance to be cleared up.
        in:   Name of the club being initiated
   */
void cleanupRestaurant(RestaurantType *r)
{
   cleanupPatronArray(&r->patrons);
   cleanupResvList(r->reservations);
}