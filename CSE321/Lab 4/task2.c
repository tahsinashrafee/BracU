#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define MaxCrops 5
#define warehouseSize 5

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
char crops[warehouseSize] = {'R', 'W', 'P', 'S', 'M'};
char warehouse[warehouseSize] = {'N', 'N', 'N', 'N', 'N'};
pthread_mutex_t mutex;

void *Farmer(void *farmer_id) {
    int id = *((int *)farmer_id);

    for (int x = 0; x < MaxCrops; x++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        warehouse[in] = crops[id - 1];
        printf("Farmer %d: Insert crops %c at %d\n", id, warehouse[in], in);
        in = (in + 1) % warehouseSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }

    printf("\nFarmer: %d", id);
    for (int y = 0; y < warehouseSize; y++) {
        printf("%c", warehouse[y]);
    }

    printf("\n");
    return NULL;
}

void *ShopOwner(void *shop_owner_id) {
    int id = *((int *)shop_owner_id);

    for (int x = 0; x < MaxCrops; x++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        warehouse[out] = 'N';
        printf("Shop owner %d: Remove crops %c from %d\n", id, warehouse[out], out);
        out = (out + 1) % warehouseSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }

    printf("\nShop owner %d: ", id);
    for (int y = 0; y < warehouseSize; y++) {
        printf("%c", warehouse[y]);
    }
    
    printf("\n");
    return NULL;
}

int main() {
    pthread_t farmer_threads[5], shop_owner_threads[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, warehouseSize);
    sem_init(&full, 0, 0);

    int farmer_ids[5] = {1, 2, 3, 4, 5};
    int shop_owner_ids[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        pthread_create(&farmer_threads[i], NULL, Farmer, (void *)&farmer_ids[i]);
        pthread_create(&shop_owner_threads[i], NULL, ShopOwner, (void *)&shop_owner_ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(farmer_threads[i], NULL);
        pthread_join(shop_owner_threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

