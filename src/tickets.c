#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t mutex;                                      /* 1 = ticket counter is free */
int tickets = 100000, sold = 0;                   /* shared by both sellers */
void *seller(void *arg) {
    while (1) { sem_wait(&mutex);                 /* one seller at a time */
        if (tickets <= 0) { sem_post(&mutex); return NULL; }   /* sold out: release first! */
        tickets--; sold++;                        /* sell one ticket */
        sem_post(&mutex); } }
int main(void) {
    pthread_t a, b; sem_init(&mutex, 0, 1);
    pthread_create(&a, NULL, seller, NULL); pthread_create(&b, NULL, seller, NULL);
    pthread_join(a, NULL); pthread_join(b, NULL);
    printf("sold = %d, left = %d (expected 100000, 0)\n", sold, tickets); }
