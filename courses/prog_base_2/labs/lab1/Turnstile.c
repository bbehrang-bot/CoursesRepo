#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "turnstile.h"
#include <time.h>
#define TURNSTILE_MAX_SIZE 100

struct turnstile_s{
    user_t * userArray[TURNSTILE_MAX_SIZE];
    int id;
    int passed_count;
    char passed_time[TURNSTILE_MAX_SIZE][20];
};
TURNSTILE_STATUS turnstile_status = TURNSTILE_OK;
//USER_STATUS uStatus = USER_OK;
/*static void turnstile_init_arrayNull(size_t size,user_t * userArray[size])
{

    for(int i = 0; i<size;i++)
    {
        userArray[i] = NULL;
    }
}*/
turnstile_t * turnstile_new_empty()
{
         turnstile_t * ts = malloc(sizeof(struct turnstile_s));
         if(ts == NULL)
    {
        turnstile_status = TURNSTILE_ERROR_NO_MEMORY;
        return NULL;
    }
    return ts;
}
turnstile_t * turnstile_new(int id)
{
    turnstile_t * ts = malloc(sizeof(struct turnstile_s));
    if(ts == NULL)
    {
        turnstile_status = TURNSTILE_ERROR_NO_MEMORY;
        return NULL;
    }
    //turnstile_init_arrayNull(TURNSTILE_MAX_SIZE,ts->userArray);
    ts->id = id;
    ts->passed_count = 0;
    turnstile_status = TURNSTILE_OK;
    for(int i=0;i<100;i++)
    {
        ts->userArray[i] = user_new_empty();
    }
    // for i to YURNSTYLE_MAX_SIZE do
    // userArray[i] = user_new();
    return ts;
}
void turnstile_free(turnstile_t * ts)
{
    if(ts==NULL)
    {
        turnstile_status = TURNSTILE_ERROR_NULL_PTR;
        return;
    }
    for(int i=0;i<100;i++)
        free(ts->userArray[i]);
    free(ts);
    turnstile_status = TURNSTILE_OK;
}
int turnstile_get_id(turnstile_t * ts)
{
    if(ts==NULL)
    {
        turnstile_status = TURNSTILE_ERROR_NULL_PTR;
        return;
    }
    return ts->id;
}
void turnstile_pass(turnstile_t * ts,user_t * userPassed)
{
    if(ts==NULL)
    {
        turnstile_status = TURNSTILE_ERROR_NULL_PTR;
        return;
    }
    if(userPassed==NULL)
    {
        //uStatus = USER_ERROR_NULL_PTR;
        return;
    }
    ts->userArray[ts->passed_count] = userPassed;
    time_t now = time (0);
    strftime(ts->passed_time[ts->passed_count],20,"%Y-%m-%d %H:%M:%S",localtime (&now));
    ts->passed_count++;
    turnstile_status = TURNSTILE_OK;
   // uStatus = USER_OK;

}
int turnstile_passed_Count_byType(turnstile_t * ts,int type)
{
    if(ts==NULL)
    {
        turnstile_status = TURNSTILE_ERROR_NULL_PTR;
        return;
    }
    int students_passed = 0;
    for(int i=0;i<ts->passed_count;i++)
    {
        if((user_get_id(ts->userArray[i])) == type)
            students_passed++;

    }
    turnstile_status = TURNSTILE_OK;
    return students_passed;
}
int turnstile_passed_count(turnstile_t * ts)
{
    if(ts==NULL)
    {
        turnstile_status = TURNSTILE_ERROR_NULL_PTR;
        return;
    }
    turnstile_status = TURNSTILE_OK;
    return ts->passed_count;
}
void turnstile_print_passedCount(turnstile_t * ts)
{
    if(ts==NULL)
    {
        turnstile_status = TURNSTILE_ERROR_NULL_PTR;
        return;
    }
    turnstile_status = TURNSTILE_OK;
    printf("turnstile id :%i , total passes : %i\n",ts->id,ts->passed_count);
}
void turnstile_print(turnstile_t * ts)
{
    if(ts==NULL)
    {
        turnstile_status = TURNSTILE_ERROR_NULL_PTR;
        return;
    }
    printf("turnstile id : %i\n",ts->id);
    for(int i=0;i<ts->passed_count;i++)
    {
        user_print(ts->userArray[i]);
        printf("passed at : %s\n",ts->passed_time[i]);
    }
    turnstile_status = TURNSTILE_OK;
}
void turnstile_print_byType(turnstile_t * ts,int type)
{

    if(ts==NULL)
    {
        turnstile_status = TURNSTILE_ERROR_NULL_PTR;
        return;
    }
    printf("turnstile id : %i\n",ts->id);
    for(int i=0;i<ts->passed_count;i++)
    {
        if(user_get_id(ts->userArray[i]) == type)
        {
            user_print(ts->userArray[i]);
            printf("passed at : %s\n",ts->passed_time[i]);
        }
    }
    turnstile_status = TURNSTILE_OK;
}
TURNSTILE_STATUS turnstile_get_last_error()
{
    return turnstile_status;
}
const char * user_strturnstile_status(USER_STATUS turnstile_status)
{

    static const char * strturnstile_status =
    {"TURNSTILE_OK", "TURNSTILE_ERROR_NULL_PTR", "TURNSTILE_ERROR_NO_MEMORY"};
    return strturnstile_status[turnstile_status];

}

