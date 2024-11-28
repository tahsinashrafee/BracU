#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    char email[50];

    printf("Enter Email: ");
    scanf("%s", email);

    char* domain = strchr(email, '@');

    bool isUpdated = (domain!= NULL && strcmp(domain + 1, "sheba.xyz") == 0);

    if (isUpdated) {
        printf("Email address is okay\n");
    } else {
        printf("Email address is outdated\n");
    }

    return 0;
}

