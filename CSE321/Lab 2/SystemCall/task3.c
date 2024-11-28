#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int count = 0;

    int a = fork();
    int b = fork();
    int c = fork();

    if (a == 0 || b == 0 || c == 0) {
        if (getpid() % 2 != 0) {
            fork();
        }
        exit(0);
    }

    wait(NULL);
    count++;

    if (a > 0 && b > 0 && c > 0) {
        printf("Processes Created: %d\n", count);
    }

    return 0;
}

