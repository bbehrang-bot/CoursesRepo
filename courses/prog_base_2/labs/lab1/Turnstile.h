#ifndef TURNSTILE_H_INCLUDED
#define TURNSTILE_H_INCLUDED
#include "user.h"
#include <stdlib.h>
typedef struct turnstile_s turnstile_t;///Turnstile count
typedef enum TURNSTILE_STATUS
{TURNSTILE_OK, TURNSTILE_ERROR_NULL_PTR, TURNSTILE_ERROR_NO_MEMORY} TURNSTILE_STATUS;
turnstile_t * turnstile_new_empty();
turnstile_t * turnstile_new(int id);///Turnstile constructor , unique id
void turnstile_free(turnstile_t * ts);///Free turnstile from memory
void turnstile_pass(turnstile_t * ts,user_t * userPassed);///pass a user through turnstile
int  turnstile_passed_count(turnstile_t * ts);///count users passed
int turnstile_get_id(turnstile_t * ts);///Return turnstile id
int turnstile_passed_Count_byType(turnstile_t * ts,int type);///count users passed by type(student =0 , teacher , staff)
void turnstile_print(turnstile_t * ts);///print all the users passed
void turnstile_print_byType(turnstile_t * ts,int type);///print users passed by type(student=0,teacher,staff)
void turnstile_print_passed_Count(turnstile_t * ts);///print amount of passed users
TURNSTILE_STATUS turnstile_get_last_error(); //GET last error status
const char * turnstile_strstatus(TURNSTILE_STATUS status);//get error message
#endif // USER_H_INCLUDED
