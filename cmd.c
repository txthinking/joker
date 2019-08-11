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

void make_cmd(struct Cmd *r, int argc, char *argv[])
{
    (*r).command = sdsempty();
    (*r).path = sdsempty();
    (*r).name = sdsempty();
    (*r).pid = 0;
    (*r).argc = argc-1;
    vec_init(&((*r).argv));
    int i = 1;
    for(;i<argc;i++){
        vec_push(&((*r).argv), argv[i]);
        if(i == 1){
            (*r).command = sdscat((*r).command, argv[i]);
            (*r).path = sdscat((*r).path, argv[i]);
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
    sdsfree((*r).path);
    sdsfree((*r).name);
    vec_deinit(&((*r).argv));
}
