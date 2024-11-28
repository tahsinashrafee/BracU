#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define MAX 10
#define BUFLEN 6
#define NUMTHREAD 2

char buffer[BUFLEN];
char source[BUFLEN] = "abcdef";
int buflen = 0;
int pCount = 0;
int cCount = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

void *consumer(void *id);
void *producer(void *id);

int main() {
    pthread_t thread[NUMTHREAD];
    int thread_id[NUMTHREAD] = {0, 1};

    buflen = strlen(source);

    // Create consumer and producer threads
    pthread_create(&thread[0], NULL, producer, (void *)&thread_id[0]);
    pthread_create(&thread[1], NULL, consumer, (void *)&thread_id[1]);

    // Wait for threads to finish
    for (int i = 0; i < NUMTHREAD; i++) {
        pthread_join(thread[i], NULL);
    }

    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&nonEmpty);
    pthread_cond_destroy(&full);

    return 0;
}

void *producer(void *id) {
    for (int i = 0; i < MAX; i++) {
        pthread_mutex_lock(&count_mutex);
        while (pCount >= BUFLEN) {
            pthread_cond_wait(&full, &count_mutex);
        }

        buffer[pCount] = source[pCount % buflen];
        printf("%d produced %c by Thread %d\n", i, buffer[pCount], *(int *)id);
        pCount++;
        cCount++;
        pthread_cond_signal(&nonEmpty);
        pthread_mutex_unlock(&count_mutex);
    }

    pthread_exit(NULL);
}

void *consumer(void *id) {
    for (int i = 0; i < MAX; i++) {
        pthread_mutex_lock(&count_mutex);
        while (cCount <= 0) {
            pthread_cond_wait(&nonEmpty, &count_mutex);
        }

        printf("%d consumed %c by Thread %d\n", i, buffer[pCount - 1], *(int *)id);
        pCount--;
        cCount--;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&count_mutex);
    }

    pthread_exit(NULL);
}

