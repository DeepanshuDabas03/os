#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <unistd.h>
#define ll long long
sem_t forks[5];
pthread_t philospher_id[5];
int val1,val2;
void *philospher(void *pointer)
{
    int i = *(int *)pointer;
    int left = i;
    int right = (i + 1) % 5;

    while (1)
    {
        printf("Philospher %d is thinking\n", i + 1);
        sem_getvalue(&forks[left],&val1);
        sem_getvalue(&forks[right],&val2);
        while(val1==0 || val2==0 ){
            sem_getvalue(&forks[left],&val1);
            sem_getvalue(&forks[right],&val2);
        }
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);
        printf("Philospher %d is eating\n", i + 1);
        ll eat = 0;
        for (ll i = 0; i < (ll)pow(2, 32); i++)
        {
            eat++;
        }
        sem_post(&forks[left]);
        sem_post(&forks[right]);
         printf("Philospher %d is done eating\n",i+1);
        sleep(1);
    }
}
int main()
{
    int array[5];
    for(int i=0;i<5;i++){
        sem_init(&forks[i],0,1);
        array[i]=i;
        pthread_create(&philospher_id[i], NULL,&philospher,&array[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(philospher_id[i], NULL);
    }
    return 0;
}
