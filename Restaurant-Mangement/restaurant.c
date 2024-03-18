#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MENU_ITEMS 20
#define MAX_NAME_LENGTH 50


struct MenuItem {
    char name[MAX_NAME_LENGTH];
    int price;
    char category[MAX_NAME_LENGTH];
};


void addMenuItem(struct MenuItem *menu, int *numItems) {
    if (*numItems < MAX_MENU_ITEMS) {
        printf("Enter name of the menu item: ");
        scanf(" %[^\n]", menu[*numItems].name); 
        printf("Enter price of the menu item: ");
        scanf("%d", &menu[*numItems].price);
        printf("Enter category of the menu item: ");
        scanf(" %[^\n]", menu[*numItems].category); 
        (*numItems)++;
        printf("Menu item added successfully!\n");
    } else {
        printf("Menu is full. Cannot add more items.\n");
    }
}


void displayMenu(const struct MenuItem *menu, int numItems) {
    printf("Menu:\n");
    for (int i = 0; i < numItems; i++) {
        printf("%d. Name: %s, Price: %d, Category: %s\n", i + 1, menu[i].name, menu[i].price, menu[i].category);
    }
}


int calculateTotalPrice(const struct MenuItem *menu, int numItems) {
    int totalPrice = 0;
    for (int i = 0; i < numItems; i++) {
        totalPrice += menu[i].price;
    }
    return totalPrice;
}


void sortMenuByCategory(struct MenuItem *menu, int numItems) {
    for (int i = 0; i < numItems - 1; i++) {
        for (int j = 0; j < numItems - i - 1; j++) {
            if (strcmp(menu[j].category, menu[j + 1].category) > 0) {
                struct MenuItem temp = menu[j];
                menu[j] = menu[j + 1];
                menu[j + 1] = temp;
            }
        }
    }
}

int main() {
    struct MenuItem menu[MAX_MENU_ITEMS];
    int numItems = 0;
    int choice;

    do {
        printf("\n-- Restaurant Management System --\n");
        printf("1. Add Menu Item\n");
        printf("2. Display Menu\n");
        printf("3. Calculate Total Price\n");
        printf("4. Sort Menu by Category\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMenuItem(menu, &numItems);
                break;
            case 2:
                displayMenu(menu, numItems);
                break;
            case 3:
                printf("Total price of all menu items: %d\n", calculateTotalPrice(menu, numItems));
                break;
            case 4:
                sortMenuByCategory(menu, numItems);
                printf("Menu sorted by category.\n");
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}
