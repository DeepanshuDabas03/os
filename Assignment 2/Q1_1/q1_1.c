#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <time.h>
#define BILLION 1000000000L
int k = 0;
pthread_t thread_id, thread_id2, thread_id1;
int array[10] = {5, 10, 20, 30, 40, 50, 60, 70, 80, 90};
int nice_value[10] = {-20, -16, -12, -10, -5, 0, 5, 10, 15, 19};
void *countA()
{
    FILE * fp;

    fp = fopen ("ThreadA_runtimes.txt", "a");
    struct sched_param p3;
    pid_t tt = syscall(SYS_gettid);
    p3.sched_priority = 0;
    if (pthread_setschedparam(thread_id, SCHED_OTHER, &p3) != 0)
    {
        perror("");
    }
    long long int count = 0;
    struct timespec start, stop;
    double t_t;
    int ret = setpriority(PRIO_PROCESS, tt, nice_value[k]);
    if (ret != 0)
    {
        perror("");
    }
    clock_gettime(CLOCK_REALTIME, &start);
    for (long long int i = 1; i < pow(2, 32); i++)
    {
        count++;
    }
    clock_gettime(CLOCK_REALTIME, &stop);
    t_t = (stop.tv_sec - start.tv_sec + (double)(stop.tv_nsec - start.tv_nsec) / (double)BILLION);
    fprintf(fp,"%f \n",t_t);
    fclose(fp);
}
void *countB()
{
    FILE * fp;

    fp = fopen ("ThreadB_runtimes.txt", "a");
    struct sched_param p2;
    p2.sched_priority = array[k];
    if (pthread_setschedparam(thread_id2, SCHED_RR, &p2) != 0)
    {
        perror("");
    }
    long long int count = 0;
    struct timespec start, stop;
    double t_t;
    clock_gettime(CLOCK_REALTIME, &start);
    for (long long int i = 1; i < pow(2, 32); i++)
    {
        count++;
    }
    clock_gettime(CLOCK_REALTIME, &stop);
    t_t = (stop.tv_sec - start.tv_sec + (double)(stop.tv_nsec - start.tv_nsec) / (double)BILLION);
    fprintf(fp,"%f \n",t_t);
    fclose(fp);
}
void *countC()
{
    FILE * fp;

    fp = fopen ("ThreadC_runtimes.txt", "a");
    struct sched_param p1;
    p1.sched_priority = array[k];
    if (pthread_setschedparam(thread_id1, SCHED_FIFO, &p1) != 0)
    {
        perror("");
    }
    long long int count = 0;
    struct timespec start, stop;
    double t_t;
    clock_gettime(CLOCK_REALTIME, &start);
    for (long long int i = 1; i < pow(2, 32); i++)
    {
        count++;
    }
    clock_gettime(CLOCK_REALTIME, &stop);
    t_t = (stop.tv_sec - start.tv_sec + (double)(stop.tv_nsec - start.tv_nsec) / (double)BILLION);
    fprintf(fp,"%f \n",t_t);
    fclose(fp);
}
int main()
{
    while (k < 10)
    {
        pthread_create(&thread_id, NULL, countA, NULL);
        pthread_create(&thread_id2, NULL, countB, NULL);
        pthread_create(&thread_id1, NULL, countC, NULL);
        pthread_join(thread_id, NULL);
        pthread_join(thread_id1, NULL);
        pthread_join(thread_id2, NULL);
        ++k;
    }
    return 0;
}
