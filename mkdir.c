// Handling mkdir, mkdir -p(no error), mkdir -v(print message)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {

    if (argc<2){
        printf("missing directory name\n");
        return 0;
    }

    char cwd[100];
    FILE *f= fopen("/home/mohit/buffer.txt", "r");
    fgets(cwd, 100, f);
    cwd[strlen(cwd)]= '/';
    cwd[strlen(cwd)+1]= 0;
    fclose(f);
    
    char *filename= (char *)malloc(100);
    char *mode= (char *)malloc(10);
    int value;

    if (argv[1][0]=='-'){
        strcpy(mode, argv[1]);

        if (argv[2][0]!='/'){
            strcpy(filename, cwd);
            strcat(filename, argv[2]);
        }
        else {
            strcpy(filename, argv[2]);
        }
        value= mkdir(filename, 0777);

    } else {
        mode= NULL;

        if (argv[1][0]!='/'){
            strcpy(filename, cwd);
            strcat(filename, argv[1]);
        }
        else {
            strcpy(filename, argv[1]);
        }
        value= mkdir(filename, 0777);
    }

    if (value==-1){
        if (mode==NULL || (mode!=NULL && strcmp(mode, "-v")==0)){
            printf("directory could not be created\n");
        }
        
        else if (mode!=NULL && strcmp(mode, "-p")!=0){
            printf("invald option\n");
        }

    } else {
        if (mode!=NULL && strcmp(mode, "-v")==0){
            printf("directory created\n");
        }
    }

    return 0;
}
