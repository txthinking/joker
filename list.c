// Copyright (c) 2019-present Cloud <cloud@txthinking.com>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of version 3 of the GNU General Public
// License as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#include "joker.h"

void list_add(struct Cmd *r, sds *e)
{
    FILE *f = fopen("/tmp/joker.list", "a");
    if(!f) {
        *e = sdscpy(*e, "can not open /tmp/joker.list");
        return;
    }
    int i = fprintf(f, "%d\t%s\t%s\n", (*r).pid, (*r).name, (*r).command);
    if(i < 0) {
        *e = sdscpy(*e, "can not write /tmp/joker.list");
        fclose(f);
        return;
    }
    fclose(f);
    chmod("/tmp/joker.list", 0666);
}

void list_stop(struct Cmd *r, sds *e)
{
    FILE *f = fopen("/tmp/joker.list", "r");
    if(!f) {
        *e = sdscpy(*e, "can not open /tmp/joker.list");
        return;
    }
    sds s = sdsempty();
    for(;;){
        char s1[1024];
        char *s2 = fgets(s1, 1024, f);
        if(s2 == NULL){
            break;
        }
        char s3[6];
        sprintf(s3, "%d", (*r).pid);
        int i = str_starts_with(s2, s3);
        if(i!=0){
            s = sdscat(s, "[stopped]");
        }
        s = sdscat(s, s2);
    }
    fclose(f);

    f = fopen("/tmp/joker.list", "w");
    if(!f) {
        *e = sdscpy(*e, "can not open /tmp/joker.list");
        return;
    }
    int i = fprintf(f, "%s", s);
    if(i < 0) {
        *e = sdscpy(*e, "can not write /tmp/joker.list");
        sdsfree(s);
        fclose(f);
        return;
    }
    sdsfree(s);
    fclose(f);
}

void list(sds *e)
{
    int i = access("/tmp/joker.list", 0);
    if(i != 0){
        return;
    }
    FILE *f = fopen("/tmp/joker.list", "r");
    if(!f) {
        *e = sdscpy(*e, "can not open /tmp/joker.list");
        return;
    }
    for(;;){
        char s1[1024];
        char *s2 = fgets(s1, 1024, f);
        if(s2 == NULL){
            break;
        }
        int i = str_starts_with(s2, "[stopped]");
        if(i==0){
            printf("%s", s2);
        }
    }
    fclose(f);
}

void list_all(sds *e)
{
    int i = access("/tmp/joker.list", 0);
    if(i != 0){
        return;
    }
    FILE *f = fopen("/tmp/joker.list", "r");
    if(!f) {
        *e = sdscpy(*e, "can not open /tmp/joker.list");
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

void list_clean(sds *e)
{
    int i = access("/tmp/joker.list", 0);
    if(i != 0){
        return;
    }
    FILE *f = fopen("/tmp/joker.list", "r");
    if(!f) {
        *e = sdscpy(*e, "can not open /tmp/joker.list");
        return;
    }
    sds s = sdsempty();
    for(;;){
        char s1[1024];
        char *s2 = fgets(s1, 1024, f);
        if(s2 == NULL){
            break;
        }
        int i = str_starts_with(s2, "[stopped]");
        if(i==0){
            s = sdscat(s, s2);
        }
    }
    fclose(f);

    f = fopen("/tmp/joker.list", "w");
    if(!f) {
        *e = sdscpy(*e, "can not open /tmp/joker.list");
        return;
    }
    i = fprintf(f, "%s", s);
    if(i < 0) {
        *e = sdscpy(*e, "can not write /tmp/joker.list");
        sdsfree(s);
        fclose(f);
        return;
    }
    sdsfree(s);
    fclose(f);
}
