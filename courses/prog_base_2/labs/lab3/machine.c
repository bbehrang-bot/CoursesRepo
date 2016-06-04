#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "machine.h"
struct machine_s{
    int firstCard;
    int secondCard;
    int thirdCard;
};
machine_t * machine_new(){
    machine_t * self = malloc(sizeof(struct machine_s));
    self->firstCard = -1;
    self->secondCard = -1;
    self->thirdCard = -1;
}
void machine_free(machine_t * self)
{
    free(self);
}
void machine_fillWithRandom(machine_t * self)
{
    self->firstCard = rand() % 9 + 1;
    self->secondCard = rand() % 9 + 1;
    self->thirdCard = rand() % 9 + 1;
}
int machine_firstEvent(machine_t * self)
{
    if(self->firstCard == self->secondCard || self->firstCard == self->thirdCard || self->secondCard == self->thirdCard)
        return 1;//True
    else
        return 0;//False
}
int machine_secondEvent(machine_t * self)
{
    if(self->firstCard == self->secondCard && self->secondCard == self->thirdCard)
        return 1;//True
    else
        return 0;//False
}
int machine_thirdEvent(machine_t * self)
{
    if(self->firstCard == 7 && self->secondCard == 7 && self->thirdCard == 7)
        return 1;//True
    else
        return 0;//False
}
void machine_print(machine_t * self){
    printf("%i\t%i\t%i\n",self->firstCard,self->secondCard,self->thirdCard);
}


