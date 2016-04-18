#ifndef TEACHER_JSON_H_INCLUDED
#define TEACHER_JSON_H_INCLUDED
#include "teacher.h"
#include "cJSON.h"
cJSON * teacher_mJSON(const teacher * teachers);
cJSON * teacher_mJSON(const teacher * teachers);
char * teacher_parseToJSON(teacher * self);
#endif // TEACHER_JSON_H_INCLUDED
