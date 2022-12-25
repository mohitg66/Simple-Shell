// Handling cat, cat -n, cat -e

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {

    if (argc<2){
        printf("missing filename\n");
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
    if (argv[1][0]=='-'){
        strcpy(mode, argv[1]);

        if (argv[2][0]!='/'){
            strcpy(filename, cwd);
            strcat(filename, argv[2]);
        }
        else {
            strcpy(filename, argv[2]);
        }
        
    } else {
        mode= NULL;

        if (argv[1][0]!='/'){
            strcpy(filename, cwd);
            strcat(filename, argv[1]);
        }
        else {
            strcpy(filename, argv[1]);
        }
    }

    FILE *file= fopen(filename, "r");

    if (file==NULL){
        printf("file not found\n");
    } else {
        char c;

        int i=1;
        if (mode!=NULL && strcmp(mode, "-n")==0){
            printf("%5d  ", i++);
        }

        do {
            if (mode!=NULL && strcmp(mode, "-n")==0){
                if (c=='\n' && fgetc(file)!=EOF){
                    fseek(file, -1, SEEK_CUR);
                    printf("%c", c);
                    printf("%5d  ", i++);
                } else {
                    printf("%c", c);
                }

            } else if (mode!=NULL && strcmp(mode, "-e")==0){
                if (c=='\n'){
                    printf("%c", '$');
                }
                printf("%c", c);
            
            } else if (mode==NULL) {
                printf("%c", c);
            
            } else {
                printf("%s", "invalid option\n");
                break;
            }

        } while ((c= fgetc(file))!=EOF);

        fclose(file);
    }

    return 0;
}


