#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NORMAL_RATE 80
#define VIP_RATE 110
#define OVERTIME_RATE 1.5
#define NUM_NORMAL_TABLES 8
#define NUM_VIP_TABLES 4

struct Reservation {
    char name[100];
    char phone[11];
    int tableType;
    int tableNumber;
    int hours;
    int minutes;
};

struct LoyaltyPoint {
    char name[100];
    unsigned long long points;
};

struct LoyaltyPoint loyaltyPoints[100];
int totalLoyaltyMembers = 0;

unsigned long long getTotalPoints(const char *phone){
    for (int i = 0; i < totalLoyaltyMembers; ++i)
    {
        if (strcmp(loyaltyPoints[i].name, phone) == 0){
            return loyaltyPoints[i].points;
        }
    }
    return 0; 
}

int calculateCost(int tableType, int tableNumber, int hours, int minutes){
    int totalCost = 0, i;
    int normalTableNumbers[NUM_NORMAL_TABLES] = {1, 2, 3, 4, 5, 6, 7, 8};
    int vipTableNumbers[NUM_VIP_TABLES] = {9, 10, 11, 12};

    switch (tableType) {
    case 1:
        for (i = 0; i < NUM_NORMAL_TABLES; i++){
            if (tableNumber == normalTableNumbers[i]){
                totalCost = hours * NORMAL_RATE;
                break;
            }
        } if (totalCost == 0){
            return 0;
        }
        break;
    case 2:
        for (i = 0; i < NUM_VIP_TABLES; i++){
            if (tableNumber == vipTableNumbers[i]){
                totalCost = hours * VIP_RATE;
                break;
            }
        } if (totalCost == 0){
            return 0;
        }
        break;
    default:
        return 0;
    }

    int overtimeHours = 0;

    if (hours > 1){
        overtimeHours = hours - 1;
    }

    totalCost += overtimeHours * OVERTIME_RATE * 60;

    for (i = 0; i < minutes; i++){
        totalCost += 1.5 * OVERTIME_RATE;
    }

    return totalCost;
}

void CheckInDetails(){
    time_t t;
    struct tm *currentDateTime;

    time(&t);
    currentDateTime = localtime(&t);

    printf("---------------------------------------------\n");
    printf("\n");
    printf("CHECK IN DATE/TIME: %02d/%02d/%04d TIME: %02d:%02d %s\n",
           currentDateTime->tm_mday, 
           currentDateTime->tm_mon + 1, 
           currentDateTime->tm_year + 1900,
           currentDateTime->tm_hour % 12 == 0 ? 12 : currentDateTime->tm_hour % 12,
           currentDateTime->tm_min, 
           currentDateTime->tm_hour < 12 ? "AM" : "PM");
    printf("\n");
    printf("---------------------------------------------\n");
    printf("\n");
    printf(" ------------------------\n");
    printf("| CALCULATE OVERTIME PAY |\n");
    printf(" ------------------------\n");
    printf("\n");
}

void getName(struct Reservation *reservation){
    printf("ENTER YOUR NAME: ");     
    scanf("%s", reservation->name);
    printf("\n");
    printf("---------------------------------------------\n");
    printf("\n");
    printf("ENTER YOUR PHONE NUMBER: ");
    scanf("%s", reservation->phone);
    printf("\n");
}

void ReservationDetails(struct Reservation *reservation, int totalCost, unsigned long long currentPoints){
    printf("---------------------------------------------\n");
    printf("\n");
    printf(" ---------------------\n");
    printf("| RESERVATION DETAILS |\n");
    printf(" ---------------------\n");
    printf("\n");
    printf("ENTER YOUR NAME: %s\n", reservation->name);
    printf("ENTER YOUR PHONE NUMBER: %s\n", reservation->phone);
    printf("TABLE TYPE: %s\n", (reservation->tableType == 1) ? "NORMAL" : "VIP");
    printf("TABLE NUMBER: %d\n", reservation->tableNumber);
    printf("BOOKING DURATION: %d HOURS %d MINUTES\n", reservation->hours, reservation->minutes);
    printf("TOTAL SERVICE COST: %d THB\n", totalCost);
    printf("EARN POINTS FOR: %d POINTS\n", reservation->hours);
}


void CheckOutDetails(int tableType, int tableNumber, int hours, int minutes, struct Reservation *reservation, int totalCost){
    time_t t;
    struct tm *currentDateTime;

    time(&t);
    currentDateTime = localtime(&t);

    FILE *file = fopen("reservation_history.txt", "a");
    if (file != NULL) {
        fprintf(file, "CHECK OUT DATE/TIME: %02d/%02d/%04d TIME: %02d:%02d %s\n",
                currentDateTime->tm_mday, 
                currentDateTime->tm_mon + 1, 
                currentDateTime->tm_year + 1900,
                currentDateTime->tm_hour % 12 == 0 ? 12 : currentDateTime->tm_hour % 12,
                currentDateTime->tm_min, 
                currentDateTime->tm_hour < 12 ? "AM" : "PM");
        fprintf(file, "NAME: %s\n", reservation->name);
        fprintf(file, "PHONE NUMBER: %s\n", reservation->phone);
        fprintf(file, "TABLE TYPE: %s\n", (tableType == 1) ? "NORMAL" : "VIP");
        fprintf(file, "TABLE NUMBER: %d\n", tableNumber);
        fprintf(file, "BOOKING DURATION: %d HOURS %d MINUTES\n", hours, minutes);
        fprintf(file, "TOTAL SERVICE COST: %d THB\n", totalCost);

        unsigned long long previousPoints = 0;
        for (int i = 0; i < totalLoyaltyMembers; ++i){
            if (strcmp(loyaltyPoints[i].name, reservation->phone) == 0) {
                previousPoints = loyaltyPoints[i].points;
                break;
            }
        }

        unsigned long long currentPoints = previousPoints + hours;
        fprintf(file, "CURRENT TOTAL: %llu POINTS\n", currentPoints);
        fprintf(file, "---------------------------------------------\n\n");

        for (int i = 0; i < totalLoyaltyMembers; ++i) {
            if (strcmp(loyaltyPoints[i].name, reservation->phone) == 0) {
                loyaltyPoints[i].points = currentPoints;
                break;
            }
        }
        fclose(file);

    } else {
        printf("ERROR: Could not open the file for saving reservation details.\n");
    }

    printf("\n");
    printf("---------------------------------------------\n");
    printf("\n");
    printf("CHECK OUT DATE/TIME: %02d/%02d/%04d TIME: %02d:%02d %s\n",
           currentDateTime->tm_mday,
           currentDateTime->tm_mon + 1,
           currentDateTime->tm_year + 1900,
           currentDateTime->tm_hour % 12 == 0 ? 12 : currentDateTime->tm_hour % 12,
           currentDateTime->tm_min,
           currentDateTime->tm_hour < 12 ? "AM" : "PM");
    printf("\n*------------------------- THANK YOU FOR USING OUR SERVICE -------------------------*\n");
    printf("\n");
}

