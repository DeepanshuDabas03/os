#include <stdio.h>	
#include <string.h>     
#include <stdlib.h> 
#include <stdbool.h>
#include <unistd.h>     
#include <sys/wait.h>
#define f(i,n) for(i=0;i<n;i++)
#define totalcommands 4
#define cwd(PWD) getcwd(PWD, sizeof(PWD))
#define COLOR_BOLD_BLUE "\033[1m"
#define COLOR_OFF "\e[m"
#define COLOR_CYAN "\033[36m"
char pwd[2048],commands[2048];
char *command[]={"cd","pwd","echo","exit"};
char *mi;
//defining 2d array to store our commands. 
int cd(char **array){
    if(array[1]==NULL){
        //if no arrguments are specified we need to change our directory to home which is "/"
        chdir("/");
    }
    else if (chdir(array[1]) < 0){
        //if we are not able to change our directory we need to produce a error
		perror("Error");
	}
    cwd(pwd);
    if(strcmp(pwd,"/")==0){
        mi="~";
    }
    else{
        char split_on[2]="/";
        int allowedsize = 128;
        char ** temp_array = malloc(sizeof(char *) * allowedsize);
        char * userinput;
        char ** input;
        int idx = 0;
        char * temp = strtok(pwd, split_on);
        while (temp != NULL){
            temp_array[idx] = temp;
            idx++;
            temp = strtok(NULL, split_on);
        }
        --idx;
        mi=temp_array[idx];
        cwd(pwd);
    }
        //update our present working directory or pwd
    return 1;
}
int pwdfunc(char ** array){
    //update pwd then print
    if(array[1]==NULL){
        cwd(pwd);
	    printf("Present working directory(pwd) is: %s\n",pwd);
	    return 1;
    }
    if(strcmp(array[1],"-P")==0){
        cwd(pwd);
        printf("%s\n",pwd);
        return 1;
    }
    if(strcmp(array[1],"-L")==0){
        cwd(pwd);
        printf("You choose -L.PWD is:%s\n",pwd);
        return 1;
    }   
}
int echo(char ** array){
    int i = 0;
    bool flag=true;
    int mne=0;
    if(strcmp(array[1],"-n")==0){
        mne=1;
        ++i;
    }
    if(strcmp(array[1],"--help")==0){
        printf("ECHO(1)                      User Commands                     ECHO(1) \n NAME \necho - display a line of text\n DESCRIPTION\nEcho the STRING(s) to standard output.\n -n     do not output the trailing newline\n");
    }
	while (flag){
        ++i;
		if (array[i] == NULL){
            //if all thing are echo, we need to exit
			flag=false;
            continue;
		}
		printf("%s ", array[i]);
	}
    if(mne){
        return 1;
    }
	printf("\n");
    return 1;
}
int exitfunc(char ** array){
	return 58;
}
int start_process(char ** array){
    
    pid_t p1;
    p1= fork();
    if (p1 == 0){
	    char commandpath[2048];
	    strcpy(commandpath, commands);
	    strcat(commandpath, array[0]);	
	    if ( execv( commandpath, array ) == -1){
		    printf("Error: Command Not found\n");
	    }	
    }
    else if (p1 < 0){
		printf("Error:Process can't be created\n");
    }
    else{      
        wait(NULL);
    }
    return 1;
}
int (* internalfunctions[]) (char **) = {&cd,&pwdfunc,&echo,&exitfunc};
int runcommands(char ** array){
    int i;
    f(i,totalcommands)
    {
	    if ( strcmp(array[0], command[i]) == 0 )
        {
            // If the process is in internal functions,run that function
		    return (* internalfunctions[i])(array);
		}
	}
    //else start a process for running external functions.
    return start_process(array);
}    
char * getinput(){
        char * command = (char *)malloc(sizeof(char) * 2048);
        //defining array for getting user input into.Since we can't have variable array for a user input, we restricted size to 2048
        char c;
        int idx = 0,total = 2048;
        c = getchar();
        while (c != EOF && c != '\n'){
                command[idx] = c;
                if (idx >= total){
                        total += 128;
                        command = realloc(command, total);
                }
                ++idx;
                c = getchar();
                //getting input character by character
        }
        return command;
}
char ** split_input(char * command){
        char split_on[2] = " ";
        char * temp = strtok(command, split_on);
        int idx = 0,allowedsize = 128;
        char ** temp_array = malloc(sizeof(char *) * allowedsize); 
        while (temp != NULL){
                temp_array[idx] = temp;
                ++idx;
                temp = strtok(NULL, split_on);
        }
        temp_array[idx] = NULL;
        //store null pointer at last of the input array.
        return temp_array;
}
int main(int argc, char ** argv){
	cwd(pwd);	
	strcpy(commands, pwd);
	strcat(commands,"/");
    char split_on[2]="/";
    int allowedsize = 128;
    char ** temp_array = malloc(sizeof(char *) * allowedsize);
    char * userinput;
    char ** input;
    int idx = 0;
        char * temp = strtok(pwd, split_on);
        while (temp != NULL){
            temp_array[idx] = temp;
            idx++;
            temp = strtok(NULL, split_on);
    }
    --idx;
    mi=temp_array[idx];
	bool flag=true;
   
    while (flag){
        printf(COLOR_CYAN COLOR_BOLD_BLUE"[deepanshu_shell@ "COLOR_OFF);
        printf(COLOR_BOLD_BLUE"%s]" COLOR_CYAN "$ "COLOR_OFF,mi);
        userinput = getinput();
		if ( strcmp(userinput, "") == 0 ){
			continue;
		}
        input = split_input(userinput);
        int returnvalue =runcommands(input);
        if(returnvalue==58){
            flag=false;
            }
        }
    return 0;
}
