#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#pragma once
#include <stdlib.h>

typedef struct user_s user_t; //User type
typedef enum user_type { STUDENT = 0 , TEACHER , STAFF} user_type;

user_t * user_new(char * fName, char * lName, int id);
void user_print(user_t * user);
void user_print_array(size_t size ,user_t * user[size]);
void user_free(user_t * user);
void user_free_array(size_t size,user_t * user[size]);

#endif // USER_H_INCLUDED
