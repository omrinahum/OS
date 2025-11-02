// Omri Nahum 211721477
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>  
#include <unistd.h>

#define NUM_OPPONENTS 3
#define MAX_LENGTH 256

struct gladiator {
    int id;
    int health;
    int attack;
    int opponents[3];
}; typedef struct gladiator gladiator;

// Extract gladiator ID from the filename
int extract_gladiator_id(const char* filename) {
    if (filename[0] == 'g') {
        return atoi(filename + 1);
    }
    return -1; 
}

// Create a gladiator from a file based on its ID
gladiator* gladiator_create(int id) {
    gladiator* new_gladiator = (gladiator*)malloc(sizeof(gladiator));
    if (new_gladiator == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_gladiator->id = id;

    // Open the file with the gladiator's ID
    char filename[100];
    snprintf(filename, sizeof(filename), "G%d.txt", id);
    FILE* my_file = fopen(filename, "r");
    if (my_file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        free(new_gladiator);
        return NULL;
    }

    // Read the file content into a buffer
    char line [MAX_LENGTH];
    int bytes_read = fread(line, 1, sizeof(line) - 1, my_file);
    if (bytes_read < 0) {
        fprintf(stderr, "Error reading file: %s\n", filename);
        fclose(my_file);
        return NULL;
    }   
    // Null-terminate the string  
    line[bytes_read] = '\0';
    
    // Parse the line to extract health, attack, and opponents
    char* token = strtok(line, ",");
    char* parts[5];
    int i = 0;
    
    while (token != NULL && i < 5) {
        parts[i] = token;
        token = strtok(NULL, ",");
        i++;
    }
    if (i != 5) {
        fprintf(stderr, "Error: Invalid file format\n");
        fclose(my_file);
        return NULL;
    }
    fclose(my_file);
    
    // Assign values to the gladiator struct
    new_gladiator->health = atoi(parts[0]);
    new_gladiator->attack = atoi(parts[1]);
    for (int i=2;i<5;i++){
        new_gladiator->opponents[i-2] = atoi(parts[i]);
    }

    return new_gladiator;
}

// Function to simulate the gladiator fight
void gladiator_fight(gladiator* glad, gladiator** opp_gladiator) {
    int my_health = glad->health;
    
    // Open the log file for writing
    char log_file_name[MAX_LENGTH]; 
    snprintf(log_file_name, sizeof(log_file_name), "G%d_log.txt", glad->id);
    FILE* log_file = fopen(log_file_name, "w+");
    if (log_file == NULL) {
        fprintf(stderr, "Error opening log file: %s\n", log_file_name);
        return;
    }

    // Add the process started message with PID to log file
    fprintf(log_file, "Gladiator process started. PID: %d\n", getpid());
    
    // Add screen logging for process start
    printf("[G%d] Entering arena (PID: %d, HP: %d)\n", glad->id, getpid(), my_health);
    
    // Loop through the opponents and simulate the fight until the gladiator's health is 0
    while (my_health > 0) {
        for (int i = 0; i < NUM_OPPONENTS; i++) {
            fprintf(log_file, "Facing opponent %d... Taking %d damage\n", opp_gladiator[i]->id, opp_gladiator[i]->attack);
            my_health -= opp_gladiator[i]->attack;
            if (my_health > 0) {
                fprintf(log_file, "Are you not entertained? Remaining health: %d\n", my_health);
            } else {
                fprintf(log_file, "The gladiator has fallen... Final health: %d\n", my_health);
                printf("[G%d] Defeated (PID: %d)\n", glad->id, getpid());
                break;
            }
        }
    }
    fclose(log_file);
}

// Function to destroy the gladiator object and free memory
void gladiator_destroy(gladiator* gladiator) {
    if (gladiator != NULL) {
        free(gladiator);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <gladiator_name>\n", argv[0]);
        return 1;
    }

    // Extract gladiator ID from the filename and create the gladiator
    int gladiator_id = extract_gladiator_id(argv[1]);
    gladiator* my_gladiator = gladiator_create(gladiator_id);
    gladiator* opp_gladiators[NUM_OPPONENTS] = {NULL, NULL, NULL};

    // Loop through the opponents and create them
    for (int i = 0; i < NUM_OPPONENTS; i++) {
        opp_gladiators[i] = gladiator_create(my_gladiator->opponents[i]);
    }

    gladiator_fight(my_gladiator, opp_gladiators);
    
    // Free the allocated memory for opponents and the gladiator
    for (int i = 0; i < NUM_OPPONENTS; i++) {
        gladiator_destroy(opp_gladiators[i]);
    }
    gladiator_destroy(my_gladiator);
    return 0;     
}
