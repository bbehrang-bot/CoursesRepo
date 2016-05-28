#ifndef PATIENT_H_INCLUDED
#define PATIENT_H_INCLUDED

#include "cJSON.h"

#define MAX_PATIENT_STR_SIZE 20
#define MAX_DATE_STR_SIZE 11
#define SMALL_BUFFER_SIZE 1024
#define BIG_BUFFER_SIZE 10240

typedef struct patient_s patient_t;

patient_t * patient_new(void); // create a patient
void patient_free(patient_t * self); // free patient

void patient_init(patient_t * self, char * name, char * surname, int roomnumber);
void patient_swap(patient_t * self, patient_t * selfSwap); // swap two patients

char * patient_json(patient_t * self, int check);
char * patient_html(patient_t * self, int ID);
char * patient_getName(patient_t * self);
char * patient_getSurname(patient_t * self);

#endif // PATIENT_H_INCLUDED
