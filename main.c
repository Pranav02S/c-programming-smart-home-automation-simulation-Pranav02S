#include <stdio.h>
#include <stdbool.h>

// Constants
#define MAX_ROOMS 5

// Global state
bool lights[MAX_ROOMS];
float temperature[MAX_ROOMS];
bool motionDetected[MAX_ROOMS];

// Function prototypes
void initializeSystem();
void displayMenu();
void controlLights();
void readTemperature();
void detectMotion();
void securitySystem();
void analyzeHouseStatus();

int main() {
    int choice;

    initializeSystem();

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                controlLights();
                break;
            case 2:
                readTemperature();
                break;
            case 3:
                detectMotion();
                break;
            case 4:
                securitySystem();
                break;
            case 5:
                analyzeHouseStatus();
                break;
            case 6:
                printf("Exiting system...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

void initializeSystem() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        lights[i] = false;
        temperature[i] = 25.0; // default temperature
        motionDetected[i] = false;
    }
    printf("System initialized successfully.\n");
}

void displayMenu() {
    printf("\n🏠 Smart Home Control System 🏠\n");
    printf("1. Control Lights\n");
    printf("2. Read Temperature\n");
    printf("3. Detect Motion\n");
    printf("4. Security System Status\n");
    printf("5. Analyze House Status\n");
    printf("6. Exit\n");
}

void controlLights() {
    int room;
    printf("Enter room number (0-%d): ", MAX_ROOMS - 1);
    scanf("%d", &room);

    if (room >= 0 && room < MAX_ROOMS) {
        lights[room] = !lights[room];
        printf("Lights in Room %d turned %s.\n", room, lights[room] ? "ON" : "OFF");
    } else {
        printf("Invalid room number.\n");
    }
}

void readTemperature() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        printf("Room %d temperature: %.1f°C\n", i, temperature[i]);
    }
}

void detectMotion() {
    int room;
    printf("Enter room number to simulate motion detection (0-%d): ", MAX_ROOMS - 1);
    scanf("%d", &room);

    if (room >= 0 && room < MAX_ROOMS) {
        motionDetected[room] = true;
        printf("Motion detected in Room %d!\n", room);
    } else {
        printf("Invalid room number.\n");
    }
}

void securitySystem() {
    printf("Security System Status:\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        printf("Room %d: %s\n", i, motionDetected[i] ? "Motion detected" : "No motion");
    }
}

void analyzeHouseStatus() {
    printf("Analyzing house status...\n");
    for (int i = 0; i < MAX_ROOMS; i++) {
        printf("Room %d: Lights: %s | Temp: %.1f°C | Motion: %s\n", i,
               lights[i] ? "ON" : "OFF",
               temperature[i],
               motionDetected[i] ? "Yes" : "No");
    }
}
