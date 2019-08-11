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

void help()
{
    printf("\njoker: run command in background\n\n");
    printf("    <command>   run your command\n");
    printf("    list [-a]   show running command list\n");
    printf("    stop <pid>  stop a command\n");
    printf("    log <pid>   view log of command\n");
    printf("    help        show help\n");
    printf("    version     show version\n\n");
}

int main(int argc, char *argv[])
{
    if(argc == 1){
        help();
        return 0;
    }
    if(argc == 2 && strcmp(argv[1], "help") == 0){
        help();
        return 0;
    }
    if(argc == 2 && strcmp(argv[1], "version") == 0){
        printf("v20190812\n");
        return 0;
    }
    if(argc == 2 && strcmp(argv[1], "list") == 0){
        sds e = sdsempty();
        list(&e);
        if(strcmp(e, "") != 0){
            printf("%s\n", e);
            sdsfree(e);
            return 0;
        }
        sdsfree(e);
        return 0;
    }
    if(argc == 3 && strcmp(argv[1], "list") == 0){
        sds e = sdsempty();
        list_all(&e);
        if(strcmp(e, "") != 0){
            printf("%s\n", e);
            sdsfree(e);
            return 0;
        }
        sdsfree(e);
        return 0;
    }
    if(argc == 3 && strcmp(argv[1], "stop") == 0){
        int pid = atoi(argv[2]);
        if(pid == 0){
            return 0;
        }
        int i = kill(pid, SIGTERM);
        if(i != 0){
            printf("%s\n", "stop failed");
            return 0;
        }
        return 0;
    }
    if(argc == 3 && strcmp(argv[1], "log") == 0){
        int pid = atoi(argv[2]);
        if(pid == 0){
            return 0;
        }
        sds e = sdsempty();
        log_cmd(pid, &e);
        if(strcmp(e, "") != 0){
            printf("%s\n", e);
            sdsfree(e);
            return 0;
        }
        sdsfree(e);
        return 0;
    }

    struct Cmd r;
    make_cmd(&r, argc, argv);

    sds e = sdsempty();
    run(&r, &e);
    if(strcmp(e, "") != 0){
        printf("%s\n", e);
        sdsfree(e);
        free_cmd(&r);
        return 0;
    }

    sdsfree(e);
    free_cmd(&r);
    return 0;
}

