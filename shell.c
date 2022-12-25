// Handling cd, cd -L, cd ..


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>

void *myFun(void *arg){
    char *command= (char *)arg;
    for (int i=0; command[i]!=0; i++){
        command[i]= command[i+3];
    }
    char *ogPath= getcwd(NULL, 100);
    char binPath[100];
    memset(binPath, 0, 100);
    strcpy(binPath, ogPath);
    strcat(binPath, "/");
    strcat(binPath, command);
    printf("%s", binPath);
    system(binPath);
}

int main() {   
    
    int n=10;
    char command[100];
    // char **commandl;
    char commandl[n][100];

    char *ogPath= getcwd(NULL, 0);
    FILE *file= fopen("/home/mohit/buffer.txt", "w");
    fwrite(ogPath, 1, 100, file);
    fclose(file);

    do {
        memset(command, 0, 100);
        for (int i=0; i<n; i++){
            memset(commandl[i], 0, 100);
            // strcpy(commandl[i], (char *)NULL);
        }
        // commandl= (char **)realloc(NULL, n);
        // for (int i=0; i<n; i++){
        //     commandl[i]= (char *)realloc(NULL, 100);
        // }

        printf("$ ");
        fgets(command, 100, stdin);

        int j=0, k=0, i=0;
        for (i=0; ((command[i]!='\n') && i<100); i++){
            if ((command[i]==' ')) {
                j++;
                k=0;
                
            } else {
                commandl[j][k]= command[i];
                k++;
            }
        }
        command[i]=0;


        // internal commands
        if ((strcmp(commandl[0], "echo"))==0) {    // echo, echo -n, echo -E
            char msg[100];
            memset(msg, 0, 100);

            if (strcmp(commandl[1], "-n")==0 || strcmp(commandl[1], "-E")==0){
                for(int i=8; command[i]!=0 && i<100;){
                    msg[i-8]= command[i];
                    i++;
                }
                if (strcmp(commandl[1], "-n")==0)
                    printf("%s", msg);
                else
                    printf("%s\n", msg);
            } else if (commandl[1][0]=='-') {
                printf("invalid option\n");
                continue;
            } else {
                for(int i=5; command[i]!=0 && i<100;){
                    msg[i-5]= command[i];
                    i++;
                }
                printf("%s\n", msg);
            }
        }

        else if ((strcmp(commandl[0], "cd"))==0) {     // cd, cd -L, cd ..
            // strcat(command, " && pwd > ~/buffer.txt");
            // system(command);

            int val;
            if (commandl[1]!=NULL && strcmp(commandl[1], "-L")==0){
                val= chdir(commandl[2]);
            } else if (commandl[1][0]=='-'){
                printf("invalid option\n");
                continue;
            } else {
                val= chdir(commandl[1]);
            }

            if (val==-1){
                printf("%s", "directory not found\n");
            } else {
                char *path= getcwd(NULL, 100);
                FILE *file= fopen("/home/mohit/buffer.txt", "w");
                fwrite(path, 1, 100, file);
                fclose(file);
            }
        }

        else if ((strcmp(commandl[0], "pwd"))==0) {    // pwd -L, pwd -P
            char path[100];
            
            if (commandl[1]!=NULL && commandl[1][0]!=0){
                if (commandl[1][0]=='-' && !(strcmp(commandl[1], "-L")==0 || strcmp(commandl[1], "-P")==0)) {
                    printf("invalid option\n");
                } else if (!(strcmp(commandl[1], "-L")==0 || strcmp(commandl[1], "-P")==0)) {
                    printf("wrong argument\n");
                } else {
                    printf("%s\n", getcwd(path,  100));
                }
                // continue;
            } else
                printf("%s\n", getcwd(path,  100));
        }

        // external commands
        else if (((strcmp(commandl[0], "ls") * strcmp(commandl[0], "cat") * strcmp(commandl[0], "date") * strcmp(commandl[0], "rm") * strcmp(commandl[0], "mkdir")))==0) {
            // add og working dir for ls

            char binPath[100];
            memset(binPath, 0, 100);
            strcpy(binPath, ogPath);
            strcat(binPath, "/");
            strcat(binPath, commandl[0]);

            char *args[]= {binPath, NULL, NULL, NULL};
            if (commandl[1][0]!=0)
                args[1]= commandl[1];
            if (commandl[2][0]!=0)
                args[2]= commandl[2];

            int val= fork();
            if (val==0){
                // int value = execl(binPath, binPath, commandl[1], commandl[2], NULL);
                int value = execv(binPath, args);
                if (value==-1){
                    printf("command could not be executed\n");
                }

            } else {
                wait(NULL);
            }
            // printf("\n");
        }

        else if (strcmp(commandl[0], "&t")==0){

            if (((strcmp(commandl[1], "ls") * strcmp(commandl[1], "cat") * strcmp(commandl[1], "date") * strcmp(commandl[1], "rm") * strcmp(commandl[1], "mkdir")))==0) {
                pthread_t id;
                pthread_create(&id, NULL, myFun, (void *)command);
                pthread_join(id, NULL);
                printf("\n");
            
            } else {
                printf("command not found\n");
            }
        }

        else if (strcmp(commandl[0], "exit")==0) {
            break;
        }

        else if (command[0]=='\0'){
            continue;
        }

        else {
            printf("command not found\n");
        }


        // printf("\n");

    } while (1);

    return 0;
}

