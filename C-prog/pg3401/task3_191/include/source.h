#ifndef SOURCE_H
#define SOURCE_H

#define FLIGHTID_LEN 16
#define DEST_LEN 32
#define NAME_LEN 32
#define SEAT_LEN 8

typedef struct PassengerNode {
	char seat_number[SEAT_LEN];
	char name[NAME_LEN];
	int age;
	struct PassengerNode* next;
} PassengerNode;

typedef struct FlightNode {
	char flight_id[FLIGHTID_LEN];
	char destination[DEST_LEN];
	int seats;
	int time;
	PassengerNode* passengers;
	struct FlightNode* prev;
	struct FlightNode* next;
} FlightNode;

// Functions
void add_flight();
void add_passenger();
void retrieve_flight();
void find_flight_by_destination();
void delete_flight();
void change_seat();
void search_passenger_by_name();
void print_passengers_multiple_flights();
void cleanup();
void print_menu();

extern FlightNode* flight_head;
extern FlightNode* flight_tail;

#endif
