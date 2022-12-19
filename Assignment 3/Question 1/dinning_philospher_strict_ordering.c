#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#define ll long long
pthread_t philospher_id[5];
pthread_mutex_t forks[5];
// Each mutex variable is treated as a fork and each philospher have to grab one left and one right
void *philospher(void*pointer)
{
    int i=*(int*)pointer;
    int left = i;
    int right = (i + 1) % 5;
    if ((i + 1) % 2 != 0)
    //If its odd numbered philoshper then he will grab left fork then right fork
    {
        while (1)
        {
            printf("Philospher %d is thinking\n", i + 1);
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
            printf("Philospher %d is eating\n", i + 1);
            ll eat = 0;
            for (ll i = 0; i <(ll) pow(2,32); i++)
            {
                eat++;
            }
            pthread_mutex_unlock(&forks[left]);
            pthread_mutex_unlock(&forks[right]);
            printf("Philospher %d is done eating\n",i+1);
            sleep(1);
        }
    }
    else
    //If its even numbered philoshper then he will grab right fork then left fork
    {
        while (1)
        {
            printf("Philospher %d is thinking\n", i + 1);
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
            printf("Philospher %d is eating\n", i + 1);
            ll eat = 0;
            for (ll i = 0; i < (ll)pow(2,32); i++)
            {
                eat++;
            }
            pthread_mutex_unlock(&forks[right]);
            pthread_mutex_unlock(&forks[left]);
            printf("Philospher %d is done eating\n",i+1);
            sleep(1);
        }
    }
}
int main()
{
    int array[5];
    for(int i=0;i<5;i++){
        pthread_mutex_init(&forks[i],NULL);
        array[i]=i;
        pthread_create(&philospher_id[i], NULL,&philospher,&array[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(philospher_id[i], NULL);
    }
    return 0;
}
