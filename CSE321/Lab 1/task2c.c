#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    char password[30];

    printf("Enter Your Password: ");
    scanf("%s", password);

    bool lowercase = false; 
    bool uppercase = false; 
    bool digit = false; 
    bool special_char = false; 

    for (int i = 0; i < strlen(password); i++) {
        char c_char = password[i];

        if (c_char >= 'a' && c_char  <= 'z') {
            lowercase = true;
        } else if (c_char >= 'A' && c_char <= 'Z') {
            uppercase = true;
        } else if (c_char >= '0' && c_char <= '9') {
            digit = true; 
        } else if (c_char == '_' || c_char == ',' || c_char == '$' || c_char == '#' || c_char == '@') {
            special_char = true;
        }
    }

    if (!lowercase) {
        printf("Lowercase character missing\n");
    }
    if (!uppercase) {
        printf("Uppercase character missing\n");
    }
    if (!digit) {
        printf("Digit missing\n");
    }
    if (!special_char) {
        printf("Special character missing\n");
    }

    if (lowercase && uppercase && digit && special_char) {
        printf("OK\n");
    }

    return 0;
}

