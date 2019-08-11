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

void run(struct Cmd *r, sds *e)
{
    if(daemon(1, 0) < 0){
        *e = sdscpy(*e, "can't create daemon");
        return;
    }

    int io[2];
    if (pipe(io) != 0){
        *e = sdscpy(*e, "can't create io");
        return;
    }

    pid_t pid = fork();
    if(pid == 0){
        prctl(PR_SET_PDEATHSIG, SIGHUP);
        close(io[0]);

        char *l[(*r).argc+1];
        int i;
        char *s;
        vec_foreach(&((*r).argv), s, i) {
            l[i] = (char *)malloc(strlen(s)+1);
            l[i] = strcpy(l[i], s);
        }
        l[i] = NULL;

        dup2(io[1], STDOUT_FILENO);
        dup2(io[1], STDERR_FILENO);
        execvp((*r).path, l);

        i=0;
        for(;i<(*r).argc;i++){
            free(l[i]);
        }
        close(io[1]);
    }
    if(pid > 0){
        signal(SIGCHLD, SIG_IGN);
        // TODO ignore kill-like signal
        close(io[1]);

        (*r).pid = pid;
        sds e = sdsempty();
        list_add(r, &e);
        if(strcmp(e, "") != 0){
            // TODO s/printf/file/
            printf("%s\n", e);
            sds_free(e);
            close(io[0]);
            return;
        }

        char s[16+1];
        sprintf(s, "/tmp/joker.%d", pid);
        FILE *f = fopen(s, "a");
        if(!f) {
            printf("can not open log file");
            list_stop(r, &e);
            if(strcmp(e, "") != 0){
                printf("%s\n", e);
                sds_free(e);
                close(io[0]);
                return;
            }
            sds_free(e);
            close(io[0]);
            return;
        }

        for(;;){
            char s[1024];
            int n = read(io[0], s, 1024-1);
            if(n <= 0){
                break;
            }
            s[n] = 0;
            int i = fputs(s, f);
            if (i<0){
                printf("append log failed");
                break;
            }
            fflush(f);
        }
        list_stop(r, &e);
        if(strcmp(e, "") != 0){
            printf("%s\n", e);
            sds_free(e);
            close(io[0]);
            fclose(f);
            return;
        }
        sds_free(e);
        close(io[0]);
        fclose(f);
    }
}

