#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 50

struct Product {
    char name[MAX_NAME_LENGTH];
    int id;
    float price;
};

void addProduct(FILE *file) {
    struct Product product;

    printf("Enter product name: ");
    scanf(" %s", product.name);

    printf("Enter product ID: ");
    scanf("%d", &product.id);
    
    printf("Enter product price: ");
    scanf("%f", &product.price);

    fseek(file, 0, SEEK_END);
    fwrite(&product, sizeof(struct Product), 1, file);

    printf("Product added successfully!\n");
}

void displayProducts(FILE *file) {
    struct Product product;

    rewind(file);
    while (fread(&product, sizeof(struct Product), 1, file) == 1) {
        printf("Name: %s, ID: %d, Price: %.2f\n", product.name, product.id, product.price);
    }
}

void deleteProduct(FILE *file, int productId) {
    struct Product product;
    long int currentPosition = ftell(file);
    int found = 0;

    rewind(file);
    FILE *tempFile = fopen("temp.txt", "wb");
    if (tempFile == NULL) {
        printf("Error: Unable to open temporary file.\n");
        return;
    }

    while (fread(&product, sizeof(struct Product), 1, file) == 1) {
        if (product.id != productId) {
            fwrite(&product, sizeof(struct Product), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("products.txt");

    rename("temp.txt", "products.txt");

    if (found) {
        printf("Product deleted successfully!\n");
    } else {
        printf("Product not found.\n");
    }
}


void editProduct(FILE *file, int productId) {
    struct Product product;
    int found = 0;

    rewind(file);
    while (fread(&product, sizeof(struct Product), 1, file) == 1) {
        if (product.id == productId) {
            printf("Enter new name for product: ");
            scanf(" %s", product.name);

            printf("Enter new price for product: ");
            scanf("%f", &product.price);

            fseek(file, -sizeof(struct Product), SEEK_CUR);
            fwrite(&product, sizeof(struct Product), 1, file);
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Product information updated successfully!\n");
    } else {
        printf("Product not found.\n");
    }
}

int main() {
    FILE *file = fopen("products.txt", "ab+"); 

    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    int choice, productId;

    do {
        printf("\n$ -- Product Management System -- $\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Delete Product\n");
        printf("4. Edit Product\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct(file);
                break;
            case 2:
                displayProducts(file);
                break;
            case 3:
                printf("Enter product ID to delete: ");
                scanf("%d", &productId);
                deleteProduct(file, productId);
                break;
            case 4:
                printf("Enter product ID to edit: ");
                scanf("%d", &productId);
                editProduct(file, productId);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);

    fclose(file);
    return 0;
}
