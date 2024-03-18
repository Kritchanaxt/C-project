#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 50
#define MAX_NAME_LENGTH 50

struct Student {
    char name[MAX_NAME_LENGTH];
    int scores[5]; 
    float averageScore;
};


void addStudent(struct Student *students, int *numStudents) {
    int i;

    if (*numStudents < MAX_STUDENTS) {
        printf("Enter student name: ");
        scanf("%s", students[*numStudents].name);

        printf("\nEnter scores for 5 subjects:\n");
        for (i = 0; i < 5; i++) {
            printf("Score for subject %d: ", i + 1);
            scanf("%d", &students[*numStudents].scores[i]);
        }
        
        (*numStudents)++;
        printf("\nStudent added successfully!\n");

    } else {
        printf("Maximum number of students reached. Cannot add more.\n");
    }
}

void calculateAverage(struct Student *student) {
    float sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += student->scores[i];
    }
    student->averageScore = sum / 5;
}

int calculateMaxScore(struct Student *students, int numStudents) {
    int maxScore = -1;
    int i, j;

    for (i = 0; i < numStudents; i++) {
        for (j = 0; j < 5; j++) {
            if (students[i].scores[j] > maxScore) {
                maxScore = students[i].scores[j];
            }
        }
    }
    return maxScore;
}

void displayStudents(struct Student *students, int numStudents) {
    int i, j;

    printf("Student List\n");
    for (i = 0; i < numStudents; i++) {
        printf("Name: %s\n", students[i].name);
        printf("Scores: ");

        for (j = 0; j < 5; j++) {
            printf("%d ", students[i].scores[j]);
        }
        printf("\n");
        printf("Average score: %.2f\n", students[i].averageScore);
    }
}

int main() {
    struct Student students[MAX_STUDENTS];
    int numStudents = 0;
    int choice, i;

    do {
        printf("\n+ -- STUDENT MANAGEMENT SYSTEM! -- +\n");
        printf("1. ADD STUDENT\n");
        printf("2. CALCULATE AVERAGE SCORE\n");
        printf("3. CALCULATE MAXIMUM SCORE\n");
        printf("4. DISPLAY STUDENTS\n");
        printf("5. EXIT\n");
        printf("\nENTER YOUR CHOICE: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1:
                addStudent(students, &numStudents);
                break;
            case 2:
                for (i = 0; i < numStudents; i++) {
                    calculateAverage(&students[i]);
                }
                printf("Average scores calculated successfully!\n");
                break;
            case 3:
                printf("Maximum score: %d\n", calculateMaxScore(students, numStudents));
                break;
            case 4:
                displayStudents(students, numStudents);
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
