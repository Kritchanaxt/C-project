#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NORMAL_RATE 700
#define VIP_RATE 1200
#define NUM_ROOM_NORMAL 10
#define NUM_ROOM_VIP 2
#define MAX_RESERVATIONS 10

struct ReservationHotel {
    char name[100];
    char IDcard[14];
    char email[100];
    char phone[12];
    int roomType;
    int NumRoom;
    int NumDays;
    char start[12];
    char end[12];
};

int calculateCost(int roomType, int NumRoom, int NumDays){
    if (roomType == 1){
        return NumRoom * NumDays * NORMAL_RATE;
    } else if (roomType == 2){
        return NumRoom * NumDays * VIP_RATE;
    } else 
        return 0;
}
void InputReservation(struct ReservationHotel *reservation) {
    printf("ENTER ROOM TYPE (1: NORMAL / 2: VIP): ");
    scanf("%d", &reservation->roomType);
    printf("\n");
    printf("---------------------------------------------\n");
    printf("\n");
    printf("ENTER NUMBER OF DAYS: ");
    scanf("%d", &reservation->NumDays);
    printf("\n");
    printf("---------------------------------------------\n");
    printf("\n");
    printf("ENTER NUMBER OF ROOM: ");
    scanf("%d", &reservation->NumRoom);
    printf("\n");
    printf("---------------------------------------------\n");
    printf("\n");
    printf("ENTER START DATE (dd/mm/yyyy): ");
    scanf("%s", reservation->start);
    printf("\n");
    printf("---------------------------------------------\n");
    printf("\n");
    printf("ENTER END DATE (dd/mm/yyyy): ");
    scanf("%s", reservation->end);
    printf("\n");
    printf("---------------------------------------------\n");
    printf("\n");
    printf("ENTER NAME: ");
    scanf("%s", reservation->name);
    printf("\n");
    printf("---------------------------------------------\n");
    printf("\n");
    printf("ENTER ID CARD: ");
    scanf("%s", reservation->IDcard);
    printf("\n");
    printf("---------------------------------------------\n");
    printf("\n");
    printf("ENTER EMAIL: ");
    scanf("%s", reservation->email);
    printf("\n");
    printf("---------------------------------------------\n");
    printf("\n");
    printf("ENTER PHONE: ");
    scanf("%s", reservation->phone);
    printf("\n");
}

void FindAvailableRoom(struct ReservationHotel *reservations[], int numReservations) {
    int availableRooms[NUM_ROOM_NORMAL + NUM_ROOM_VIP] = {0};
    int i;

    for (i = 0; i < numReservations; i++) {
        if (reservations[i]->roomType == 1){
            availableRooms[reservations[i]->NumRoom - 1] = 1;

        } else if (reservations[i]->roomType == 2){
            availableRooms[NUM_ROOM_NORMAL + reservations[i]->NumRoom - 1] = 1;
        }
    }

    printf("\nAVAILABLE ROOMS!\n");
    printf("\n");
    printf("NORMAL ROOMS:\n");
    for (i = 0; i < NUM_ROOM_NORMAL; i++) {
        if (!availableRooms[i])
            printf("ROOM %d\n", i + 1);
    }
    printf("\n");
    printf("VIP ROOMS:\n");
    for (i = 0; i < NUM_ROOM_VIP; i++) {
        if (!availableRooms[NUM_ROOM_NORMAL + i])
            printf("ROOM %d\n", i + 1);
    }
}

