#include "defs.h"

int main()
{
  RestaurantType MyRestaurant;
  int choice;
  int PatronID;

  initRestaurant(&MyRestaurant, "Ced's Burgers");
  loadPatronData(&MyRestaurant);
  loadResData(&MyRestaurant);

  while (1) {
    printMenu(&choice);
    if (choice == 0){
      break;
      }
    if (choice == 1){
      printf("\n patrons at %s:\n", MyRestaurant.name);
      printPatrons(&MyRestaurant.patrons);

    }else if (choice == 2){
      printf("\n Reservations at %s:\n", MyRestaurant.name);

      printReservations(MyRestaurant.reservations);
    }else if (choice == 3){
      
      printf("Please enter the Patron ID: ");
      scanf("%d", &PatronID);
      printResByPatron(&MyRestaurant, PatronID);

    }
  }
  cleanupRestaurant(&MyRestaurant);
  
  return(0);
}

void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Print patrons\n");
  printf("  (2) Print reservations\n");
  printf("  (3) Print reservations by patron\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);    
  }

  *choice = c;
}
