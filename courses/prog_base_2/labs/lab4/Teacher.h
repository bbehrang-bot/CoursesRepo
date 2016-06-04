#ifndef TEACHER_H_INCLUDED
#define TEACHER_H_INCLUDED

typedef struct teacher_s teacher_t;

teacher_t * teacher_new(void);
void teacher_free(teacher_t *);
void teacher_print(teacher_t *);

void teacher_set(teacher_t *, char *, char * , double , char *, int );

char * teacher_name_get(teacher_t *);
char * teacher_surname_get(teacher_t *);
char * teacher_date_get(teacher_t *);
double teacher_age_get(teacher_t *);
char * teacher_companyName_get(teacher_t *);
int teacher_salary_get(teacher_t *);

#endif