void showReservationHistory(){
    FILE *file = fopen("reservation_history.txt", "r");

    if (file != NULL) {
         
        char line[200];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }

        fclose(file);
    } else {
        printf("ERROR: Could not open the file for showing reservation history.\n");
    }
}

void addPoints(const char *phone, int hours) {
    int found = 0, i;
    for (i = 0; i < totalLoyaltyMembers; ++i){
        if (strcmp(loyaltyPoints[i].name, phone) == 0){
            found = 1;
            loyaltyPoints[i].points += hours;        }
    }

    if (!found){
        strcpy(loyaltyPoints[totalLoyaltyMembers].name, phone);
        loyaltyPoints[totalLoyaltyMembers].points = hours;
        totalLoyaltyMembers++;
    }
}


int main(){

    do {
        struct Reservation reservation;
        unsigned long long currentPoints = getTotalPoints(reservation.phone); 
        int totalCost, totalPoint;

        printf("\n");
        printf("*-------------------------- SNOOKER TABLE BOOKING SYSTEM! -------------------------*\n");
        printf("\n");

        printf(" --------------------\n");
        printf("| MENU SNOOKER TABLE |\n");
        printf(" --------------------\n");
        printf("\n");
        printf("1.NORMAL RATE 80 THB\n");
        printf("* TABLE THERE ARE NUMBERS\n");
        printf("\n");
        printf("NUMBER: 1\tNUMBER: 2\nNUMBER: 3\tNUMBER: 4\nNUMBER: 5\tNUMBER: 6\nNUMBER: 7\tNUMBER: 8\n");
        printf("\n");
        printf("2.VIP RATE 110 THB\n");
        printf("* TABLE THERE ARE NUMBERS\n");
        printf("\n");
        printf("NUMBER: 9\tNUMBER: 10\nNUMBER: 11\tNUMBER: 12\n");
        printf("\n");
        printf("---------------------------------------------\n");
        printf("\n");

        printf("ENTER TABLE TYPE (1 FOR NORMAL / 2 FOR VIP): ");
        scanf("%d", &reservation.tableType);
        printf("\n");
        printf("---------------------------------------------\n");
        printf("\n");

        if (reservation.tableType != 1 && reservation.tableType != 2){
            printf("INVALID TABLE TYPE.\n");
            continue; 
            break;
        }

        printf("ENTER TABLE NUMBER: ");
        scanf("%d", &reservation.tableNumber);
        printf("\n");
        printf("---------------------------------------------\n");
        printf("\n");

        if ((reservation.tableType == 1 && (reservation.tableNumber < 1 || reservation.tableNumber > 8)) ||
            (reservation.tableType == 2 && (reservation.tableNumber < 9 || reservation.tableNumber > 12))) {
            printf("INVALID TABLE NUMBER.\n");
            continue;
            break;
        }

        printf("ENTER NUMBER OF HOURS TO BOOK: ");
        scanf("%d", &reservation.hours);
        printf("\n");
        printf("---------------------------------------------\n");
        printf("\n");

        if (reservation.hours <= 0){
            printf("INVALID NUMBER OF HOURS.\n");
            continue; 
            break;
        }

        getName(&reservation);

        CheckInDetails();

        printf("ENTER NUMBER OF MINUTES FOR OVERTIME: ");
        scanf("%d", &reservation.minutes);
        printf("\n");

        if (reservation.minutes < 0){
            printf("INVALID NUMBER OF MINUTES.\n");
            continue; 
            break;
        }

        totalCost = calculateCost(reservation.tableType, reservation.tableNumber, reservation.hours, reservation.minutes);

        if (totalCost == 0){
            printf("INVALID TABLE TYPE OR NUMBER.\n");
            continue; 
            break;
        }

        addPoints(reservation.phone, reservation.hours);

        ReservationDetails(&reservation, totalCost, currentPoints);

        CheckOutDetails(reservation.tableType, reservation.tableNumber, reservation.hours, reservation.minutes, &reservation, totalCost);

        printf("\n");
        printf("DO YOU WANT TO MAKE ANOTHER RESERVATION? (3 FOR YES / 4 FOR SHOW HISTORY / 0 FOR NO): ");

        int choice;
        scanf("%d", &choice);

        if (choice == 4){
            showReservationHistory();
        } else if (choice != 3){
            break;
        }

    } while (1);

    return 0;
}
