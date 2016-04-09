#include <stdlib.h>
#include <stdio.h>
#include "terminal.h"
TERMINAL_STATUS terminal_status = TERMINAL_OK;
struct terminal_s
{
    turnstile_t * tsArray[100];
    int turnstile_count;
    int passed;
    int id;
};
/*static void terminal_init_arrayNull(size_t size,turnstile_t * tsArray[size])
{

    for(int i = 0; i<size;i++)
    {
        tsArray[i] = NULL;
    }
}*/
terminal_t * terminal_new(int id)
{
    terminal_t * terminal = malloc(sizeof(struct terminal_s));
    if(terminal==NULL)
    {
        terminal_status = TERMINAL_ERROR_NO_MEMORY;
        return;
    }
    terminal->id = id;
    terminal->passed = 0;
    terminal->turnstile_count = 0;
   // terminal_init_arrayNull(100,terminal->tsArray);
    for(int i=0;i<100;i++)
        terminal->tsArray[i] = turnstile_new_empty();
    terminal_status = TERMINAL_OK;
    return terminal;
}
void terminal_free(terminal_t * terminal)
{
    if(terminal==NULL)
    {
        terminal_status = TERMINAL_ERROR_NO_MEMORY;
        return;
    }
    for(int i=0;i<100;i++)
        free(terminal->tsArray[i]);
    free(terminal);
    terminal_status = TERMINAL_OK;
}
int terminal_get_id(terminal_t * terminal)
{
     if(terminal==NULL)
    {
        terminal_status = TERMINAL_ERROR_NO_MEMORY;
        return;
    }
    terminal_status = TERMINAL_OK;
    return terminal->id;


}
void terminal_add_turnstile(terminal_t * terminal,turnstile_t * ts)
{
    if(terminal==NULL)
    {
        terminal_status = TERMINAL_ERROR_NULL_PTR;
        return;
    }
    terminal->tsArray[terminal->turnstile_count] = ts;
    terminal->turnstile_count ++;
    terminal_status = TERMINAL_OK;
}
int terminal_passed_count(terminal_t * terminal)
{
    if(terminal==NULL)
    {
         terminal_status = TERMINAL_ERROR_NULL_PTR;
        return;
    }
    for(int i=0;i<terminal->turnstile_count;i++)
        terminal->passed += turnstile_passed_count(terminal->tsArray[i]);
    terminal_status = TERMINAL_OK;
    return terminal->passed;
}
void terminal_print_passed_count(terminal_t * terminal)
{
    if(terminal==NULL)
    {
        terminal_status = TERMINAL_ERROR_NULL_PTR;
        return;
    }
    for(int i=0;i<terminal->turnstile_count;i++)
        turnstile_print_passedCount(terminal->tsArray[i]);
    printf("Total passes from terminal id %i : %i\n",terminal->id,terminal->passed);
    terminal_status = TERMINAL_OK;

}
int terminal_passed_count_byType(terminal_t * terminal,int type)
{
    if(terminal==NULL)
    {
        terminal_status = TERMINAL_ERROR_NULL_PTR;
        return;
    }
    int passedType=0;
    for(int i=0;i<terminal->turnstile_count;i++)
        passedType += turnstile_passed_Count_byType(terminal->tsArray[i],type);
    terminal_status = TERMINAL_OK;
    return passedType;
}
void terminal_print_passed_byType(terminal_t * terminal,int type)
{
    if(terminal==NULL)
    {
        terminal_status = TERMINAL_ERROR_NULL_PTR;
        return;
    }
    for(int i=0;i<terminal->turnstile_count;i++)
        turnstile_print_byType(terminal->tsArray[i],type);
    terminal_status = TERMINAL_OK;
}
void terminal_print(terminal_t * terminal)
{
    if(terminal==NULL)
    {
        terminal_status = TERMINAL_ERROR_NULL_PTR;
        return;
    }
    for(int i=0;i<terminal->turnstile_count;i++)
        turnstile_print(terminal->tsArray[i]);
    terminal_status = TERMINAL_OK;
}
TERMINAL_STATUS terminal_get_last_error()
{
    return terminal_status;
}
const char * terminal_strterminal_status(TERMINAL_STATUS terminal_status)
{

    static const char * strterminal_status =
    {"TERMINAL_OK", "TERMINAL_ERROR_NULL_PTR", "TERMINAL_ERROR_NO_MEMORY"};
    return strterminal_status[terminal_status];

}
