#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
char split_on[2] = " ";

int main(int argc, char *argv[]) {
	struct sockaddr_un address;
	int sckt;
	int data_socket;
	char *prev = (char *)malloc(sizeof(char) * 200);
	sckt = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	memset(&address, 0, sizeof(address));
	address.sun_family = AF_UNIX;
	strncpy(address.sun_path, "ipc_process.socket", sizeof(address.sun_path) - 1);

	while(bind(sckt, (const struct sockaddr *) &address, sizeof(address))==-1);
    while(listen(sckt, 100)==-1);
	char mystring[200];
    data_socket = accept(sckt, NULL, NULL);
    for (int i = 0; i < 10; i++)
    {
		read(data_socket, mystring, sizeof(mystring));
        while (strcmp(prev, mystring) == 0);
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
        strcpy(mystring, max);
		write(data_socket, mystring, strlen(mystring));
    }
	close(data_socket);
	printf("Socket Connection closed\n");
	close(sckt);
	unlink("ipc_process.socket");
	return 0;
}
