#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "source.h"

// Global pointers that point to head and tail of linked list
FlightNode* flight_head = NULL;
FlightNode* flight_tail = NULL;

// Createss a new flight node
static FlightNode* create_flight(const char* flight_id, const char* destination, int seats, int time) {
	FlightNode* node = (FlightNode*)malloc(sizeof(FlightNode));
	strcpy(node->flight_id, flight_id);
	strcpy(node->destination, destination);
	node->seats = seats;
	node->time = time;
	node->passengers = NULL;
	node->prev = node->next = NULL;
	return node;
}

// Creates a new passenger node
static PassengerNode* create_passenger(const char* seat_number, const char* name, int age) {
	PassengerNode* node = (PassengerNode*)malloc(sizeof(PassengerNode));
	strncpy(node->seat_number, seat_number, SEAT_LEN - 1);
	node->seat_number[SEAT_LEN - 1] = '\0';
	strncpy(node->name, name, NAME_LEN - 1);
	node->name[NAME_LEN - 1] = '\0';
	node->age = age;
	node->next = NULL;
	return node;
}

// Adds a flight to the end of the list and asks user for required details
void add_flight() {
	char flight_id[FLIGHTID_LEN], destination[DEST_LEN];
	int seats, time;
	printf("Enter flight ID: ");
	scanf("%s", flight_id);
	printf("Enter destination: ");
	scanf("%s", destination);
	printf("Enter number of seats: ");
	scanf("%d", &seats);
	printf("Enter departure time (integer): ");
	scanf("%d", &time);

	FlightNode* node = create_flight(flight_id, destination, seats, time);
	if (!flight_head) {
        flight_head = flight_tail = node;
	} else {
		flight_tail->next = node;
		node->prev = flight_tail;
        	flight_tail = node;
    }
    printf("Flight added.\n");
}

// Find flight by number (1-based), returns pointer or NULL
static FlightNode* get_flight_by_number(int n) {
	FlightNode* curr = flight_head;
	int count = 1;
	while (curr) {
		if (count == n) return curr;
		curr = curr->next;
		count++;
	}
	return NULL;
}

// Add a passenger to a flight,but keeps list sorted by seat number
void add_passenger() {
	int flight_num, age;
	char seat_number[SEAT_LEN], name[NAME_LEN];
	printf("Enter flight number to add passenger to: ");
	scanf("%d", &flight_num);
	FlightNode* flight = get_flight_by_number(flight_num);
	if (!flight) {
        printf("Flight not found.\n");
        return;
	}
	printf("Enter seat number (for example 19A): ");
	scanf("%s", seat_number);
	printf("Enter passenger name: ");
	scanf("%s", name);
	printf("Enter age: ");
	scanf("%d", &age);

// Checks for insertion point and checks for duplicated seat
	PassengerNode *curr = flight->passengers, *prev = NULL;
	while (curr && strcmp(curr->seat_number, seat_number) < 0) {
		prev = curr;
        	curr = curr->next;
	}
	if (curr && strcmp(curr->seat_number, seat_number) == 0) {
		printf("Seat already taken.\n");
        	return;
    	}
    PassengerNode* node = create_passenger(seat_number, name, age);
    if (!prev) {
        node->next = flight->passengers;
        flight->passengers = node;
	} else {
        node->next = prev->next;
        prev->next = node;
	}
    printf("Passenger added.\n");
}

// Print flight and passenger info
static void print_flight_info(FlightNode* flight, int number) {
	printf("Flight #%d: %s to %s, Seats: %d, Time: %d\n", number, flight->flight_id, flight->destination, flight->seats, flight->time);
    	printf("Passengers:\n");
    	PassengerNode* p = flight->passengers;
    	if (!p) printf("  None\n");
    	while (p) {
		printf("  Seat %s: %s, Age %d\n", p->seat_number, p->name, p->age);
        	p = p->next;
	}
}

// Asks for flight number and prints the given detail regarding the flight if details are acknowledged
void retrieve_flight() {
	int n;
    	printf("Enter flight number to retrieve: ");
    	scanf("%d", &n);
    	FlightNode* flight = get_flight_by_number(n);
    	if (!flight) {
        	printf("Flight not found.\n");
        	return;
    	}
    	print_flight_info(flight, n);
}

// Searches after flight by destination and then prints its position in the list
void find_flight_by_destination() {
    	char destination[DEST_LEN];
    	printf("Enter destination to search: ");
    	scanf("%s", destination);
    	FlightNode* curr = flight_head;
    	int count = 1;
    	while (curr) {
        	if (strcmp(curr->destination, destination) == 0) {
            		printf("Flight to %s is at position %d.\n", destination, count);
            		return;
		}
        	curr = curr->next;
        	count++;
    	}
    	printf("No flight to %s found.\n", destination);
}

// Delete all passengers in a flight
static void delete_passenger_list(PassengerNode* head) {
    	while (head) {
        	PassengerNode* tmp = head;
        	head = head->next;
        	free(tmp);
    	}
}

// Delete a flight, also deletes the passengers in the given flight
void delete_flight() {
    	int n;
    	printf("Enter flight number to delete: ");
    	scanf("%d", &n);
    	FlightNode* curr = get_flight_by_number(n);
    	if (!curr) {
        	printf("Flight not found.\n");
        	return;
    	}
// Remove from list
    	if (curr->prev) curr->prev->next = curr->next;
    	else flight_head = curr->next;
    	if (curr->next) curr->next->prev = curr->prev;
    	else flight_tail = curr->prev;

    	delete_passenger_list(curr->passengers);
    	free(curr);
    	printf("Flight deleted.\n");
}

