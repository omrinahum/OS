// Omri Nahum 211721477
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>     
#include <sys/wait.h>    

#define NUM_GLADIATORS 4

void create_gladiators(char* names[], char* files[], int pid[]) {
    printf("🏛️  ARENA: Creating gladiator processes...\n");
    for (int i = 0; i < NUM_GLADIATORS; i++) {
        pid_t child_pid = fork();
        pid[i] = child_pid;
        
        // The child process will run the gladiator program
        if (child_pid == 0) {
            execlp("./gladiator", "gladiator", files[i], NULL);
            perror("Exec failed");
            exit(1);
        }
        // Fork failed
         else if (child_pid < 0) {
            perror("Fork failed");
            exit(1);
        } else {
            printf("⚔️  Spawned %s (PID: %d)\n", names[i], child_pid);
        }
    }
    printf("🏛️  ARENA: All gladiators ready. Let the battle begin!\n\n");
}

int run_tournament(int pid[], char* names[]) {
    int status;
    pid_t terminated_pid;
    bool finished[NUM_GLADIATORS] = {false};
    int defeated_count = 0;
    
    // Wait for first 3 gladiators to finish
    for (int i = 0; i < NUM_GLADIATORS - 1; i++) {
        terminated_pid = wait(&status);
        
        for (int j = 0; j < NUM_GLADIATORS; j++) {
            if (terminated_pid == pid[j]) {
                finished[j] = true;
                defeated_count++;
                printf("💀 %s has fallen! (PID: %d) [%d/%d defeated]\n", 
                       names[j], terminated_pid, defeated_count, NUM_GLADIATORS - 1);
                break;
            }
        }
    }
    
    // The last gladiator 
    terminated_pid = wait(&status);
    
    // Find which gladiator finished last (is still not marked as finished)
    for (int i = 0; i < NUM_GLADIATORS; i++) {
        if (!finished[i]) {
            printf("\n🏆 Victory! %s stands alone!\n", names[i]);
            return i;  
        }
    }
    
    // No winner found
    return -1;  
}

int main(int argc, char *argv[]) {    
    char* gladiator_names[NUM_GLADIATORS] = {"Maximus", "Lucius", "Commodus", "Spartacus"};
    char* gladiator_files[NUM_GLADIATORS] = {"g1", "g2", "g3", "g4"};
    int pid[4];
    
    printf("\n═══════════════════════════════════════\n");
    printf("   GLADIATOR TOURNAMENT SIMULATOR\n");
    printf("═══════════════════════════════════════\n\n");
    
    // Create gladiator processes
    create_gladiators(gladiator_names, gladiator_files, pid);
    
    // Run the tournament 
    int winner = run_tournament(pid, gladiator_names);
    
    // Announce the winner
    printf("\n═══════════════════════════════════════\n");
    if (winner != -1) {
        printf("   🎖️  THE GODS HAVE SPOKEN!\n");
        printf("   Champion: %s\n", gladiator_names[winner]);
    } else {
        printf("   ❌ Error: Could not determine winner\n");
    }
    printf("═══════════════════════════════════════\n\n");
    
    return 0;
}
