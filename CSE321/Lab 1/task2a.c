#include <stdio.h>

int main() {
    int num1, num2, result;
    printf("Enter 1st number: ");
    scanf("%d", &num1);
    printf("Enter 2nd number: ");
    scanf("%d", &num2);

    if (num1> num2){
        result= num1-num2;

    }
    else if ( num1< num2){
       result = num1+num2;
    }
    else {
        result = num1*num2;
    }
    printf("Result: %d\n", result);

    return 0;
}

