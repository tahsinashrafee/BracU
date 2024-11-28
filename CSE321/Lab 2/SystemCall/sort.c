#include <stdio.h>
#include <stdlib.h>
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

int main(int argc, char *argv[]) {
    int num_count = argc - 1;
    int numbers[num_count];
    for (int i = 0; i < num_count; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    sort(numbers, num_count);
    printf("Sorted in descending: ");
    for (int i = 0; i < num_count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}

