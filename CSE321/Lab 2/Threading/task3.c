#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

char name1[30];
char name2[30];
char name3[30];
int thread_no;
int char_sum1, char_sum2, char_sum3;

void *block(void *ptr) {
    char user_input[30];

    if (thread_no == 1) {
        printf("Enter first name: ");
        scanf("%s", user_input);
        char_sum1 = 0;
        for (int i = 0; user_input[i] != '\0'; i++) {
            char_sum1 += user_input[i];
        }
        strcpy(name1, user_input);
        
    } else if (thread_no == 2) {
        printf("Enter second name: ");
        scanf("%s", user_input);
        char_sum2 = 0;
        for (int i = 0; user_input[i] != '\0'; i++) {
            char_sum2 += user_input[i];
        }
        strcpy(name2, user_input);
        
    } else if (thread_no == 3) {
        printf("Enter third name: ");
        scanf("%s", user_input);
        char_sum3 = 0;
        for (int i = 0; user_input[i] != '\0'; i++) {
            char_sum3 += user_input[i];
        }
        strcpy(name3, user_input);
    }

    return NULL;
}

int main() {
    thread_no = 1;
    while (thread_no <= 3) {
        pthread_t thr;
        pthread_create(&thr, NULL, block, NULL);
        pthread_join(thr, NULL);
        thread_no++;
    }

    if (char_sum1 == char_sum2 && char_sum1 == char_sum3) {
        printf("Youreka\n");
    } else if ((char_sum1 != char_sum2 && char_sum1 == char_sum3) || 
               (char_sum1 == char_sum2 && char_sum1 != char_sum3) || 
               (char_sum2 == char_sum3 && char_sum2 != char_sum1)) {
        printf("Miracle\n");
    } else {
        printf("Hasta la vista\n");
    }

    return 0;
}

