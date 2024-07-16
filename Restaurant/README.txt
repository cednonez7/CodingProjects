
Assignment 4 submission
Cedric Nonez
101268510

Program purpose:
Runs a multithreaded restaurant server, which has a list of patrons, each with their own list of reservations

Included files:

defs.h 
main.c
load.c 
resv.c 
patrons.c 
restaurant.c 

Instructions:

To compile and run files, use the following instruction:

Compile: gcc -Wall -o a4 defs.h load.c patrons.c resv.c restaurant.c main.c
Run: /.a4

All functions used in my submission:

void printMenu(int*);
void loadPatronData(RestaurantType*);
void loadResData(RestaurantType*);

void initPatronArray(PatronArrayType *arr);
void addPatron(PatronArrayType *arr, char *n);
int findPatron(PatronArrayType *arr, int id, PatronType **p);
void printPatrons(PatronArrayType *arr);
void cleanupPatronArray(PatronArrayType *arr);

void initResvList(ResvListType *list);
void initResvTime(ResvTimeType **rt, int yr, int mth, int day, int hr, int min);
void initResv(ResvType **r, PatronType *p, ResvTimeType *rt);
int lessThan(ResvTimeType *r1, ResvTimeType *r2);
void addResv(ResvListType *list, ResvType *r);
void printReservation(ResvType *r);
void printReservations(ResvListType *list);
void cleanupResvList(ResvListType *list);

void initRestaurant(RestaurantType *r, char *n);
int validateResvTime(int yr, int mth, int day, int hr, int min);
void createResv(RestaurantType *r, int pId, int yr, int mth, int day, int hr, int min);
void printResByPatron(RestaurantType *r, int id);
void cleanupRestaurant(RestaurantType *r);

Detailed function explanation:

patrons.c functions:

  Function:   initPatronArray
   Purpose:   Initializes every field of the given patron collection to default values
in and out:   Pointer to a PatronArrayType instance

Function:   addPatron
   Purpose:   Adds a new patron to the back of the given patron collection
in and out:   Pointer to the PatronArrayType instance that is being updated
        in:   Name of the patron being added to the list
        
Function:   findPatron
   Purpose:   Searches through the given patron collection to find the patron with the given id
        in:   Pointer to a PatronArrayType instance
        in:   Id of the patron we are searching for
       out:   The patron, if found
    return:   An error flag if the patron is not found, or a success flag otherwise

Function:   printPatrons
   Purpose:   Prints out to the screen all the details of every patron in the given patron collection
        in:   Pointer to a PatronArrayType instance

Function:   cleanupPatronArray
   Purpose:   Deallocates all the required dynamically allocated memory for the given patron collection
in and out:   Pointer to a PatronArrayType instance

resv.c functions:

Function:   initResvList
   Purpose:   Initializes both fields of the given list parameter to default values
in and out:   Pointer to the ResvListType instance that is to be initiated

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
        
Function:   initResv
   Purpose:   Dynamically allocates memory for a ResvType structure, initializes its patron
              and reservation time fields to the given parameters, and “returns” this new 
              structure using the r parameter.
in and out:   ResvType instance to be initiated
        in:   The patron that made the reservation
        in:   The time of the reservation
        
Function:   lessThan
   Purpose:   Compares two reservation times, and returns the constant associated with true
              if the first reservation begins earlier in date and time than the second one, 
              and the constant for false otherwise.
        in:   Time of the first reservation
        in:   Time of the second reservation
        
Function:   addResv
   Purpose:   Adds the reservation r in its correct position in the given list, so that the 
              list remains ordered in ascending (increasing) order by reservation time.
in and out:   Pointer to the ResvListType instance to be added to the restaurant list.
        in:   Reservation to be added to the given list
        
Function:   printReservation
   Purpose:   Prints out all the details of the given reservation
in and out:   Reservation to be printed

Function:   printReservations
   Purpose:   Prints out the details of every reservation in the given list
        in:   List of reservations to be printed to the screen
        
Function:   cleanupResvList
   Purpose:   deallocates all the required dynamically allocated memory for the given list
in and out:   Pointer to the ResvListType to be deallocated

restaurant.c functions:

Function:   initRestaurant
   Purpose:   Initializes the three fields of the given restaurant structure
in and out:   pointer to the Restaurant instance to be initiated  
        in:   Name of the restaurant
        
Function:   validateResvTime
   Purpose:   Checks that the parameters represent a valid date and time
        in:   The year to be verified
        in:   The month to be verified
        in:   The day to be verified
        in:   The hour to be verified
        in:   The minute  to be verified
        
Function:   createResv
   Purpose:   Creates a new reservation and adds it to the given restaurant
in and out:   Pointer to a RestaurantType instance
        in:   Name of the club being initiated
        
Function:   printResByPatron
   Purpose:   Prints out the restaurant name and the details of every reservation made by the patron with
              the given id.
in and out:   Pointer to the Restaurant instance from which the patron has made reservations.
        in:   Id of the patron
        
Function:   cleanupRestaurant
   Purpose:   Cleans up all the dynamically allocated memory for the given restaurant r.
in and out:   Pointer to the RestaurantType instance to be cleared up.
        in:   Name of the club being initiated

