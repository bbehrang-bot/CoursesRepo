#ifndef TEACHER_H_INCLUDED
#define TEACHER_H_INCLUDED
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
struct identification
{
    struct tm birthday;
};
typedef struct teacher
{
    char  firstName[100];
    char  lastName[100];
    int id;
    struct identification idCard;
} teacher;
void printStruct(teacher * teacher);
int teacher_fillArray(size_t size,teacher teachers[size]);
void teacher_init(teacher *teach);
#endif // TEACHER_H_INCLUDED
