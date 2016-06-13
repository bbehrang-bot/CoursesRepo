#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef struct user_s user_t;
user_t * user_new(int id,char * login,char * country,int age);
void user_free(user_t *  self);
int user_getId(user_t * self);

#endif // USER_H_INCLUDED
