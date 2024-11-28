#include <stdio.h>

int Palindrome(char* str) {
    char* sp = str;
    char* ep = str;
    while (*ep) {
        ++ep;
    }
    --ep; 

    while (sp < ep) {
        if (*sp++ != *ep--) {
            return 0;
        }
    }

    return 1; 
}

int main() {
    char input[50];

    printf("Enter string: ");
    scanf("%s", input);

    if (Palindrome(input)) {
        printf("Palindrome\n");
    } else {
        printf("Not a palindrome\n");
    }

    return 0;
}

