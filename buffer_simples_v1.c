#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM_BUFFER 5
#define NUM_IT 20

int buffer[TAM_BUFFER];
int in = 0, out = 0;
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* produtor(void* arg) {
    for (int i = 0; i < NUM_IT; i++) {
        pthread_mutex_lock(&mutex);
        buffer[in] = i;
        printf("Produzido: %d em %d\n", i, in);
        in = (in + 1) % TAM_BUFFER;
        count++;
        usleep(rand() % 100000);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* consumidor(void* arg) {
    for (int i = 0; i < NUM_IT; i++) {
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumido: %d de %d\n", item, out);
        out = (out + 1) % TAM_BUFFER;
        count--;
        usleep(rand() % 150000);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, produtor, NULL);
    pthread_create(&t2, NULL, consumidor, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_exit(NULL);
    return 0;
}
