#ifndef FREELANSER_H_INCLUDED
#define FREELANSER_H_INCLUDED
#include <time.h>
//typedef struct teacher_s teacher_t;

typedef struct teacher_s {
    int id;
    char name[256];
    char surname[256];
    float salary;
    int age;
   char date[10];
    char bookName[256];
   char  time[9];
} teacher_t;

teacher_t * teacher_new(void);
void teacher_free(teacher_t *);


//void teacher_set(teacher_t *, char *, char * , double , char *, int );

char * teacher_name_get(teacher_t *);
char * teacher_surname_get(teacher_t *);
char * teacher_date_get(teacher_t *);
double teacher_age_get(teacher_t *);
char * teacher_companyName_get(teacher_t *);
int teacher_salary_get(teacher_t *);
void teacher_print(teacher_t * st);
void teacher_printList(teacher_t * arr, int len);
void teacher_set(teacher_t * self, char * name, char * surname, int age,float salary, char * date);
#endif
