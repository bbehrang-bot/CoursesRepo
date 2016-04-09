#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "teacher.h"


int main() {
    teacher teachers[4];
	int p =teacher_fillArray(4,teachers);
	for(int i = 0; i < 4; i++)
    {
        printf("firstName : %s\n", teachers[i].firstName);
        printf("lastName : %s\n", teachers[i].lastName);
        printf("missedClasses : %i\n",teachers[i].missedClasses);
        printf("lessonName : %i\n",teachers[i].teacher_lesson.lessonName);
        printf("average : %.2f\n",teachers[i].teacher_lesson.average);
        printf("birthTown : %s\n",teachers[i].idCard.birthTown);
        printf("birthday : %d-%d-%d\n",(teachers[i].idCard.birthday.tm_year),(teachers[i].idCard.birthday.tm_mon),
                        (teachers[i].idCard.birthday.tm_mday));
        puts("\n");
    }

	return 0;
}
