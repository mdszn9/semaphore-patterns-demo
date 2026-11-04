#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t done;                                       /* 0 = A has not finished yet */
void *A(void *arg) { sleep(1); printf("A: boil water\n");
                     sem_post(&done); return NULL; }    /* signal: A is done */
void *B(void *arg) { sem_wait(&done);                   /* wait for A's signal */
                     printf("B: pour tea\n"); return NULL; }
int main(void) {
    pthread_t a, b; sem_init(&done, 0, 0);
    pthread_create(&b, NULL, B, NULL); pthread_create(&a, NULL, A, NULL);
    pthread_join(a, NULL); pthread_join(b, NULL); }
