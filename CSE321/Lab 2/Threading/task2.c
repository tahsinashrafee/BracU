#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_no = 0;
int count = 1;

void *block(void *ptr) {
    for (int i = 0; i < 5; i++) {
        printf("Thread %d prints %d\n", thread_no, count);
        count++;
    }
    return NULL;
}

int main() {
    while (thread_no <= 5) {
        pthread_t thread;
        pthread_create(&thread, NULL, block, NULL);
        pthread_join(thread, NULL);
        thread_no++;
    }
    return 0;
}

