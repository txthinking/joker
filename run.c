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

void run(struct Cmd *r, sds *e)
{
    if(daemon(1, 0) < 0){
        *e = sdscpy(*e, "can't create daemon");
        return;
    }
    pid_t pid;
    pid = fork();
    if (pid < 0){
        *e = sdscpy(*e, "fork failed");
        return;
    }
    if (pid == 0){
        prctl(PR_SET_PDEATHSIG, SIGHUP);
        sds s1 = sdsnew("");
        s1 = sdscatprintf(s1, "%s >> /tmp/joker_%d 2>&1", (*r).command, getpid());
        execlp("/bin/sh", "/bin/sh", "-c", s1, NULL);
    }
    if (pid > 0){
        (*r).pid = pid;
        sds e = sdsempty();
        list_add(r, &e);
        if(strcmp(e, "") != 0){
            perror(e);
            sds_free(e);
            return;
        }
        waitpid(pid, 0, 0);
        list_del(r, &e);
        if(strcmp(e, "") != 0){
            perror(e);
            sds_free(e);
            return;
        }
    }
}

