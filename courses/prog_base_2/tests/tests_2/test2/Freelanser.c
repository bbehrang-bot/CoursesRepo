#include <stdlib.h>
#include <string.h>
#include "Freelanser.h"


/*struct teacher_s {
    char * name;
    char * surname;
    double age;
    char * date;
    int salary;

};*/

teacher_t * teacher_new(void) {
    teacher_t * newLanc=malloc(sizeof(struct teacher_s));
    strcpy(newLanc->name,"");
    //newLanc->name=NULL;
    //strcpy(newLanc->surname,"");
    //newLanc->surname=NULL;
    //newLanc->age=0;
    //strcpy(newLanc->date,"");
   // newLanc->date=NULL;
   // newLanc->salary=0;
    return newLanc;
}

void teacher_free(teacher_t * self) {
    free(self);
}

/*void teacher_set(teacher_t * self, char * name, char * surname, double age, char * date,int salary){
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
*/

char * teacher_name_get(teacher_t * self)
{
    return self->name;
}

char * teacher_surname_get(teacher_t * self)
{
    return self->surname;
}

/*char * teacher_date_get(teacher_t * self)
{
    return self->date;
}*/

double teacher_age_get(teacher_t * self)
{

    double age=self->age;
    return age;
}

int teacher_salary_get(teacher_t * self)
{
    return self->salary;
}
void teacher_print(teacher_t * st) {
    //printf("ID: %i\nName: %s\nSurname: %s\nSalary: %f\nAge: %i\nDate: %s\n\n",
//        st->id,st->name, st->surname, st->salary, st->age, st->date);
}

void teacher_printList(teacher_t * arr, int len) {
    for (int i = 0; i < len; i++) {
        teacher_print(&arr[i]);
    }
}


void teacher_set(teacher_t * self, char * name, char * surname, int age,float salary, char * date){

    strcpy(self->name, (const char *)name);
    strcpy(self->surname, (const char *)surname);
    self->age=age;
    self->salary=salary;
//    strcpy(self->date, (const char *)date);

}
