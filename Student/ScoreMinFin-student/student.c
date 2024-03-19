#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 100

struct ScoreStudent {
    int studentID;
    char name[MAX_NAME_LENGTH];
    float midScore;
    float finScore;
};

void CheckScore(struct ScoreStudent *std) {
    float totalScore = std->midScore + std->finScore;

    if (totalScore >= 60) {
        printf("Student %s: Pass\n", std->name);
        printf("--------------------------\n");
    } else {
        printf("Student %s: Fail\n", std->name);
        printf("--------------------------\n");
    }
}

void InputStudent(struct ScoreStudent *std, int *numStudent) {
    printf("\nEnter the number of students: ");
    scanf("%d", numStudent);

    for (int i = 0; i < *numStudent; i++) {
        printf("\nEnter information for student: %d\n", i + 1);
        printf("Student ID: ");
        scanf("%d", &std[i].studentID);
        printf("Name: ");
        scanf("%s", std[i].name);
        printf("Score midTerm: ");
        scanf("%f", &std[i].midScore);
        printf("Score finalTerm: ");
        scanf("%f", &std[i].finScore);
        printf("--------------------------\n");
    }
}

void loadFromFile(struct ScoreStudent *students, int *numStudent) {
    FILE *file = fopen("ScoreStudent_history.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "Student %d %s: %f %f", &students[*numStudent].studentID, students[*numStudent].name, &students[*numStudent].midScore, &students[*numStudent].finScore) == 4) {
            (*numStudent)++;
        }
        fclose(file);
    } else {
        printf("Error: Could not open file for loading score student history.\n");
    }
}

void saveToFile(struct ScoreStudent *score, int numStudent) {
    FILE *file = fopen("ScoreStudent_history.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < numStudent; i++) {
            float totalScore = score[i].midScore + score[i].finScore;
            if (totalScore >= 60) {
                fprintf(file, "Student %d %s: %.2f %.2f Pass\n", score[i].studentID, score[i].name, score[i].midScore, score[i].finScore);
            } else {
                fprintf(file, "Student %d %s: %.2f %.2f Fail\n", score[i].studentID, score[i].name, score[i].midScore, score[i].finScore);
            }
        }
        fclose(file);
    } else {
        printf("Error: Could not open file for saving score student history.\n");
    }
}


void readFromFile() {
    FILE *file = fopen("ScoreStudent_history.txt", "r");
    if (file != NULL) {
        char line[256];
        printf("\nHistory from file:\n");
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("Error: Could not open file for reading score student history.\n");
    }
}

int main() {
   struct ScoreStudent students[MAX_STUDENTS];
    int numStudent = 0;
    int choice;
    loadFromFile(students, &numStudent);

    do {
        printf("\nCalculate score student system!\n");
        printf("1. Input data\n");
        printf("2. Check score student\n");
        printf("3. History score\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                InputStudent(students, &numStudent);
                printf("Input Successful!\n");
                saveToFile(students, numStudent); 
                break;
            case 2:
                if (numStudent == 0) {
                    printf("No students data.\n");
                } else {
                    printf("\nEnter the student's name to check score: ");
                    char studentName[MAX_NAME_LENGTH];
                    scanf("%s", studentName);
                    int found = 0;
                    for (int i = 0; i < numStudent; i++) {
                        if (strcmp(students[i].name, studentName) == 0) {
                            CheckScore(&students[i]);
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        printf("Student not found.\n");
                    }
                }
                break;
            case 3:
                readFromFile(); 
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 4);

    return 0;
}
