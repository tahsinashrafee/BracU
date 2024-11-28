#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>

struct shared {
    char sel[100];
    int b;
};
int main() {
    int p_pipe[2];
    pid_t child_pid;
    char buffer[19];
    struct shared *shared_memory;
    int shared_memory_id;
    shared_memory_id = shmget(IPC_PRIVATE, sizeof(struct shared), IPC_CREAT | 0666);
    if (shared_memory_id < 0) {
        perror("Error");
        exit(1);
    }
    shared_memory = (struct shared *)shmat(shared_memory_id, NULL, 0);
    if (shared_memory == (struct shared *)-1) {
        perror("Error");
        exit(1);
    }
    shared_memory->b = 1000;

    if (pipe(p_pipe) == -1) { 
        perror("Error");
        exit(1);
    }
    printf("Provide Your Input From Given Options:\n1. Type a to Add Money\n2. Type w to Withdraw Money\n3. Type c to Check Balance\n");
    scanf("%s", shared_memory->sel);
    printf("Your selection: %s\n", shared_memory->sel);

    child_pid = fork();
    if (child_pid == -1) {
        perror("Error");
        exit(1);
    }
    if (child_pid == 0) {
        int amount;
        if (shared_memory->sel[0] == 'a') {
            printf("Enter amount to be added:\n");
            scanf("%d", &amount);
            if (amount > 0) {
                shared_memory->b += amount;
                printf("Balance added successfully\nUpdated balance after addition:\n%d\n", shared_memory->b);
            } else {
                printf("Adding failed, Invalid amount\n");
            }
        } else if (shared_memory->sel[0] == 'w') {
            printf("Enter amount to be withdrawn:\n");
            scanf("%d", &amount);
            if (amount > 0 && amount <= shared_memory->b) {
                shared_memory->b -= amount;
                printf("Balance withdrawn successfully\nUpdated balance after withdrawal:\n%d\n", shared_memory->b);
            } else {
                printf("Withdrawal failed, Invalid amount\n");
            }
        } else if (shared_memory->sel[0] == 'c') {
            printf("Your current balance is:\n%d\n", shared_memory->b);
        } else {
            printf("Invalid selection\n");
        }
        write(p_pipe[1], "Thank you for using", strlen("Thank you for using"));
        close(p_pipe[0]);
        close(p_pipe[1]);
        exit(0);
    } else {
        wait(NULL);
        close(p_pipe[1]);
        read(p_pipe[0], buffer, sizeof(buffer));
        printf("%s\n", buffer);
        close(p_pipe[0]);
        shmdt((void *) shared_memory);
        shmctl(shared_memory_id, IPC_RMID, NULL);
    }
    return 0;
}

