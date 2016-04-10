#ifndef ZEROWRITER_H_INCLUDED
#define ZEROWRITER_H_INCLUDED
typedef struct shared_s shared_t;
shared_t * shared_new();
void shared_write_zero(LPVOID args);
HANDLE shared_zero_handle(shared_t * data);
void shared_free(shared_t *);


#endif // ZEROWRITER_H_INCLUDED
