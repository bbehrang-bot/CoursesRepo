#include <stdlib.h>
#include <string.h>

#include "Freelanser.h"


struct Freelanser {
    char * name;
    char * surname;
    double age;
    char * date;
    int salary;
};

lanser * Freelanser_new(void) {
    lanser * newLanc=malloc(sizeof(struct Freelanser));
    newLanc->name=NULL;
    newLanc->surname=NULL;
    newLanc->age=0;
    newLanc->date=NULL;
    newLanc->salary=0;
    return newLanc;
}

void Freelanser_free(lanser * self) {
    free(self);
}

void Freelanser_set(lanser * self, char * name, char * surname, double age, char * date,int salary){
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


char * Freelanser_name_get(lanser * lancer)
{
    return lancer->name;
}

char * Freelanser_surname_get(lanser * lancer)
{
    return lancer->surname;
}

char * Freelanser_date_get(lanser * lancer)
{
    return lancer->date;
}

double Freelanser_age_get(lanser * lancer)
{

    double age=lancer->age;
    return age;
}

int Freelanser_salary_get(lanser * lancer)
{
    return lancer->salary;
}
