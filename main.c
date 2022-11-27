#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONG_SPACE "===================================\n"

typedef struct Date {
    int month;
    int day;
    long year;
} Date;

typedef struct Task {
    int id;
    char contents[100];
    Date *date;
    struct Task *next;
} Task;

Task *addTask(char task[], Date *date);

Date *addDate(int month, int day, long year);

void showDate(Date *date);

void insertToHead(Task *insert);

void showAllTasks();

void freeAll();

Task *head = NULL;

int main() {
    char task[100];
    int choice, month, day;
    long year;
    do {
        printf("\nWelcome to your To-Do List!\n");
        printf(LONG_SPACE);
        printf("[1] Add New Task\n");
        printf("[2] Show All Tasks\n");
        printf("[3] Exit\n");
        printf("--> ");
        scanf(" %d", &choice);

        switch (choice) {
            case 1:
                // Prevent newlines
                fflush(stdin);

                // Get task from user
                printf("Enter task: ");
                scanf("%[^\n]", task);

                // Get deadline from user
                printf("Enter deadline (MM/DD/YYYY): ");
                scanf("%d %d %li", &month, &day, &year);

                insertToHead(addTask(task, addDate(month, day, year)));
                printf("Successfully added!\n");
                break;

            case 2:
                showAllTasks();
                break;

            case 3:
                printf("Thank you for using To-Do List!\n");
                freeAll();
                break;

            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 3);

    return 0;
}

Task *addTask(char task[], Date *date) {
    Task *newTask = malloc(sizeof(Task));
    strcpy(newTask->contents, task);
    newTask->date = date;
    newTask->next = NULL;
    return newTask;
}

Date *addDate(int month, int day, long year) {
    Date *date = malloc(sizeof(Date));
    date->month = month;
    date->day = day;
    date->year = year;
    return date;
}

void showDate(Date *date) {
    if (date == NULL) {
        return;
    } else {
        printf("%d %d %li\n", date->month, date->day, date->year);
    }
}

void insertToHead(Task *insert) {
    if (head == NULL) {
        insert->id = 1;
        head = insert;
    } else {
        Task *temp = head;
        int count = 1;
        while (temp->next != NULL) {
            temp = temp->next;
            count++;
        }
        temp->id = count;
        temp->next = insert;
    }
}

void showAllTasks() {
    if (head == NULL) {
        printf("No tasks entered yet!\n");
        return;
    }

    printf("ID\tTask\t\tDate\n");
    printf(LONG_SPACE);
    for (Task *tempTask = head; tempTask != NULL; tempTask = tempTask->next) {
        printf("%d\t%s\t\t", tempTask->id, tempTask->contents);
        showDate(tempTask->date);
    }
}

void freeAll() {
    for (Task *temp = head, *save; temp != NULL; temp = save) {
        save = temp->next;
        free(temp->date);
        free(temp);
    }
}
