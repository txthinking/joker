#ifndef __JOKER_H
#define __JOKER_H

void help();

struct Cmd {
    sds command;
    sds name;
    int argc;
    vec_str_t argv;
    pid_t pid;
};

void run(struct Cmd *r, sds *e);
void make_cmd(struct Cmd *r, int argc, char *argv[]);
void free_cmd(struct Cmd *r);
void list_add(struct Cmd *r, sds *e);
void list_del(struct Cmd *r, sds *e);
void list(sds *e);

#endif
