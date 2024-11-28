#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int var = 0;

void* block(void* arg) {
    var++;
    return NULL;
}

int main() {
    pthread_t threads[5];
    
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, block, NULL);
        pthread_join(threads[i], NULL);
        printf("thread- %d running\n", i + 1);
        printf("thread- %d closed\n", i + 1);
    }
    
    return 0;
}

