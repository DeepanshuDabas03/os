#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define f(i, j, k) for (i = j; i < k; i++)
int comparetostring(char const *a, char const *b)
{
	for (;; a++, b++)
	{
		int d = tolower(*a) - tolower(*b);
		if (d != 0 || !*a)
			return d;
	}
}

int main(int argc, char **array)
{

	DIR *dir;
	struct dirent *listmydirectory[2048];
	// assuming no directory will have more than 2048 files
	int runtimefile = 1;
	int a = 0, i_option_run = 0;
	runtimefile = 1;
	if(array[1]!=NULL){
		if(strcmp(array[1],"-i")==0)
		{runtimefile=2;
		i_option_run=1;}
		if(strcmp(array[1],"-a")==0){
			a=1;
			runtimefile=2;
		}
	}
	if (array[runtimefile] == NULL)
	{
		array[runtimefile] = ".";
		argc++;
	}
	for (int i = runtimefile; i < argc; i++)
	{
		if ((dir = opendir(array[i])) == NULL)
		{
			printf("ls: Error,'%s' - No such file or directory\n", array[i]);
			return 1;
		}
		errno = 0;
		int var = 0;
		int loop = 1;
		while (loop)
		{
			listmydirectory[var] = readdir(dir);
			if (listmydirectory[var] == NULL)
			{
				if (errno != 0)
				{
					printf("ls: error process wasn't succesfful. Please try again");
					return 1;
				}
				else
				{
					break;
				}
			}
			var++;
		}
		struct dirent *temp;
		for (int j = 0; j < var - 1; j++)
		{
			for (int k = j + 1; k < var; k++)
			{
				if (comparetostring(listmydirectory[j]->d_name, listmydirectory[k]->d_name) > 0)
				{
					temp = listmydirectory[k];
					listmydirectory[k] = listmydirectory[j];
					listmydirectory[j] = temp;
				}
			}
		}
		for (var = 0; listmydirectory[var] != NULL; ++var)
		{
			if ((listmydirectory[var]->d_name)[0] != '.' || a == 1)
			{
				if (i_option_run == 1)
				{
					printf("%-7ld %s\n", listmydirectory[var]->d_ino,listmydirectory[var]->d_name);
					continue;
				}
				if(a==1){
					printf("%s\n", listmydirectory[var]->d_name);
					continue;
				}
				else if((listmydirectory[var]->d_name)[0] != '.'){
					printf("%s\n", listmydirectory[var]->d_name);
				}
			}
		}
	}
	return 1;
}
