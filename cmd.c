#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <signal.h>
#include "sds/sds.h"
#include "joker.h"

void make_cmd(struct Cmd *r, int argc, char *argv[])
{
    (*r).command = sdsempty();
    (*r).name = sdsempty();
    (*r).pid = 0;
    int i = 1;
    for(;i<argc;i++){
        if(i == 1){
            (*r).command = sdscat((*r).command, argv[i]);
            char *s = strrchr(argv[i], '/');
            if (s != NULL){
                (*r).name = sdscat((*r).name, s+1);
            }
            if (s == NULL){
                (*r).name = sdscat((*r).name, argv[i]);
            }
            continue;
        }
        (*r).command = sdscat((*r).command, " ");
        (*r).command = sdscat((*r).command, argv[i]);
    }
}

void free_cmd(struct Cmd *r)
{
    sdsfree((*r).command);
}
