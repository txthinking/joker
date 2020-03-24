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

void run(struct Cmd *r)
{
    pid_t pid1 = fork();
    if (pid1 > 0) {
        waitpid(pid1, NULL, 0);
    }
    if (pid1 == 0) {
        pid_t pid2 = fork();
        if (pid2 > 0) {
            exit(0);
        }
        if (pid2 == 0) {
            int io[2];
            if (pipe(io) != 0){
                perror("can't create io");
                return;
            }
            pid_t pid = fork();
            if(pid == 0){
#ifdef __linux__
                prctl(PR_SET_PDEATHSIG, SIGHUP);
#endif
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
                sds err = sdsempty();
                list_add(r, &err);
                if(strcmp(err, "") != 0){
                    perror(err);
                    close(io[0]);
                    return;
                }

                char s[16+1];
                sprintf(s, "/tmp/joker.%d", pid);
                FILE *f = fopen(s, "w");
                if(!f) {
                    perror("can not open log file");
                    list_stop(r, &err);
                    if(strcmp(err, "") != 0){
                        perror(err);
                        close(io[0]);
                        return;
                    }
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
                        perror("append log failed");
                        break;
                    }
                    fflush(f);
                }
                list_stop(r, &err);
                if(strcmp(err, "") != 0){
                    perror(err);
                    close(io[0]);
                    fclose(f);
                    chmod(s, 0666);
                    return;
                }
                close(io[0]);
                fclose(f);
                chmod(s, 0666);
            }
        }
    }
}

void log_cmd(int pid, sds *e)
{
    char s[16+1];
    sprintf(s, "/tmp/joker.%d", pid);
    FILE *f = fopen(s, "r");
    if(!f) {
        *e = sdscpy(*e, "can not open log");
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
