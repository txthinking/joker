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
    printf("\njoker: run command as daemon\n\n");
    printf("    <command>   run your command\n");
    printf("    list        show running commands\n");
    printf("    stop <pid>  stop a command by SIGTERM\n");
    printf("    log <pid>   view log of command\n");
    printf("    last        view pid of last command\n\n");
    printf("    help        show help\n");
    printf("    version     show version\n\n");
}

int main(int argc, char **argv)
{
    if(argc == 1){
        help();
        return 0;
    }
    if(argc == 2 && (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)){
        help();
        return 0;
    }
    if(argc == 2 && (strcmp(argv[1], "version") == 0 || strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)){
        printf("v20221120\n");
        return 0;
    }

    struct passwd *pw = getpwuid(getuid());
    char *s = (char *) malloc(strlen(pw->pw_dir) + 7*100);
    sprintf(s, "%s/.joker", pw->pw_dir);
    struct stat st = {0};
    if (stat(s, &st) == -1) {
        mkdir(s, 0700);
    }
    free(s);

    if(argc == 2 && strcmp(argv[1], "list") == 0){
        char **lp = NULL;
        int li = 0;
        char b[100*2000];
        FILE *f;
        if ((f = popen("ps -x -ww -o pid,tty,stat,time,command", "r")) == NULL) {
            printf("popen ps failed!\n");
            return -1;
        }
        while (fgets(b, 100*2000, f) != NULL) {
            li++;
            lp = realloc(lp, sizeof(char*) * li);
            if(lp == NULL){
                printf("realloc failed\n");
                return -1;
            }
            lp[li-1] = (char *) malloc(strlen(b) + 1);
            memcpy(lp[li-1], b, strlen(b) + 1);
        }
        if (pclose(f)) {
            printf("pclose failed\n");
            return -1;
        }

        char **cp = NULL;
        char **jp = NULL;
        int ji = 0;
        for(int i=0; i<li; i++){
            if(i==0){
                continue;
            }
            char *cstep = NULL;
            char *s0 = strdup(lp[i]);
            char *s = s0;
            int wi = 0;
            int got = 0;
            char *jstep = NULL;
            char *p = NULL;
            for(p=strsep(&s, " \t");p!=NULL;p=strsep(&s, " \t")){
                if(strcmp(p, "") == 0){
                    continue;
                }
                wi++;
                if(wi == 5){
                    cp = realloc(cp, sizeof(char*) * (i+1));
                    if(cp == NULL){
                        printf("realloc failed\n");
                        return -1;
                    }
                    cp[i] = (char *) malloc(strlen(lp[i])+1);
                    cstep = cp[i];
                }
                if(wi >= 5){
                    memcpy(cstep, p, strlen(p));
                    cstep += strlen(p);
                }
                if(wi == 5 && strlen(p)>=5 && strcmp(p+strlen(p)-5, "joker") == 0){
                    got = 1;
                    ji++;
                    jp = realloc(jp, sizeof(char*) * ji);
                    if(jp == NULL){
                        printf("realloc failed\n");
                        return -1;
                    }
                    jp[ji-1] = (char *) malloc(strlen(lp[i])+1);
                    jstep = jp[ji-1];
                    continue;
                }
                if(got == 1){
                    memcpy(jstep, p, strlen(p));
                    jstep += strlen(p);
                }
            }
            cstep++;
            *cstep = '\0';
            if(got == 1){
                jstep++;
                *jstep = '\0';
            }
            free(s0);
        }

        for(int j=0; j<ji; j++){
            for(int i=1; i<li; i++){
                if(strcmp(cp[i], jp[j]) == 0){
                    printf("%s", lp[i]);
                }
            }
        }

        for(int j=0; j<ji; j++){
            free(jp[j]);
        }
        free(jp);
        for(int i=1; i<li; i++){
            free(cp[i]);
        }
        free(cp);
        for(int i=0; i<li; i++){
            free(lp[i]);
        }
        free(lp);

        return 0;
    }
    if(argc == 3 && strcmp(argv[1], "restart") == 0){
        char *s = (char *)malloc(100);
        sprintf(s, "joker list | grep %s | cut -w -f5- > /tmp/jokerrestart", argv[2]);
        int i = system(s);
        if(i != 0){
            printf("%s\n", "failed");
            return i;
        }
        int pid = atoi(argv[2]);
        if(pid == 0){
            printf("%s\n", "invalid id");
            return 1;
        }
        i = kill(pid, SIGTERM);
        if(i != 0){
            printf("%s\n", "stop failed");
            return i;
        }
        sleep(2);
        sprintf(s, "joker `cat /tmp/jokerrestart`");
        return system(s);
    }
    if(argc == 3 && strcmp(argv[1], "stop") == 0){
        int pid = atoi(argv[2]);
        if(pid == 0){
            return 0;
        }
        int i = kill(pid, SIGTERM);
        if(i != 0){
            printf("%s\n", "stop failed");
        }
        return i;
    }
    if(argc == 3 && strcmp(argv[1], "log") == 0){
        char *s = (char *) malloc(4*100+strlen(pw->pw_dir) + 8*100 + strlen(argv[2]));
        sprintf(s, "cat %s/.joker/%s.*", pw->pw_dir, argv[2]);
        int i = system(s);
        free(s);
        return i;
    }
    if(argc == 2 && strcmp(argv[1], "last") == 0){
        char *s = (char *) malloc(strlen(pw->pw_dir) + 18*100);
        sprintf(s, "cat %s/.joker/lastid", pw->pw_dir);
        int i = system(s);
        free(s);
        return i;
    }

    run(argc, argv);
    return 0;
}
