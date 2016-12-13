#ifndef __LOADWORD__
#define __LOADWORD__
#include "ADT_QUEUE.h"
char *readline(int fd);
void shufword(char *filename);
QUEUE *loadQueue(char *filename, int n);
void rmtemp();

#endif
