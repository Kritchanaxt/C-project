#include <stdio.h>
#include <math.h>

#define RATE_PER_KM 10

struct Passenger {
    char name[50];
    int age;
};

struct Route {
    float distance; 
    int duration; 
};


float calculateDistance(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int calculateDuration(float distance) {
    return distance / 60 * 60; 
}

float calculateCost(float distance) {
    return distance * RATE_PER_KM;
}


int main() {
    struct Passenger passenger;
    struct Route route;
    float startX, startY, endX, endY;

    printf("Enter passenger name: ");
    scanf(" %s", passenger.name);
    printf("Enter passenger age: ");
    scanf("%d", &passenger.age);
    printf("Enter starting point coordinates (x, y): ");
    scanf("%f %f", &startX, &startY);
    printf("Enter destination coordinates (x, y): ");
    scanf("%f %f", &endX, &endY);

    route.distance = calculateDistance(startX, startY, endX, endY);

    route.duration = calculateDuration(route.distance);
    
    float cost = calculateCost(route.distance);

    printf("\nPassenger Details:\n");
    printf("Name: %s\n", passenger.name);
    printf("Age: %d\n", passenger.age);
    printf("\nTravel Route Details:\n");
    printf("Distance: %.2f km\n", route.distance);
    printf("Duration: %d minutes\n", route.duration);
    printf("Cost: %.2f THB\n", cost);

    return 0;
}
