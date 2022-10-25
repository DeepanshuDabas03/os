#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc,char **array) {
    if(array[1]==NULL){
        time_t now=time(NULL);
        char *string_now=ctime(&now);
        printf("%s",string_now);
    }
    else if(strcmp(array[1],"-u")==0){
        time_t t=time(&t);
		struct tm *utc=gmtime(&t);
		if(utc==NULL){
			printf("date:error unable to handle process right now \n");
            return 1;
		}
		printf("Time in UTC : %s",asctime(utc));
    }
    else if(strcmp(array[1],"-r")==0){
        struct stat attr;
        if(argc<3){
            printf("date: option requires an argument -- '%s'\n",array[1]);
            return 1;
        }
        stat(array[2], &attr);
        printf("Last modified time: %s", ctime(&attr.st_mtime));
    }
    else{
        printf("date: error invalid option\n");
    }
return 1;
}
