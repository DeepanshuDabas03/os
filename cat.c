#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char **array) {
    if (argc==1){
        char arr[1024]="";
        printf("If you want to exit type 'exit' else it will continue to print since you only entered cat\n");
        while(strcmp(arr,"exit\n")!=0){
            printf("%s",arr);
            fgets(arr,1024, stdin );
        }
        return 1;
    }
    if(strcmp(array[1], "-E") == 0) {
        FILE *fr = fopen(array[2], "r");
        if(fr == NULL) {
            printf("cat: Error,file does not exist.\n");
            return 0;
        }
        char ch;
        do {
            ch = fgetc(fr);
            if(ch=='\n'){
                printf("$");
            }
            if(ch!=EOF)
                printf("%c", ch);
        } while (ch != EOF);
        fclose(fr);
        return 1;        
    }
    else if(strcmp(array[1], "-n") == 0) {
        char f[1024];
        FILE *fr = fopen(array[2], "r");
        if(fr == NULL) {
            printf("cat: Error,file does not exist.\n");
            return 0;
        }
        int st=1;
        while (fgets(f, 1024, fr) != NULL) {
            printf("    %d  %s",st,f);
            ++st;
        }
        fclose(fr);     
        return 1;       
    }
    else{
        FILE *fr = fopen(array[1], "r");
        if(fr == NULL) {
            printf("cat: Error,file does not exist.\n");
            return 0;
        }
        char ch;
        do {
            ch = fgetc(fr);
            if(ch!=EOF)
                printf("%c", ch);
        } while (ch != EOF);
        fclose(fr);
        return 1;
    }
}
