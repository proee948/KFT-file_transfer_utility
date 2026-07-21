#ifndef MAIN_H
#define MAIN_H

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info{char path[1024];};
struct info get_path(void);

#endif