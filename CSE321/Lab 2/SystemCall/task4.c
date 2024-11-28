#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void check_odd_even(int num) {
    if (num % 2 == 0) {
        printf("%d is even\n", num);
    } else {
        printf("%d is odd\n", num);
    }
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main() {
    int numbers[] = {7, 2, 4, 8, 3};

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        int n = sizeof(numbers) / sizeof(numbers[0]);
        sort(numbers, n);

        printf("Sorted in descending : ");
        for (int i = 0; i < n; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");

        exit(EXIT_SUCCESS);
    } else { 
        wait(NULL);
        int n = sizeof(numbers) / sizeof(numbers[0]);
        for (int i = 0; i < n; i++) {
            check_odd_even(numbers[i]);
        }
    }

    return 0;
}

