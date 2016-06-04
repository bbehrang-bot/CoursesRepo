#ifndef MACHINE_H_INCLUDED
#define MACHINE_H_INCLUDED
typedef struct machine_s machine_t;
machine_t * machine_new();
void machine_free(machine_t * self);
int machine_firstEvent(machine_t * self);
int machine_secondEvent(machine_t * self);
int machine_thirdEvent(machine_t * self);
void machine_print(machine_t * self);

#endif // MACHINE_H_INCLUDED
