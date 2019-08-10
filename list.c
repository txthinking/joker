#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <signal.h>
#include "str-starts-with.c/src/str-starts-with.h"
#include "vec/src/vec.h"
#include "sds/sds.h"
#include "joker.h"

void list_add(struct Cmd *r, sds *e)
{
    FILE *f = fopen("/tmp/joker", "a");
    if(!f) {
        *e = sdscpy(*e, "can not open /tmp/joker");
        return;
    }
    int i = fprintf(f, "%d %s\n", (*r).pid, (*r).command);
    if(i < 0) {
        *e = sdscpy(*e, "can not write /tmp/joker");
        fclose(f);
        return;
    }
    fclose(f);
}

void list_del(struct Cmd *r, sds *e)
{
    FILE *f = fopen("/tmp/joker", "r");
    if(!f) {
        *e = sdscpy(*e, "can not open /tmp/joker");
        return;
    }
    sds s = sdsempty();
    for(;;){
        char s1[1024];
        char *s2 = fgets(s1, 1024, f);
        if(s2 == NULL){
            break;
        }
        char s3[9];
        sprintf(s3, "%d", (*r).pid);
        int i = str_starts_with(s2, s3);
        if(i==0){
            s = sdscat(s, s1);
        }
    }
    fclose(f);

    f = fopen("/tmp/joker", "w");
    if(!f) {
        *e = sdscpy(*e, "can not open /tmp/joker");
        return;
    }
    int i = fprintf(f, "%s", s);
    if(i < 0) {
        *e = sdscpy(*e, "can not write /tmp/joker");
        fclose(f);
        return;
    }
    fclose(f);
}

void list(sds *e)
{
    FILE *f = fopen("/tmp/joker", "r");
    if(!f) {
        *e = sdscpy(*e, "can not open /tmp/joker");
        return;
    }
    for(;;){
        char s1[1024];
        char *s2 = fgets(s1, 1024, f);
        if(s2 == NULL){
            break;
        }
        printf("%s", s2);
    }
    fclose(f);
}

