#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

char split_on[2] = " ";
int main()
{
    char *prev = (char *)malloc(sizeof(char) * 200);
    key_t key = ftok("shmfile", 65);
    int count = 0;

    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, (void *)0, 0);
    char mystring[200];
    for (int i = 0; i < 10; i++)
    {
        while (strcmp(prev, str) == 0);
        strcpy(mystring, str);
        char *temp = strtok(mystring, split_on);
        char **temp_array = malloc(sizeof(char *) * 100);
        int idx = 0;
        while (temp != NULL)
        {
            temp_array[idx] = temp;
            ++idx;
            temp = strtok(NULL, split_on);
        }
        char *max = (char *)malloc(sizeof(char) * 3);
        max[0] = '0';
        max[1] = '\0';
        for (int j = 0; j < 10; j++)
        {
            if (j % 2 == 0)
            {
                printf("Recieved String index :%s, ", temp_array[j]);
                int num = (int)(max[0] - '0');
                int num2 = (int)(temp_array[j][0] - '0');
                if (max[1] != '\0')
                {
                    num *= 10;
                    num += (int)(max[1] - '0');
                }
                if (temp_array[j][1] != '\0')
                {
                    num2 *= 10;
                    num2 += (int)(temp_array[j][1] - '0');
                    if (num2 > num)
                    {
                        max[0] = temp_array[j][0];
                        max[1] = temp_array[j][1];
                        max[2] = '\0';
                    }
                }
                else
                {
                    if (num2 > num)
                    {
                        max[0] = temp_array[j][0];
                        max[1] = '\0';
                    }
                }
            }

            else
                printf("Recieved String: %s\n", temp_array[j]);
        }
        strcpy(prev, max);
        strcpy(str, max);
    }
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
