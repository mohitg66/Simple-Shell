// Handling rm, rm -i, rm -f

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char const *argv[])
{
    if (argc<2){
        printf("%s", "missing operand\n");
        return 0;
    }

    char cwd[100];
    FILE *f= fopen("/home/mohit/buffer.txt", "r");
    fgets(cwd, 100, f);
    cwd[strlen(cwd)]= '/';
    cwd[strlen(cwd)+1]= 0;
    fclose(f);

    char *filename= (char *)malloc(100);
    int value;

    if (argv[1][0]=='-'){
        // strcpy(mode, argv[1]);
        if (argv[2][0]!='/'){
            strcpy(filename, cwd);
            strcat(filename, argv[2]);
        }
        else {
            strcpy(filename, argv[2]);
        }

    } else {
        // mode= NULL;
        if (argv[1][0]!='/'){
            strcpy(filename, cwd);
            strcat(filename, argv[1]);
        }
        else {
            strcpy(filename, argv[1]);
        }
    }

    DIR *dir = opendir(filename);
    if(dir != NULL) {
        printf("%s",  "a directory cannot be deleted through this command\n");
        return 0;
    }

    if (argv[1]!=0 && strcmp(argv[1], "-f")==0) {
        remove(filename);
    }
    
    // else if (argv[2]!=0 && strcmp(argv[2], "-f")==0) {
    //     remove(argv[1]);
    // }

    else {

        // FILE *file1, *file2;
        FILE *file;
        
        // if (!(argv[1]!=0 && ((file1 = fopen(argv[1], "r")))) && (!(argv[2]!=0 && ((file2 = fopen(argv[2], "r")))))) {
        if (!(file= fopen(filename, "r"))){
            printf("%s", "file not found\n");
            return 0;
        }
    
        if (argv[1]!=0 && strcmp(argv[1], "-i")==0) {
            char c;
            printf("remove file '%s'? ", filename);
            scanf("%c", &c);
            if (c=='y' || c=='Y'){
                value= remove(filename);

                if (value<0){
                    printf("%s", "file could not be deleted\n");
                }
            }
        }
        
        // else if (argv[2]!=0 && strcmp(argv[2], "-i")==0) {
        //     char c;
        //     printf("remove file '%s'? ", argv[1]);
        //     scanf("%c", &c);
        //     if (c=='y' || c=='Y'){
        //         value= remove(argv[1]);

        //         if (value<0){
        //             printf("%s", "file could not be deleted");
        //         }
        //     }
        // }

        else {
            value= remove(filename);
        }
    }

    return 0;
}