void ReservationDetail(struct ReservationHotel *reservation, int totalCost) {
    time_t t;
    struct tm *currentDateTime;

    time(&t);
    currentDateTime = localtime(&t);

    printf("---------------------------------------------\n");
    printf("\nRESERVATION HOTEL DETAILS\n");
    printf("You have reservation a time: %02d/%02d/%04d TIME: %02d:%02d %s\n",
           currentDateTime->tm_mday,
           currentDateTime->tm_mon + 1,
           currentDateTime->tm_year + 1900,
           currentDateTime->tm_hour % 12 == 0 ? 12 : currentDateTime->tm_hour % 12,
           currentDateTime->tm_min,
           currentDateTime->tm_hour < 12 ? "AM" : "PM");
    printf("Room Type: %s\n", reservation->roomType == 1 ? "Normal" : "VIP");
    printf("Number of Days: %d\n", reservation->NumDays);
    printf("Number of Room: %d\n", reservation->NumRoom);
    printf("Start Date: %s\n", reservation->start);
    printf("End Date: %s\n", reservation->end);
    printf("Name: %s\n", reservation->name);
    printf("ID Card: %s\n", reservation->IDcard);
    printf("Email: %s\n", reservation->email);
    printf("Phone: %s\n", reservation->phone);
    printf("Total Service Cost: %d THB\n", totalCost);
    printf("---------------------------------------------\n");
    printf("\n");
    printf("\nTHANK YOU FOR USING OUR SERVICE\n");
    printf("\n");
}

void SaveToFile(struct ReservationHotel *reservation, int totalCost) {

    time_t t;
    struct tm *currentDateTime;

    time(&t);
    currentDateTime = localtime(&t);

    FILE *file = fopen("ReservationHotel_history.txt", "a");
    if (file != NULL) {
        fprintf(file, "RESERVATION HOTEL DETAILS\n");
        fprintf(file,"You have reservation a time: %02d/%02d/%04d TIME: %02d:%02d %s\n",
           currentDateTime->tm_mday,
           currentDateTime->tm_mon + 1,
           currentDateTime->tm_year + 1900,
           currentDateTime->tm_hour % 12 == 0 ? 12 : currentDateTime->tm_hour % 12,
           currentDateTime->tm_min,
           currentDateTime->tm_hour < 12 ? "AM" : "PM");
        fprintf(file, "Room Type: %s\n", reservation->roomType == 1 ? "Normal" : "VIP");
        fprintf(file, "Number of Days: %d\n", reservation->NumDays);
        fprintf(file, "Number of Room: %d\n", reservation->NumRoom);
        fprintf(file, "Start Date: %s\n", reservation->start);
        fprintf(file, "End Date: %s\n", reservation->end);
        fprintf(file, "Name: %s\n", reservation->name);
        fprintf(file, "ID Card: %s\n", reservation->IDcard);
        fprintf(file, "Email: %s\n", reservation->email);
        fprintf(file, "Phone: %s\n", reservation->phone);
        fprintf(file, "Total Service Cost: %d THB\n", totalCost);
        fprintf(file, "---------------------------------------------\n\n");
        fclose(file);

    } else {
        printf("ERROR: Could not open file for saving reservation details.\n");
    }
}

int main() {
    struct ReservationHotel *reservations[MAX_RESERVATIONS];
    int numReservations = 0;
    int choice, totalCost;

    do {
        printf("\n");
        printf("*-------------------------- RESERVATION HOTEL SYSTEM! -------------------------*\n");
        printf("\n");
        printf("1. MAKE A RESERVATION\n");
        printf("2. FIND AVAILABLE ROOMS\n");
        printf("3. EXIT\n");
        printf("\nENTER YOUR CHOICE: ");
        scanf("%d", &choice);
        printf("\n");
        printf("---------------------------------------------\n");
        printf("\n");

        switch (choice) {
            case 1:
                if (numReservations < MAX_RESERVATIONS) {
                    reservations[numReservations] = malloc(sizeof(struct ReservationHotel));

                    if (reservations[numReservations] != NULL) {
                        InputReservation(reservations[numReservations]);

                        totalCost = calculateCost(reservations[numReservations]->roomType, 
                        reservations[numReservations]->NumRoom, reservations[numReservations]->NumDays);

                        ReservationDetail(reservations[numReservations], totalCost);

                        SaveToFile(reservations[numReservations], totalCost);

                        numReservations++;

                    } else {
                        printf("Memory allocation failed. Unable to make a reservation.\n");
                    }

                } else {
                    printf("Maximum number of reservations reached.\n");
                }
                break;

            case 2:
                FindAvailableRoom(reservations, numReservations);
                break;

            case 3:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);

    for (int i = 0; i < numReservations; i++) {
        free(reservations[i]);
    }

    return 0;
}
