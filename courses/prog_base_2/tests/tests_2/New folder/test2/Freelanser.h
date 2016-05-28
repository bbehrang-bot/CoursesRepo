#ifndef FREELANSER_H_INCLUDED
#define FREELANSER_H_INCLUDED

typedef struct Freelanser lanser;

lanser * Freelanser_new(void);
void Freelanser_free(lanser *);
void Freelanser_print(lanser *);

void Freelanser_set(lanser *, char *, char * , double , char *, int );

char * Freelanser_name_get(lanser *);
char * Freelanser_surname_get(lanser *);
char * Freelanser_date_get(lanser *);
double Freelanser_age_get(lanser *);
char * Freelanser_companyName_get(lanser *);
int Freelanser_salary_get(lanser *);

#endif
