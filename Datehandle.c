#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main() {
    time_t now=time(NULL);
    char *string_now=ctime(&now);
    printf("%s\n",string_now);
    printf("%d",now);
return 0;
}cd
