#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "turnstile.h"
#include <time.h>

struct turnstile_s{
    user_t * userArray[100];
    int id;
    int passed_count;
    char passed_time[100][20];
};
static void turnstile_init_arrayNull(size_t size,user_t * userArray[size])
{
    for(int i = 0; i<size;i++)
    {
        userArray[i] = NULL;
    }
}
turnstile_t * turnstile_new(int id,int passed)
{
    turnstile_t * ts = malloc(sizeof(struct turnstile_s));
    turnstile_init_arrayNull(100,ts->userArray);
    ts->id = id;
    ts->passed_count = 0;
    return ts;
}
void turnstile_free(turnstile_t * ts)
{
    free(ts->userArray);
    free(ts);
}
void turnstile_pass(turnstile_t * ts,user_t * userPassed)
{

    ts->userArray[ts->passed_count] = userPassed;
    time_t now = time (0);
    strftime(ts->passed_time[ts->passed_count],20,"%Y-%m-%d %H:%M:%S",localtime (&now));
    ts->passed_count++;

}
int turnstile_passed_byId(turnstile_t * ts,int id)
{
    int students_passed = 0;
    for(int i=0;i<ts->passed_count;i++)
    {
        if((ts->userArray[i])->id == id)
            students_passed++;

    }
    return students_passed;
}

void turnstile_print(turnstile_t * ts)
{
    printf("turnstile id : %i\n",ts->id);
    for(int i=0;i<ts->passed_count;i++)
    {
        user_print(ts->userArray[i]);
        printf("passed at : %s\n",ts->passed_time[i]);
    }
}
void turnstile_print_byId(turnstile_t * ts,int id)
{
    printf("%turnstile id : %i\n",ts->id);
    for(int i=0;i<ts->passed_count;i++)
    {
        if(ts->userArray[i]->id == id)
        {
            user_print(ts->userArray[i]);
            printf("passed at : %s\n",ts->passed_time[i]);
        }
    }
}
