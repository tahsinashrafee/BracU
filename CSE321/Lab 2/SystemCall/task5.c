#include <stdio.h> 
#include <sys/wait.h>  
#include <stdlib.h>  
#include <unistd.h>

int main() {
    pid_t parent_pid = getpid();
    printf("Parent process ID : %d\n", parent_pid);
    pid_t child_pid = fork();
    if (child_pid == 0) { 
        printf("Child process ID : %d\n", getpid());
        for (int i = 0; i < 3; i++) {
            pid_t grandchild_pid = fork();
            if (grandchild_pid == 0) {
                printf("Grandchild process ID : %d\n", getpid());
                exit(0);
            } else if (grandchild_pid > 0) {
                wait(NULL);
            }
        }
    } else if (child_pid > 0) {
        wait(NULL);
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    return 0;
}

