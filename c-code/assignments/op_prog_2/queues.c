#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int QueueLength = 1000;
int ClockTickerSimulator = 0;

struct Process {
    char id[10];
    int entryTime;
    int instructions;
    int remainingInstructions;
};

// CreateNewProcess initializes a new process struct
struct Process CreateNewProcess(char name[], int entryTime, int instructions) {
    struct Process newProcess;
    strcpy(newProcess.id, name);
    newProcess.entryTime = entryTime;
    newProcess.instructions = instructions;
    newProcess.remainingInstructions = instructions;
    return newProcess;
}

// RemoveAndShuffle takes a queue and process position and removes it, and shuffles the process queue
int RemoveAndShuffle(struct Process Queue[], int len, int posToRemove) {
    for (int i = posToRemove; i < len; i++) {
        // Shift elements left
        if (i != len-1) {
            Queue[i] = Queue[i+1];
        }
    }

    return len-1;
}

// RemoveProcess finds the location of a process and calls for its removal
int RemoveProcess(char name[], struct Process Queue[], int len) {
    int posToRemove = -1;
    for (int i = 0; i < len; i++) {
        // Find process by name
        struct Process process = Queue[i];
        if (strcmp(process.id, name) == 0) {
            posToRemove = i;
            break;
        }
    }

    // Only remove if found
    if (posToRemove != -1) {
        return RemoveAndShuffle(Queue, len, posToRemove);
    }

    return len;
}

// TransferFromInputToWait moves processes from Input to Wait queue based on entry time
void TransferFromInputToWait(struct Process Input[], int *inputLength, struct Process Wait[], int *waitLength) {
    // Move processes that are ready (entryTime <= ClockTickerSimulator)
    int i = 0;
    // Use while loop to handle shifting correctly
    while (i < *inputLength) {
        // Check if process is ready to move
        if (Input[i].entryTime <= ClockTickerSimulator) {
            // Transfer process
            Wait[*waitLength] = Input[i];
            // Increment wait length
            (*waitLength)++;
            // Remove from input queue
            *inputLength = RemoveAndShuffle(Input, *inputLength, i);
            // Don't increment i, as the array shifted
        } else {
            // Only increment if no removal
            i++;
        }
    }
}

// Reads processes from file and places them in the Input queue
void readProcessesAndPlaceThemInTheInputQueue(struct Process InputQueue[], int *inputQLen) {
    FILE *file = fopen("processes.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    char line[50]; 
    int queueIndex = 0;
    // read file line by line
    while(fgets(line, sizeof(line), file) != NULL) {
        int next = 0;
        int indexer = 0;
        char id[10] = {0};
        char instructions[10] = {0};
        
        // parse out values
        for (int i = 0; line[i] != '\n' && line[i] != '\0'; i++) {
            if (line[i] == '-') {
                next = 1;
                indexer = 0;
                continue;
            }
            if (next == 0) {
                id[indexer] = line[i];
            } else {
                instructions[indexer] = line[i];
            }
            indexer++;
        }

        // Assign entry times: 0, 5, 10, 15...
        int entryTime = queueIndex * 5;
        struct Process newProcess = CreateNewProcess(id, entryTime, atoi(instructions));

        InputQueue[queueIndex] = newProcess;
        (*inputQLen)++;
        queueIndex++;
    }
    fclose(file);
}

// DisplayQueues prints the current state of all queues and CPU
void DisplayQueues(struct Process Input[], int iLen, struct Process Wait[], int wLen, struct Process *cpu, int busy) {
    printf("Time: %d\n", ClockTickerSimulator);
    printf("Input Queue: ");

    // Display input queue with entry times
    for(int i = 0; i < iLen; i++) {
        printf("%s(%d) ", Input[i].id, Input[i].entryTime);
    }

    printf("\nWait Queue: ");

    // Display wait queue with remaining instructions
    for(int i = 0; i < wLen; i++) {
        printf("%s(%d) ", Wait[i].id, Wait[i].remainingInstructions);
    }

    printf("\nProcessor: ");

    // Display CPU state
    if (busy) {
        printf("%s(%d)", cpu->id, cpu->remainingInstructions);
    } else {
        printf("Idle");
    }

    printf("\n--------------------------------\n");
}

int main() {
    // Initialize Queues
    int inputQLen = 0;
    int WaitQLen = 0;
    struct Process InputQueue[QueueLength];
    struct Process WaitQueue[QueueLength];
    
    // CPU State
    struct Process cpu;
    int cpuBusy = 0;
    int currentSliceInstructions = 0;

    // Load processes into Input Queue
    readProcessesAndPlaceThemInTheInputQueue(InputQueue, &inputQLen);

    // Simulation Loop
    while (inputQLen > 0 || WaitQLen > 0 || cpuBusy) {
        // 1. Move from Input to Wait
        TransferFromInputToWait(InputQueue, &inputQLen, WaitQueue, &WaitQLen);

        // 2. Schedule to CPU if idle
        if (!cpuBusy && WaitQLen > 0) {
            cpu = WaitQueue[0];
            WaitQLen = RemoveAndShuffle(WaitQueue, WaitQLen, 0);
            cpuBusy = 1;
            currentSliceInstructions = 0;
            printf("-> Loading %s to CPU\n", cpu.id);
        }

        DisplayQueues(InputQueue, inputQLen, WaitQueue, WaitQLen, &cpu, cpuBusy);

        // 3. Execute
        if (cpuBusy) {
            // Rate is 5 instructions per tick
            int instructionsToRun = 5;
            if (cpu.remainingInstructions < 5) {
                instructionsToRun = cpu.remainingInstructions;
            }

            cpu.remainingInstructions -= instructionsToRun;
            currentSliceInstructions += instructionsToRun;

            // Check completion
            if (cpu.remainingInstructions <= 0) {
                printf("-> Process %s Completed\n", cpu.id);
                cpuBusy = 0;
            } 
            // Check Process (10 instructions)
            else if (currentSliceInstructions >= 10) {
                printf("-> Process %s Expired (Moved to Wait)\n", cpu.id);
                WaitQueue[WaitQLen] = cpu;
                WaitQLen++;
                cpuBusy = 0;
            }
        }

        ClockTickerSimulator++;
    }

    return 0;
}