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

void help()
{
    printf("\njoker: run command in background\n\n");
    printf("    <command>   run your command\n");
    printf("    list        show running command list\n");
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
        printf("v20190810\n");
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
    if(argc == 3 && strcmp(argv[1], "stop") == 0){
        int pid = atoi(argv[2]);
        if(pid == 0){
            return 0;
        }
        int i = kill(pid, SIGINT);
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
        log(pid, &e);
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

