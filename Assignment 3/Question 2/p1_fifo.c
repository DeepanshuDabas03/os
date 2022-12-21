#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
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
    char *fifo_1 = "/tmp/fifo_1";
    
    mkfifo(fifo_1, 0666);
    char *mys = (char *)malloc(sizeof(char) * 200);
    char idx[3];
    for (int i = 0; i < 50; i += 5)
    {
        int fp,fp2;
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
            if(j!=i+4)
                strcat(mys, " ");
        }
        fp = open(fifo_1, O_WRONLY);
        write(fp, mys, strlen(mys));
        close(fp);        
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
        
        char arr[3];
        fp2 = open(fifo_1, O_RDONLY);
        read(fp2, arr, sizeof(arr));
        close(fp2);
        while (strcmp(arr, a) != 0){
            read(fp2, arr, sizeof(arr));
        }
        printf("Recieved Index: %s\n", arr);  
    }
    
    return 0;
}
