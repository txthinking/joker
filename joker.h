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

#ifndef __JOKER_H
#define __JOKER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#ifdef __linux__
#include <sys/prctl.h>
#endif
#include <signal.h>
#include "sds/sds.h"
#include "vec/src/vec.h"
#include "joker.h"

void help();

struct Cmd {
    sds command;
    sds path;
    sds name;
    pid_t pid;
    int argc;
    vec_str_t argv;
};

void run(struct Cmd *r, sds *e);
void make_cmd(struct Cmd *r, int argc, char *argv[]);
void free_cmd(struct Cmd *r);
void list_add(struct Cmd *r, sds *e);
void list_stop(struct Cmd *r, sds *e);
void list(sds *e);
void list_all(sds *e);
void log_cmd(int pid, sds *e);

#endif
