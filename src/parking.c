#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t spots;                                      /* counts free parking spots */
void *car(void *arg) {
    sem_wait(&spots);                             /* take a spot; blocks if lot is full */
    printf("Car %ld parks\n", (long)arg); sleep(1);
    printf("Car %ld leaves\n", (long)arg);
    sem_post(&spots);                             /* free the spot */
    return NULL; }
int main(void) {
    pthread_t t[6]; sem_init(&spots, 0, 3);       /* lot has 3 spots */
    for (long i = 0; i < 6; i++) pthread_create(&t[i], NULL, car, (void *)i);
    for (int i = 0; i < 6; i++) pthread_join(t[i], NULL); }
