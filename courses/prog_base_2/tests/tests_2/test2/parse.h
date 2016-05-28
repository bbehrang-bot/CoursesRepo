#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED

#include <libxml/parser.h>
#include <libxml/tree.h>
#include "Freelanser.h"

void parse(teacher_t ** teacherArray,char * fileName);
void parseTest(teacher_t ** teacherArray,char * fileName);

#endif
