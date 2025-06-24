#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define TAM_BUFFER 5
#define NUM_IT 20

int buffer[TAM_BUFFER];
int in = 0, out = 0;
int count = 0;

sem_t semaforo;

void* produtor(void* arg) {
    for (int i = 0; i < NUM_IT; i++) {
        sem_wait(&semaforo);
        buffer[in] = i;
        printf("Produzido: %d em %d\n", i, in);
        in = (in + 1) % TAM_BUFFER;
        count++;
        usleep(rand() % 100000);
        sem_post(&semaforo);
    }
    return NULL;
}

void* consumidor(void* arg) {
    for (int i = 0; i < NUM_IT; i++) {
        sem_wait(&semaforo);
        int item = buffer[out];
        printf("Consumido: %d de %d\n", item, out);
        out = (out + 1) % TAM_BUFFER;
        count--;
        usleep(rand() % 150000);
        sem_post(&semaforo);
    }
    return NULL;
}

int main() {
    sem_init(&semaforo, 0, 1);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, produtor, NULL);
    pthread_create(&t2, NULL, consumidor, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_exit(NULL);
    return 0;
}
