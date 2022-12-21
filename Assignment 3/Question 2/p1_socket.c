#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
int main(int argc, char *argv[])
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
	struct sockaddr_un addr;
	int ret;
	int data_socket;
	data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, "ipc_process.socket", sizeof(addr.sun_path) - 1);
	while(connect(data_socket, (const struct sockaddr *)&addr, sizeof(addr))==-1);
	// connect(data_socket, (const struct sockaddr *)&addr, sizeof(addr));
	char *mys = (char *)malloc(sizeof(char) * 200);
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
            if(j!=i+4)
                strcat(mys, " ");
        }
		write(data_socket, mys, strlen(mys));
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
		read(data_socket, arr, sizeof(arr));
		while (strcmp(arr, a) != 0){
            read(data_socket, arr, sizeof(arr));
        }
        printf("Recieved Index: %s\n", arr);  
	}
	return 0;
}
