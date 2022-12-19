#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    char **array = malloc(sizeof(char *) * 1000);
    for (int i = 0; i < 50; i++)
    {
        char *new = (char *)malloc(sizeof(char) * 6);
        for (int j = 0; j < 5; j++)
        {
            new[j] = ((rand()) % 26) + 65;
        }
        array[i] = new;
    }
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, (void *)0, 0);
    char *mys = (char *)malloc(sizeof(char) * 200);
    ;
    char idx[3];
    for (int i = 0; i < 50; i += 5)
    {
        if (i > 9)
        {
            idx[0] = (char)(i / 10) + '0';
            idx[1] = (char)(i % 10) + '0';
            idx[2] = '\0';
        }
        else
        {
            idx[0] = (char)(i) + '0';
            idx[1] = '\0';
        }
        strcpy(mys, idx);
        strcat(mys, " ");
        strcat(mys, array[i]);
        strcat(mys, " ");
        for (int j = i + 1; j < i + 5; j++)
        {
            if (i > 9)
            {
                idx[0] = (char)(j / 10) + '0';
                idx[1] = (char)(j % 10) + '0';
                idx[2] = '\0';
            }
            else
            {
                idx[0] = (char)(j) + '0';
                idx[1] = '\0';
            }
            strcat(mys, idx);
            strcat(mys, " ");
            strcat(mys, array[j]);
            strcat(mys, " ");
        }
        strcat(mys, "\0");

        strcpy(str, mys);
        char a[3];
        if(i+4<10){
            a[0] = (char)(i + 4) + '0';
            a[1] = '\0';
        }
        else{
            a[0] = (char)(i + 4) / 10 + '0';
            a[1] = (char)(i + 4) % 10 + '0';
            a[2] = '\0';
        }
        while (strcmp(str, a) != 0);
    }
    shmdt(str);
    return 0;
}
