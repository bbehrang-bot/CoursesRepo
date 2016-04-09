#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED
#include "Turnstile.h"
typedef enum TERMINAL_STATUS
{TERMINAL_OK, TERMINAL_ERROR_NULL_PTR, TERMINAL_ERROR_NO_MEMORY, TERMINAL_ERROR_FULL} TERMINAL_STATUS;
typedef struct terminal_s terminal_t;
terminal_t * terminal_new(int id);
void terminal_free(terminal_t * terminal);
void terminal_add_turnstile(terminal_t * terminal,turnstile_t * ts);
int terminal_passed_count(terminal_t * terminal);
void terminal_print_passed_count(terminal_t * terminal);
int terminal_passed_count_byType(terminal_t * terminal,int type);
int terminal_get_id(terminal_t * ts);
void terminal_print_passed_byType(terminal_t * terminal,int type);
void terminal_print(terminal_t * terminal);
TERMINAL_STATUS terminal_get_last_error(); //GET last error status
const char * terminal_strstatus(TERMINAL_STATUS status);//get error message
#endif // TERMINAL_H_INCLUDED
