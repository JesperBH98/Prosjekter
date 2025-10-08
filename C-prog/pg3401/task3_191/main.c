#include <stdio.h>
#include "source.h"

// Flight system menu layout
int main() {
    int choice;
    while (1) {
        print_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: add_flight(); break;
            case 2: add_passenger(); break;
            case 3: retrieve_flight(); break;
            case 4: find_flight_by_destination(); break;
            case 5: delete_flight(); break;
            case 6: change_seat(); break;
            case 7: search_passenger_by_name(); break;
            case 8: print_passengers_multiple_flights(); break;
            case 9: cleanup(); printf("Exiting...\n"); return 0;
            default: printf("Invalid option.\n");
        }
    }
}