// Change the seat of a passenger, checks that the given seat is not already taken
void change_seat() {
    	int flight_num;
    	char old_seat[SEAT_LEN], new_seat[SEAT_LEN];
    	printf("Enter flight number: ");
    	scanf("%d", &flight_num);
    	FlightNode* flight = get_flight_by_number(flight_num);
    	if (!flight) {
        	printf("Flight not found.\n");
        	return;
    	}
    	printf("Enter current seat number: ");
    	scanf("%s", old_seat);
    	printf("Enter new seat number: ");
    	scanf("%s", new_seat);

// Find and remove passenger from old seat
	PassengerNode *curr = flight->passengers, *prev = NULL;
    	while (curr && strcmp(curr->seat_number, old_seat) != 0) {
        	prev = curr;
        	curr = curr->next;
    	}
    	if (!curr) {
        	printf("Passenger not found at seat %s.\n", old_seat);
        	return;
    	}
// Check if new seat is taken
    	PassengerNode *check = flight->passengers;
    	while (check) {
        	if (strcmp(check->seat_number, new_seat) == 0) {
            	printf("New seat already taken.\n");
            	return;
        }
        check = check->next;
}

// Remove from old position
if (!prev) flight->passengers = curr->next;
else prev->next = curr->next;
    
// Insert into new position, sorted
strncpy(curr->seat_number, new_seat, SEAT_LEN - 1);
curr->seat_number[SEAT_LEN - 1] = '\0';
PassengerNode *p = flight->passengers, *p_prev = NULL;
while (p && strcmp(p->seat_number, new_seat) < 0) {
	p_prev = p;
        p = p->next;
    	}	
    	if (!p_prev) {
        	curr->next = flight->passengers;
        	flight->passengers = curr;
    	} else {
        	curr->next = p_prev->next;
        	p_prev->next = curr;
    	}
    	printf("Seat changed.\n");
}

// Search for a passengers name in all flights
void search_passenger_by_name() {
	char name[NAME_LEN];
    	printf("Enter passenger name to search: ");
    	scanf("%s", name);
    	int found = 0;
    	FlightNode* flight = flight_head;
    	int flight_num = 1;
    	while (flight) {
        	PassengerNode* p = flight->passengers;
        	while (p) {
            		if (strcmp(p->name, name) == 0) {
                		printf("Passenger %s found on flight #%d (%s to %s), seat %s\n",
                       			name, flight_num, flight->flight_id, flight->destination, p->seat_number);
                		found = 1;
            		}
            		p = p->next;
        	}
        	flight = flight->next;
        	flight_num++;
	}
    	if (!found) printf("Passenger %s not found on any flight.\n", name);
}

// Helper struct for duplicate name check
typedef struct NameNode {
    	char name[NAME_LEN];
    	int count;
    	struct NameNode* next;
} NameNode;

// Add or increment name in list
static void add_or_increment(NameNode** head, const char* name) {
	NameNode* curr = *head;
    	while (curr) {
        	if (strcmp(curr->name, name) == 0) {
            	curr->count++;
            	return;
        	}
        	curr = curr->next;
    	}
    	NameNode* node = (NameNode*)malloc(sizeof(NameNode));
    	strncpy(node->name, name, NAME_LEN - 1);
    	node->name[NAME_LEN - 1] = '\0';
    	node->count = 1;
    	node->next = *head;
    	*head = node;
}

// Print passengers booked on more than one flight
void print_passengers_multiple_flights() {
    	NameNode* name_list = NULL;
    	FlightNode* flight = flight_head;
    	while (flight) {
        	PassengerNode* p = flight->passengers;
        	while (p) {
            		add_or_increment(&name_list, p->name);
            		p = p->next;
        	}
        	flight = flight->next;
    	}
    	int found = 0;
    	NameNode* curr = name_list;
    	printf("Passengers booked on more than one flight:\n");
    	while (curr) {
        	if (curr->count > 1) {
            	printf("  %s\n", curr->name);
            	found = 1;
        	}
        	curr = curr->next;
    	}
    	if (!found) printf("  None\n");
	// Free name_list
    	while (name_list) {
        	NameNode* tmp = name_list;
        	name_list = name_list->next;
        	free(tmp);
    	}
}

// Cleans up all the data
void cleanup() {
    	while (flight_head) {
        	FlightNode* tmp = flight_head;
        	flight_head = flight_head->next;
        	delete_passenger_list(tmp->passengers);
        	free(tmp);
    	}
    	flight_tail = NULL;
}

// Menu print function
void print_menu() {
    	printf("\n--- Flight Departure System ---\n");
    	printf("1. Add flight\n");
    	printf("2. Add passenger to flight\n");
    	printf("3. Retrieve flight N and print info\n");
    	printf("4. Find flight by destination\n");
    	printf("5. Delete flight\n");
    	printf("6. Change seat of a passenger\n");
    	printf("7. Search for passenger by name\n");
    	printf("8. Print passengers on more than one flight\n");
    	printf("9. Exit\n");
    	printf("Choose option: ");
}
