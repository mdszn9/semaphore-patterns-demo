#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t alice_here, bob_here;                       /* 0 = not arrived yet */
void *alice(void *arg) { printf("Alice arrives\n"); sem_post(&alice_here);  /* announce */
                         sem_wait(&bob_here);                               /* wait for Bob */
                         printf("Alice leaves\n"); return NULL; }
void *bob(void *arg)   { sleep(1); printf("Bob arrives\n"); sem_post(&bob_here);
                         sem_wait(&alice_here);
                         printf("Bob leaves\n"); return NULL; }
int main(void) {
    pthread_t a, b; sem_init(&alice_here, 0, 0); sem_init(&bob_here, 0, 0);
    pthread_create(&a, NULL, alice, NULL); pthread_create(&b, NULL, bob, NULL);
    pthread_join(a, NULL); pthread_join(b, NULL); }
