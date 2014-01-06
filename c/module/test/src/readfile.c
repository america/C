/********************************************/
/* read_file.c                              */
/*------------------------------------------*/
/* author:t.haga                            */
/********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024 + 1

int read_file(char *fname, char *data)
{
    FILE *fp;
    char *buf;
   
    buf = (char *)malloc(BUFSIZE);

    if(buf == NULL) {
        exit -1;
    } 

    fp = fopen(fname, "r");
    if(fp == NULL) {
        perror("fopen");
        exit -1;
    }

    while(fgets(buf, sizeof(buf), fp) != NULL) {
        strncat(data, buf, sizeof(buf));
    }

    fclose(fp);
    free(buf);

    return 0;
}
