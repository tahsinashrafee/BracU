#include <stdio.h>
#include <stdlib.h>

void check_odd_even(int num) {
    if (num % 2 == 0) {
        printf("%d is even\n", num);
    } else {
        printf("%d is odd\n", num);
    }
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        int num = atoi(argv[i]);
        check_odd_even(num);
    }
    return 0;
}

