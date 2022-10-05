#include <stdio.h>	
#include <stdlib.h>    
#include <unistd.h>     
#include <sys/wait.h>
#include <fcntl.h>
#define totalcommands 4
#define cwd(PWD) getcwd(PWD, sizeof(PWD))
char pwd[2048];
char commands[2048];

char *command[]={"cd","echo","pwd","exit"};
//defining 2d array to store our commands. 
int cd(char **arr){
    if(arr[1]==NULL){
        //if no arrguments are specified we need to change our directory to home which is "/"
        chdir("//");
        //update our present working directory or pwd
    }
    else if (chdir(args[1]) < 0){
        //if we are not able to change our directory we need to produce a error
		perror("Error:");
	}
    cwd(PWD);
    return 1;
}
int main(){
    return 0;
}