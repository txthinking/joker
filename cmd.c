#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <signal.h>
#include "vec/src/vec.h"
#include "sds/sds.h"
#include "joker.h"

void make_cmd(struct Cmd *r, int argc, char *argv[])
{
    (*r).command = sdsempty();
    (*r).name = sdsempty();
    (*r).argc = argc-1;
    vec_init(&((*r).argv));
    (*r).pid = 0;
    int i = 1;
    for(;i<argc;i++){
        vec_push(&((*r).argv), argv[i]);
        if(i == 1){
            (*r).name = sdscat((*r).name, argv[i]);
            (*r).command = sdscat((*r).command, argv[i]);
            continue;
        }
        (*r).command = sdscat((*r).command, " ");
        (*r).command = sdscat((*r).command, argv[i]);
    }
}

void free_cmd(struct Cmd *r)
{
    sdsfree((*r).name);
    sdsfree((*r).command);
    vec_deinit(&((*r).argv));
}
