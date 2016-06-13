#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student_s student_t;
struct student_s{
    char firstName[100];
    char secondName[100];
    char middleName[100];
    char date[10];
    int id;
    int number;
};
student_t * student_new(char * firstname,char * lastname,char *middleName,char *date,int number);
int student_getId(student_t * self);
void student_free(student_t * self);


#endif // STUDENT_H_INCLUDED
