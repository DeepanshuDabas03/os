#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
char split_on[2] = " ";
int main()
{
    char *prev = (char *)malloc(sizeof(char) * 200);
    char *fifo_1 = "/tmp/fifo_1";   
    mkfifo(fifo_1, 0666);
    char str[100], str2[80];
    char mystring[500];
    for (int i = 0; i < 10; i++)
    {
        int fp,fp2;
        fp = open(fifo_1, O_RDONLY);
        read(fp, str, sizeof(str));
         close(fp);
        strcpy(mystring, str);
        char *temp = strtok(mystring, split_on);
        char **temp_array = malloc(sizeof(char *) * 200);
        int idx = 0;
        while (temp != NULL)
        {
            temp_array[idx] = temp;
            ++idx;
            temp = strtok(NULL, split_on);
            
        }
        char max[3];
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
        strcpy(str2, max);
        fp2 = open(fifo_1, O_WRONLY);
        write(fp2, str2, strlen(str2));
        close(fp2);
    }
    
   
    return 0;
}
