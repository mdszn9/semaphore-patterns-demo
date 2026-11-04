#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t ping_turn, pong_turn;                       /* whose turn is it? */
void *ping(void *arg) {
    for (int i = 0; i < 5; i++) { sem_wait(&ping_turn); printf("ping\n"); sem_post(&pong_turn); }
    return NULL; }
void *pong(void *arg) {
    for (int i = 0; i < 5; i++) { sem_wait(&pong_turn); printf("pong\n"); sem_post(&ping_turn); }
    return NULL; }
int main(void) {
    pthread_t a, b; sem_init(&ping_turn, 0, 1); sem_init(&pong_turn, 0, 0);   /* ping goes first */
    pthread_create(&b, NULL, pong, NULL); pthread_create(&a, NULL, ping, NULL);
    pthread_join(a, NULL); pthread_join(b, NULL); }
