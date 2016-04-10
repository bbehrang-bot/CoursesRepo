#ifndef RANDOMIZER_H_INCLUDED
#define RANDOMIZER_H_INCLUDED
#include "thread.h"
#include "mutex.h"
typedef struct shared_s shared_t;
shared_t * shared_new();
void shared_random_generator(LPVOID args);
HANDLE shared_random_handler(shared_t * data);
void shared_free(shared_t *);
void randomzier_startThread();

#endif // RANDOMIZER_H_INCLUDED
