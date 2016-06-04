#include <stdlib.h>
#include <string.h>

#include "Teacher.h"


struct teacher_s {
    char * name;
    char * surname;
    double age;
    char * date;
    int salary;
};

teacher_t * teacher_new(void) {
    teacher_t * newLanc=malloc(sizeof(struct teacher_s));
    newLanc->name=NULL;
    newLanc->surname=NULL;
    newLanc->age=0;
    newLanc->date=NULL;
    newLanc->salary=0;
    return newLanc;
}

void teacher_free(teacher_t * self) {
    free(self);
}

void teacher_set(teacher_t * self, char * name, char * surname, double age, char * date,int salary){
    if(name!=NULL)
    {
    self->name=malloc(sizeof(name));
    strcpy(self->name,name);
    }
    else
        self->name=name;
    if(surname!=NULL)
    {
    self->surname=malloc(sizeof(surname));
    strcpy(self->surname,surname);
    }
    else
        self->surname=surname;
    if(date!=NULL)
    {
    self->date=malloc(sizeof(date));
    strcpy(self->date,date);
    }
    else
       self->date=date;


    self->age=age;

    self->salary=salary;
}


char * teacher_name_get(teacher_t * myTeacher)
{
    return myTeacher->name;
}

char * teacher_surname_get(teacher_t * myTeacher)
{
    return myTeacher->surname;
}

char * teacher_date_get(teacher_t * myTeacher)
{
    return myTeacher->date;
}

double teacher_age_get(teacher_t * myTeacher)
{

    double age=myTeacher->age;
    return age;
}

int teacher_salary_get(teacher_t * myTeacher)
{
    return myTeacher->salary;
}
