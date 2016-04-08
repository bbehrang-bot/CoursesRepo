#ifndef TURNSTILE_H_INCLUDED
#define TURNSTILE_H_INCLUDED
#include "user.h"
#pragma once
#include <stdlib.h>

typedef struct turnstile_s turnstile_t; //turnstile type

turnstile_t * turnstile_new(int id,int passed);
void turnstile_pass(turnstile_t * ts,user_t * userPassed);
void turnstile_print(turnstile_t * ts);


#endif // USER_H_INCLUDED
