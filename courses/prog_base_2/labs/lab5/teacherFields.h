#ifndef TEACHERFIELDS_H_INCLUDED
#define TEACHERFIELDS_H_INCLUDED
#include "time.h"
struct teacher_s {
    int id;
    char  name[50];
    double salary;
    double experience;
    struct tm hireDate;
};


#endif // TEACHERFIELDS_H_INCLUDED
