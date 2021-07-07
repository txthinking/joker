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

int main(int argc, char *argv[])
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
        printf("v20210707\n");
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
        int i = system("s=`ps -e -o command | grep joker | grep -v grep | grep -v \"joker list\"`; if [ -n \"$s\" ]; then ps -x | grep -F \"`echo \"$s\" | cut -d' ' -f2-`\" | grep -v joker | grep -v grep; fi;");
        return i;
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
