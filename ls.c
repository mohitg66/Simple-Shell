// Handling ls, ls -a, ls -p

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    struct dirent *dEntry;

    char cwd[100];
    FILE *f= fopen("/home/mohit/buffer.txt", "r");
    fgets(cwd, 100, f);
    cwd[strlen(cwd)]= 0;
    // printf("directory is %s", cwd);
    fclose(f);
    
    DIR *dir= opendir(cwd);

    if (dir==NULL) {
        printf("%s", "Could not open the directory\n");
        return 0;
    }

    while ((dEntry= readdir(dir)) != NULL){
        if (argv[1]!=0 && (strcmp(argv[1], "-a")==0)) {
            printf("%s\t", dEntry->d_name);
        
        } else if (argv[1]!=0 && (strcmp(argv[1], "-p"))==0) {
            if (dEntry->d_name[0]!='.'){
                if (dEntry->d_type==4){
                    printf("%s/\t", dEntry->d_name);
                } else {
                    printf("%s\t", dEntry->d_name);
                }
            }
        
        } else if (argv[1]==NULL) {
            if (dEntry->d_name[0]!='.') {
                printf("%s\t", dEntry->d_name);
            }
        }

        else if (argv[1][0]=='-') {
            printf("%s", "invalid option");
            break;
        }

        else {
            printf("wrong argument");
            break;
        }
    }

    closedir(dir);
    printf("%c", '\n');

    return 0;
}
