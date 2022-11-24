#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>
#include <time.h>
#define BILLION 1000000000L
int main()
{
    struct timespec stop;
    struct sched_param pa1, pa2, pa3;
    struct timespec start1, start2, start3;
    clock_gettime(CLOCK_REALTIME, &start1);
    double t_t1, t_t2, t_t3;
    pid_t p1, p2, p3;
    p1 = fork();
    if (p1 == 0)
    {
        pa1.sched_priority = 0;
        if(sched_setscheduler(p1, SCHED_OTHER, &pa1)!=0)
        {
            perror("");
        }
        char commandpath[100];
        strcpy(commandpath, "/home/deepanshu/Desktop/Assignment2/script1.sh");
        execl(commandpath, NULL);
        perror("");
    }
    clock_gettime(CLOCK_REALTIME, &start2);
    p2 = fork();
    if (p2 == 0)
    {
        pa2.sched_priority = 1;
        if(sched_setscheduler(p2, SCHED_RR, &pa2)!=0)
        {
            perror("");
        }
        char commandpath[100];
        strcpy(commandpath, "/home/deepanshu/Desktop/Assignment2/script2.sh");
        execl(commandpath, NULL);
        perror("");
    }
    clock_gettime(CLOCK_REALTIME, &start3);
    p3 = fork();
    if (p3 == 0)
    {
        pa3.sched_priority = 1;
        if(sched_setscheduler(p3, SCHED_FIFO, &pa3)!=0)
        {
            perror("");
        }
        char commandpath[100];
        strcpy(commandpath, "/home/deepanshu/Desktop/Assignment2/script3.sh");
        execl(commandpath, NULL);
        perror("");
    }
    int num;
    pid_t a = waitpid(-1, NULL, 0);
    while (a)
    {
        if (a == p3)
        {
            clock_gettime(CLOCK_REALTIME, &stop);
            t_t3 = (stop.tv_sec - start3.tv_sec + (double)(stop.tv_nsec - start3.tv_nsec) / (double)BILLION);
        }
        else if (a == p2)
        {
            clock_gettime(CLOCK_REALTIME, &stop);
            t_t2 = (stop.tv_sec - start2.tv_sec + (double)(stop.tv_nsec - start2.tv_nsec) / (double)BILLION);
        }
        else if (a == p1)
        {
            clock_gettime(CLOCK_REALTIME, &stop);
            t_t1 = (stop.tv_sec - start1.tv_sec + (double)(stop.tv_nsec - start1.tv_nsec) / (double)BILLION);
        }
        else
        {
            break;
        }
        a = waitpid(-1, NULL, 0);
    }
    FILE * fp;

    fp = fopen ("output_q1_2.txt", "a");
    fprintf(fp,"%f\n", t_t1);
    fprintf(fp,"%f\n", t_t2);
    fprintf(fp,"%f\n", t_t3);
    fclose(fp);
    return 0;
}
