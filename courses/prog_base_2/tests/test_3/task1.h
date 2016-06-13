#ifndef TASK1_H_INCLUDED
#define TASK1_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct strings_s strings_t;
strings_t * strings_new(char * first,char * second);
int strings_exist(strings_t * self);
void strings_free(free);


#endif // TASK1_H_INCLUDED
