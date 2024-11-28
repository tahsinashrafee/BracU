#include <stdio.h>

int perfect_num(int num) {
    int sum = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    if (sum == num){
    return 1;
    } else{
    return 0;
    }
}

int main() {
    int start, end;
    printf("Enter Intervals: \n");
    scanf("%d", &start);
    scanf("%d", &end);
    
    printf("Perfect Numbers: \n");
    for (int i = start; i <= end; i++) {
        if (perfect_num(i)) {
            printf("%d \n", i);
        }
    }
    return 0;
}

