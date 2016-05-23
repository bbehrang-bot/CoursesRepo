#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
typedef struct queue_s queue_t;

queue_t * queue_new(void);
void queue_free(queue_t * self);
///////////
int queue_isFull(queue_t * self);
int queue_isEmpty(queue_t * self);
size_t queue_getSize(queue_t * self);
int queue_getTail(queue_t * self);
//////////
void queue_enqueue(queue_t * self,int value);
int queue_dequeue(queue_t * self);
int queue_getByInd(queue_t * self, int index);
void queue_print(queue_t * self);



#endif // QUEUE_H_INCLUDED
