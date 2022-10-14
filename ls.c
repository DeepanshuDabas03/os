#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <ctype.h>	
#define f(i,j,k) for(i=j;i<k;i++)
int comparetostring(char const *a, char const *b)
{
	for (;; a++, b++){
		int d = tolower(*a) - tolower(*b);
		if (d != 0 || !*a)
			return d;
	}
}

int main(int argc, char ** array){

	DIR * dir;
	struct dirent * listmydirectory[2048];
    //assuming no directory will have more than 2048 files
	int runtimefile = 1;
	int a = 0,i_option_run = 0;
	runtimefile = 1;
	if ( array[1] != NULL && array[1][0] == '-'  ){
		int i = 0;
		for ( i = 1 ; i < strlen(array[1]) ; i++ ){
			
			if ( array[1][i] == 'a' ){
				a = 1;
			}
			else if ( array[1][i] == 'i' ){
				i_option_run = 1;
			}
			else{
				printf("ls: invalid option -- '%s'\n",array[1][i]);
				return 0;
			}
		}
		runtimefile = 2;
	}
	if ( array[runtimefile] == NULL ){
		array[runtimefile] = ".";
		argc++;
	}
	for (int i = runtimefile ; i < argc ; i++ ){
		if ( (dir = opendir(array[i])) == NULL ){
			printf("ls: Error,'%s' - No such file or runtimefile\n", array[i]);
			return 0;
		}
		errno = 0;	
		int var = 0;
		while ( 1 ){
			listmydirectory[var] = readdir(dir);
			if (listmydirectory[var] == NULL){
				if (errno != 0){
					printf("ls: error process wasn't succesfful. Please try again");
					return 0;
				}
				else{	
					break;
				}
			}
			var++;
		}
		struct dirent * temp;
		for (int j = 0 ; j < var-1 ; j++ ){
			for ( int k = j+1 ; k < var ; k++ ){
				if ( comparetostring(listmydirectory[j]->d_name, listmydirectory[k]->d_name) > 0 ){
					temp = listmydirectory[k];
					listmydirectory[k] = listmydirectory[j];
					listmydirectory[j] = temp;
				}
			}
		} 		
			for (var = 0 ; listmydirectory[var] != NULL ; var++){
				if ( (listmydirectory[var]->d_name)[0] != '.' || a == 1 ){
					if ( i_option_run == 1 ){
						printf("%-8ld ", listmydirectory[var]->d_ino);
				}
				printf("%s\n", listmydirectory[var]->d_name);
			}
		}
	}
	return 1;
}
