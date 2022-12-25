// Handling date, date -R, date -I

#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    time_t t= time(NULL);
    struct tm tm= *localtime(&t);

    char *day= (char *)malloc(4);
    char *month= (char *)malloc(4);
    char *mode= (char *)malloc(3);

    switch (tm.tm_wday){
        case 0: day= "Sun"; break;
        case 1: day= "Mon"; break;
        case 2: day= "Tue"; break;
        case 3: day= "Wed"; break;
        case 4: day= "Thu"; break;
        case 5: day= "Fri"; break;
        case 6: day= "Sat"; break;
    }

    switch (tm.tm_mon){
        case 0: month = "Jan"; break;
        case 1: month = "Feb"; break;
        case 2: month = "Mar"; break;
        case 3: month = "Apr"; break;
        case 4: month = "May"; break;
        case 5: month = "Jun"; break;
        case 6: month = "Jul"; break;
        case 7: month = "Aug"; break;
        case 8: month = "Sep"; break;
        case 9: month = "Oct"; break;
        case 10: month= "Nov"; break;
        case 11: month= "Dec"; break;
    }

    int hour;
    if (tm.tm_hour>=12){
        mode= "PM";
        hour= tm.tm_hour-12;
    } else {
        mode= "AM";
        if (tm.tm_hour==0) {
            hour= 12;
        } else {
            hour= tm.tm_hour;
        }
    }
    

    if (argv[1]!=0 && strcmp(argv[1], "-R")==0) {
        printf("%s, %d %s %d %02d:%02d:%02d +0530", day, tm.tm_mday, month, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    }

    else if (argv[1]!=0 && strcmp(argv[1], "-I")==0){
        printf("%d-%d-%d", tm.tm_year+1900, tm.tm_mon, tm.tm_mday);
    }

    else if (argv[1]==0) {
        printf("%s %s %d %02d:%02d:%02d %s %s %d", day, month, tm.tm_mday, hour, tm.tm_min, tm.tm_sec, mode, tm.tm_zone, tm.tm_year+1900);
    
    } else if (argv[1][0]=='-') {
        printf("%s", "invalid option");
    
    } else {
        printf("invalid argument");
    }

    printf("%c", '\n');

    return 0;
}

