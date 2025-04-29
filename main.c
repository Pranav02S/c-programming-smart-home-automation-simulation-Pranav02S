#include <stdio.h>

#define MAX_INPUTS 1000
#define TEMP_ALERT 30
#define LIGHT_USAGE_LIMIT 5  // Number of times all lights ON triggers energy saving suggestion

// Function declarations
void initializeSystem(int lights[], int temp[], int motion[], int locks[], int rooms);
void displayMenu();
void controlLights(int lights[], int rooms, int *allLightsCounter);
void readTemperature(int temp[], int rooms);
void detectMotion(int motion[], int rooms, int *motionCounter);
void securitySystem(int locks[], int rooms);
void analyzeHouseStatus(int lights[], int temp[], int motion[], int locks[], int rooms);
int allLightsOn(int lights[], int rooms);
int anyTempHigh(int temp[], int rooms);
void autoLock(int motionCounter, int locks[], int rooms);

int main() {
    int rooms;
    printf("Enter number of rooms (1-100): ");
    scanf("%d", &rooms);
    if (rooms < 1 || rooms > 100) {
        printf("Invalid number of rooms.\n");
        return 1;
    }

    int lights[rooms];
    int temp[rooms];
    int motion[rooms];
    int locks[rooms];
    int choice;
    int motionCounter = 0;
    int allLightsOnCounter = 0;

    initializeSystem(lights, temp, motion, locks, rooms);

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                controlLights(lights, rooms, &allLightsOnCounter);
                break;
            case 2:
                readTemperature(temp, rooms);
                break;
            case 3:
                detectMotion(motion, rooms, &motionCounter);
                break;
            case 4:
                securitySystem(locks, rooms);
                break;
            case 5:
                analyzeHouseStatus(lights, temp, motion, locks, rooms);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

        autoLock(motionCounter, locks, rooms);
        if (anyTempHigh(temp, rooms)) {
            printf("⚠️ Warning: One or more rooms have temperature above %d°C!\n", TEMP_ALERT);
        }
        if (allLightsOn(lights, rooms)) {
            allLightsOnCounter++;
            if (allLightsOnCounter >= LIGHT_USAGE_LIMIT) {
                printf("💡 Energy Saving Tip: All lights have been ON for a while. Consider turning some OFF.\n");
            }
        } else {
            allLightsOnCounter = 0; // reset if not all ON
        }

    } while(choice != 6);

    return 0;
}

void initializeSystem(int lights[], int temp[], int motion[], int locks[], int rooms) {
    for (int i = 0; i < rooms; i++) {
        lights[i] = 0;
        temp[i] = 22 + (i % 5); // Simulated temperature
        motion[i] = 0;
        locks[i] = 1;
    }
    printf("Initializing system...\n");
}

void displayMenu() {
    printf("\n===== Smart Home Menu =====\n");
    printf("1. Toggle Light\n");
    printf("2. Read Temperature\n");
    printf("3. Check Motion Sensor\n");
    printf("4. Lock/Unlock Security System\n");
    printf("5. House Status Summary\n");
    printf("6. Exit\n");
}

void controlLights(int lights[], int rooms, int *allLightsCounter) {
    int room;
    printf("Enter room number to toggle light (1-%d): ", rooms);
    scanf("%d", &room);
    if (room < 1 || room > rooms) {
        printf("Invalid room number.\n");
        return;
    }
    lights[room - 1] = !lights[room - 1];
    printf("Light in Room %d is now %s.\n", room, lights[room - 1] ? "ON" : "OFF");
}

void readTemperature(int temp[], int rooms) {
    int room;
    printf("Enter room number to read temperature (1-%d): ", rooms);
    scanf("%d", &room);
    if (room < 1 || room > rooms) {
        printf("Invalid room number.\n");
        return;
    }
    printf("Room %d Temperature: %d°C\n", room, temp[room - 1]);
}

void detectMotion(int motion[], int rooms, int *motionCounter) {
    int room;
    printf("Enter room number to check motion (1-%d): ", rooms);
    scanf("%d", &room);
    if (room < 1 || room > rooms) {
        printf("Invalid room number.\n");
        return;
    }
    motion[room - 1] = 1; // Simulate motion
    *motionCounter = 0;   // Reset no-motion counter
    printf("Motion detected in Room %d!\n", room);
}

void securitySystem(int locks[], int rooms) {
    int room;
    printf("Enter room number to toggle lock (1-%d): ", rooms);
    scanf("%d", &room);
    if (room < 1 || room > rooms) {
        printf("Invalid room number.\n");
        return;
    }
    locks[room - 1] = !locks[room - 1];
    printf("Room %d is now %s.\n", room, locks[room - 1] ? "LOCKED" : "UNLOCKED");
}

void analyzeHouseStatus(int lights[], int temp[], int motion[], int locks[], int rooms) {
    printf("\nHouse Status:\n");
    for (int i = 0; i < rooms; i++) {
        printf("Room %d: Light %s, Temp %d°C, %s, %s\n",
               i + 1,
               lights[i] ? "ON" : "OFF",
               temp[i],
               motion[i] ? "Motion Detected" : "No Motion",
               locks[i] ? "Locked" : "Unlocked");
        motion[i] = 0; // Reset motion after reporting
    }
}

int allLightsOn(int lights[], int rooms) {
    for (int i = 0; i < rooms; i++) {
        if (!lights[i])
            return 0;
    }
    return 1;
}

int anyTempHigh(int temp[], int rooms) {
    for (int i = 0; i < rooms; i++) {
        if (temp[i] > TEMP_ALERT)
            return 1;
    }
    return 0;
}

void autoLock(int motionCounter, int locks[], int rooms) {
    static int noMotionCount = 0;
    noMotionCount++;

    if (motionCounter == 0 && noMotionCount >= 5) {
        for (int i = 0; i < rooms; i++) {
            locks[i] = 1;
        }
        noMotionCount = 0;
        printf("🔒 Auto-lock activated: All rooms have been locked due to inactivity.\n");
    }
}
