# Multi-Process Gladiator Tournament

## Topic
**Multi-Process Programming & Process Synchronization**

## Description
A gladiator battle simulator where each gladiator runs as an independent process. The tournament manager spawns gladiator processes that fight concurrently until one remains victorious.

## Key Concepts
- **Process Creation**: `fork()` to spawn child processes
- **Process Execution**: `execlp()` to run gladiator program
- **Process Synchronization**: `wait()`/`waitpid()` for process coordination
- **File I/O**: Reading stats from files and writing battle logs
- **Inter-Process Communication**: Parent-child process management

## How to Run (*This would only work on Linux*)

### Compile
```bash
gcc -o gladiator gladiator.c
gcc -o tournament tournament.c
```

### Run
```bash
./tournament
```

### Test
```bash
# Compile the tester
gcc -o tester tester.c

# Run the tester
./tester
```

## Example Output

### Tournament Run
```
═══════════════════════════════════════
   GLADIATOR TOURNAMENT SIMULATOR
═══════════════════════════════════════

🏛️  ARENA: Creating gladiator processes...
⚔️  Spawned Maximus (PID: 2889)
⚔️  Spawned Lucius (PID: 2890)
⚔️  Spawned Commodus (PID: 2891)
⚔️  Spawned Spartacus (PID: 2892)
🏛️  ARENA: All gladiators ready. Let the battle begin!

[G2] Entering arena (PID: 2890, HP: 1000)
[G1] Defeated (PID: 2890)
[G1] Entering arena (PID: 2889, HP: 10000)
[G4] Entering arena (PID: 2892, HP: 500)
[G4] Defeated (PID: 2892)
💀 Lucius has fallen! (PID: 2890) [1/3 defeated]
[G3] Entering arena (PID: 2891, HP: 800)
💀 Spartacus has fallen! (PID: 2892) [2/3 defeated]
💀 Commodus has fallen! (PID: 2891) [3/3 defeated]
[G1] Defeated (PID: 2889)

🏆 Victory! Maximus stands alone!

═══════════════════════════════════════
   🎖️  THE GODS HAVE SPOKEN!
   Champion: Maximus
═══════════════════════════════════════
```

### Tester Output
```
Checking G1_log.txt with tester file:
✅ The output of G1_log.txt is good!

Checking G2_log.txt with tester file:
✅ The output of G2_log.txt is good!

Checking G3_log.txt with tester file:
✅ The output of G3_log.txt is good!

Checking G4_log.txt with tester file:
✅ The output of G4_log.txt is good!
```


## Files
- `tournament.c` - Main coordinator that spawns gladiator processes
- `gladiator.c` - Individual gladiator process that simulates combat
- `G1.txt - G4.txt` - Gladiator configuration files
- `G1_log.txt - G4_log.txt` - Battle logs (generated)

## Input Format
Gladiator file example (`G1.txt`):
```
10000,20,2,3,4
```
- Health: 10000
- Attack: 20  
- Opponents: 2, 3, 4

## System Calls
- `fork()` - Create child processes
- `execlp()` - Execute gladiator program
- `wait()` - Wait for process termination
- File operations: `fopen()`, `fprintf()`, `fgets()`

