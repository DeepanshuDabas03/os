#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#define ll long long
pthread_t philospher_id[5];
pthread_mutex_t forks[5];
pthread_mutex_t sauce[2];
// Each mutex variable is treated as a fork and each philospher have to grab one left and one right
void *philospher(void *pointer)
{
    int i = *(int *)pointer;
    int left = i;
    int right = (i + 1) % 5;
    if ((i + 1) % 2 != 0)
    // If its odd numbered philoshper then he will grab left fork then right fork
    {
        while (1)
        {
            printf("Philospher %d is thinking\n", i + 1);
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
            int flag = 0;
            int current_sauce;
            while (!flag)
            {
                if (pthread_mutex_trylock(&sauce[0]) == 0)
                {
                    current_sauce = 0;
                    flag = 1;
                    break;
                }
                if (pthread_mutex_trylock(&sauce[1]) == 0)
                {
                    current_sauce = 1;
                    flag = 1;
                    break;
                }
            }
            printf("Philospher %d has %d sauce bowl\n", i + 1, current_sauce + 1);
            printf("Philospher %d is eating\n", i + 1);
            ll eat = 0;
            for (ll i = 0; i < (ll)pow(2, 32); i++)
            {
                eat++;
            }
            printf("Philospher %d is done eating\n", i + 1);
            pthread_mutex_unlock(&sauce[current_sauce]);
            pthread_mutex_unlock(&forks[left]);
            pthread_mutex_unlock(&forks[right]);
            sleep(1);
        }
    }
    else
    // If its even numbered philoshper then he will grab right fork then left fork
    {
        while (1)
        {
            printf("Philospher %d is thinking\n", i + 1);
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
            int flag = 0;
            int current_sauce;
            while (!flag)
            {
                if (pthread_mutex_trylock(&sauce[1]) == 0)
                {
                    current_sauce = 1;
                    flag = 1;
                    break;
                }
                if (pthread_mutex_trylock(&sauce[0]) == 0)
                {
                    current_sauce = 0;
                    flag = 1;
                    break;
                }
            }
            printf("Philospher %d has %d sauce bowl\n", i + 1, current_sauce + 1);
            printf("Philospher %d is eating\n", i + 1);
            ll eat = 0;
            for (ll i = 0; i < (ll)pow(2, 32); i++)
            {
                eat++;
            }
            printf("Philospher %d is done eating\n", i + 1);
            pthread_mutex_unlock(&sauce[current_sauce]);
            pthread_mutex_unlock(&forks[right]);
            pthread_mutex_unlock(&forks[left]);
            sleep(1);
        }
    }
}
int main()
{
    int array[5];
    pthread_mutex_init(&sauce[0], NULL);
    pthread_mutex_init(&sauce[1], NULL);
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
        array[i] = i;
        pthread_create(&philospher_id[i], NULL, &philospher, &array[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(philospher_id[i], NULL);
    }
    return 0;
}
