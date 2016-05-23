#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#define QUEUE_MAX 14
struct queue_s
{
    size_t maxSize;
    size_t elemCount;
    int head;
    int * queue;
    int tail;

};
queue_t * queue_new(void)
{
    queue_t * self = malloc(sizeof(struct queue_s));
    self->queue = calloc(QUEUE_MAX,sizeof(int));
    self->elemCount = 0;
    self->maxSize = QUEUE_MAX;
    self->head = 0;
    self->tail = 0;
    return self;
}
void queue_free(queue_t * self)
{
    free(self->queue);
    free(self);
}
int queue_isFull(queue_t * self)
{
    if(self->maxSize == self->elemCount)
        return 1;
    else
        return 0;
}
int queue_isEmpty(queue_t * self)
{
    if(self->maxSize == 0)
        return 1;
    else
        return 0;
}
void queue_enqueue(queue_t * self,int value)
{
    if(queue_isFull(self) == 1)
        self->tail =0;
    if(queue_isFull(self) == 0)
    {
        self->elemCount++;
    }
    self->queue[self->tail] = value;
    self->tail++;
}
int queue_dequeue(queue_t * self);
int queue_getByInd(queue_t * self, int index)
{
    if(queue_isEmpty(self) == 1)
        return -1;
    else
    {
        int elem;
        elem = self->queue[index];
        return elem;
    }
}

size_t queue_getSize(queue_t * self)
{
    return self->elemCount;
}
int queue_getTail(queue_t * self)
{
    return self->tail;
}
void queue_print(queue_t * self)
{
    if(queue_isEmpty(self) == 1)
        puts("Queue is Empty");
    else
    {
        int day = 0;
        if(queue_isFull(self) == 0)
        {
            for(int i =0 ; i<self->tail ; i++)
            {
                printf("Days %i Rained %i mm\n",day,self->queue[i]);
                day++;
            }
        }
        else
        {
            int day = 0;
            for(int i =self->tail ; i<self->maxSize; i++)
            {
                printf("Days %i Rained %i mm\n",day,self->queue[i]);
                day++;
            }
            for(int i = 0; i<self->tail; i++)
            {
                printf("Days %i Rained %i mm\n",day,self->queue[i]);
                day++;
            }
        }

    }
    printf("\n");

}
