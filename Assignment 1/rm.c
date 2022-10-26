#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc,char **array){
    if(argc<2){
        printf("rm: Error.Atleast one option required\n");
        return 0;
    }
    if(strcmp(array[1],"-f")==0){
        if(argc<3){
            printf("rm: Atleast one argument required\n");
            return 0;
        }
        else{
            for (int i = 2 ; i < argc ; i++ ){
                struct stat dirstat;
                if (stat(array[i], &dirstat) < 0 ){	
			        continue;
		        }
                if ( unlink(array[i]) < 0 ){
			        continue; 
		        }
            }
        }
    }
    else if(strcmp(array[1],"-i")==0){
        if(argc<3){
            printf("rm: Atleast one argument required\n");
        }
        else{
            for (int i = 2 ; i < argc ; i++ ){
                struct stat dirstat;
                if (stat(array[i], &dirstat) < 0 ){	
			    printf("rm: cannot remove '%s': No such file or directory\n", array[i]);
			    continue;
		        }
                printf("rm: remove regular file '%s'?(Enter Y for Yes and N for No)",array[i]);
                char option;
                option=getchar();
                if(option=='N'){
                    return 1;
                }
                else if(option=='Y'){
                    if ( unlink(array[i]) < 0 ){
			            printf("rm: error can't remove file\n");
		    }
                }
            }
        }
    }
    else{
	    int i = 1;	
	    for ( i = 1 ; i < argc ; i++ ){
		    struct stat dirstat;
		    if (stat(array[i], &dirstat) < 0 ){	
			    printf("rm: cannot remove '%s': No such file or directory\n", array[i]);
			continue;
		}

		if ( unlink(array[i]) < 0 ){
			printf("rm: error can't remove file\n");
		    }
	    }
    }
    return 1;
}
