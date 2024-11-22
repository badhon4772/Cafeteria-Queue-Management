#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define YELLOW "\033[1;33m"

// Function to display colored text
void printColoredText(const char *text, const char *color) {
    printf("%s%s\033[0m", color, text); // Reset color with \033[0m
}

// Queue Node Structure
typedef struct Node {
    int customerID;
    time_t timestamp;
    struct Node *next;
} Node;

// Global Variables
Node *front = NULL, *rear = NULL;
int totalCustomersServed = 0, peakQueueSize = 0, currentQueueSize = 0;

// Function Prototypes
void drawBox(const char *text, int width, const char *alignment);
void displayWelcomeScreen();
void queueManager();
void customerPanel();
void aboutSystem();
void enqueue(int customerID);
void dequeue();
void displayQueue();
void generateReport();
char *formatTime(time_t rawtime);
void safeInput(int *choice);

// Function to draw a box around text and center it
void drawBox(const char *text, int width, const char *alignment) {
    int textLength = strlen(text);
    int padding = (width - textLength) / 2;

    int leftPadding = 0;
    if (strcmp(alignment, "left") == 0) {
        leftPadding = 40;
    } else if (strcmp(alignment, "right") == 0) {
        leftPadding = 60;
    } else {
        leftPadding = 32;
    }

    printf("\n\n");
    printf("%*s", leftPadding, "");
    printColoredText("*", CYAN);
    for (int i = 0; i < width; i++) printColoredText("-", MAGENTA);
    printColoredText("*\n", CYAN);

    printf("%*s", leftPadding, "");
    printColoredText("|", YELLOW);
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", text);
    for (int i = 0; i < width - padding - textLength; i++) printf(" ");
    printColoredText("|\n", YELLOW);


    printf("%*s", leftPadding, "");
    printColoredText("*", CYAN);
    for (int i = 0; i < width; i++) printColoredText("-", MAGENTA);
    printColoredText("*\n", CYAN);
}

// Function to format timestamp
char *formatTime(time_t rawtime) {
    static char buffer[26];
    struct tm *timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return buffer;
}

// Function to display the welcome screen
void displayWelcomeScreen() {
    system("cls");
    drawBox("Welcome to my Cafeteria Management System project for Data Structure Lab", 75, "center");
    drawBox("1. Queue Manager", 30, "left");
    drawBox("2. Customer Panel", 30, "left");
    drawBox("3. About the System", 30, "left");
    drawBox("4. Generate Report", 30, "right");
    drawBox("5. Exit", 30, "right");
    printf("\nEnter your choice: ");
}

// Queue Manager (Admin Panel)
void queueManager() {
    int choice, customerID;
    while (1) {
        system("cls");
        drawBox("Queue Manager", 30, "center");
        printf("\n1. Enqueue Customer\n");
        printf("2. Serve and Remove Customer\n");
        printf("3. View Current Queue\n");
        printf("4. Back to Main Menu\n");
        printf("\nEnter your choice: ");
        safeInput(&choice);

        switch (choice) {
            case 1:
                printf("Enter customer ID to enqueue: ");
                safeInput(&customerID);
                enqueue(customerID);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice! Try again.\n");
        }
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }
}

// Customer Panel
void customerPanel() {
    system("cls");
    drawBox("Customer Panel", 30, "center");
    printf("\nYou can view your position in the queue here.\n");
    displayQueue();
    printf("\nPress Enter to go back...");
    getchar();
    getchar();
}

// About the System
void aboutSystem() {
    system("cls");
    drawBox("About the System", 30, "center");
    printf("\nThis Cafeteria Queue Management System is a project for Data Structure Lab Course (CSE135)\n");
    printf("designed to efficiently manage customer queues.\n");
    printColoredText("\nDeveloped by Nazmul Huda Badhon (Student ID: 221-15-4772).\n", YELLOW);
    printf("\nPress Enter to go back...");
    getchar();
    getchar();
}

// Function to enqueue a customer
void enqueue(int customerID) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->customerID = customerID;
    newNode->timestamp = time(NULL);
    newNode->next = NULL;

    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    currentQueueSize++;
    if (currentQueueSize > peakQueueSize) {
        peakQueueSize = currentQueueSize;
    }

    printf("Customer %d added to the queue at %s.\n", customerID, formatTime(newNode->timestamp));
}

// Function to dequeue a customer
void dequeue() {
    if (front == NULL) {
        printf("Queue is empty! No customers to serve.\n");
        return;
    }

    Node *temp = front;
    printf("Customer %d served at %s.\n", temp->customerID, formatTime(time(NULL)));

    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }

    free(temp);
    currentQueueSize--;
    totalCustomersServed++;
}

// Function to display the current queue
void displayQueue() {
    if (front == NULL) {
        printf("\nQueue is empty.\n");
        return;
    }

    Node *current = front;
    printf("\nCurrent Queue:\n");
    while (current != NULL) {
        printf("Customer ID: %d | Ordered at: %s\n", current->customerID, formatTime(current->timestamp));
        current = current->next;
    }
}

// Function to generate a report
void generateReport() {
    system("cls");
    drawBox("Queue Activity Report", 40, "center");
    printf("\nTotal Customers Served: %d\n", totalCustomersServed);
    printf("Peak Queue Size: %d\n", peakQueueSize);
    printf("Current Queue Size: %d\n", currentQueueSize);
    printf("\nPress Enter to go back...");
    getchar();
    getchar();
}

// Improved input validation
void safeInput(int *choice) {
    while (scanf("%d", choice) != 1) {
        printf("Invalid input! Please enter a valid number: ");
        while (getchar() != '\n'); // Clear invalid input
    }
}

// Main Function
int main() {
    int choice;
    while (1) {
        displayWelcomeScreen();
        safeInput(&choice); // Ensure valid input

        switch (choice) {
            case 1:
                queueManager();
                break;
            case 2:
                customerPanel();
                break;
            case 3:
                aboutSystem();
                break;
            case 4:
                generateReport();
                break;
            case 5:
                printf("Thank you for using the Cafeteria Queue Management System. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
