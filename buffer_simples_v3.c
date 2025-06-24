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

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_prod = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_cons = PTHREAD_COND_INITIALIZER;

void* produtor(void* arg) {
    for (int i = 0; i < NUM_IT; i++) {
        pthread_mutex_lock(&lock);
        while(count == TAM_BUFFER)
            pthread_cond_wait(&cond_prod, &lock);
        buffer[in] = i;
        printf("Produzido: %d em %d\n", i, in);
        in = (in + 1) % TAM_BUFFER;
        count++;
        pthread_cond_signal(&cond_cons);
        pthread_mutex_unlock(&lock);
        usleep(rand() % 100000);
        
    }
    return NULL;
}

void* consumidor(void* arg) {
    for (int i = 0; i < NUM_IT; i++) {
        pthread_mutex_lock(&lock);
        while(count == 0)
            pthread_cond_wait(&cond_cons, &lock);
        int item = buffer[out];
        printf("Consumido: %d de %d\n", item, out);
        out = (out + 1) % TAM_BUFFER;
        count--;
        pthread_cond_signal(&cond_prod);
        pthread_mutex_unlock(&lock);
        usleep(rand() % 150000);
        
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
