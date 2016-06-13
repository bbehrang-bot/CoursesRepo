#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

student_t * student_new(char * firstname,char * lastname,char *middleName,char *date,int number){
    student_t * student = malloc(sizeof(struct student_s));
    if(firstname != NULL)
        strcpy(student->firstName,firstname);
    if(lastname != NULL)
        strcpy(student->secondName,lastname);
    if(middleName != NULL)
        strcpy(student->middleName,middleName);
    if(date!= NULL)
        strcpy(student->date,date);
    student->number = number;
    return student;

}
int student_getId(student_t * student){
    return student->id;
}
void student_free(student_t * self){
    free(self);
}
