#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char ** array){
	if (argc == 1){
	    printf("mkdir: missing operand\n");
		return 0;
	}
    if(strcmp(array[1],"-m")==0){
        if(argc<3){
            printf("mkdir: missing operand\n");
            return 1;
        }
        int num=0;
        for(int i=0;i<strlen(array[2]);i++){
            num=num*10+array[2][i];
        }
        for (int i = 3 ; i < argc ; i++){
		if ( mkdir(array[i], num) < 0 ){
			printf("mkdir:Can't create directory\n");
			continue;
		}
	} 
    }
    else if(strcmp(array[1],"-v")==0){
    for (int i = 2 ; i < argc ; i++){
		if ( mkdir(array[i], 0755) < 0 ){
			printf("mkdir:Can't create directory\n");
			continue;
		}
        else{
            printf("mkdir: created directory '%s'\n",array[i]);
        }
	} 
    }
    else{
	    int i = 1;
	    for (i = 1 ; i < argc ; i++){
		    if ( mkdir(array[i], 0755) < 0 ){
			    printf("mkdir:Can't create directory\n");
			    continue;
		    }
	    } 
    }

	return 0;
}
