#include "teacher_json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
cJSON * teacher_mJSON(const teacher * teachers) {
    cJSON * teachersJSON = cJSON_CreateObject();
	cJSON_AddItemToObject(teachersJSON, "firstName", cJSON_CreateString(teachers->firstName));
	cJSON_AddItemToObject(teachersJSON, "lastName", cJSON_CreateString(teachers->lastName));
	cJSON_AddItemToObject(teachersJSON, "id", cJSON_CreateNumber(teachers->id));
	cJSON_AddItemToObject(teachersJSON, "lessonName", cJSON_CreateString(teachers->teacher_lesson.lessonName));
	cJSON_AddItemToObject(teachersJSON, "average", cJSON_CreateNumber(teachers->teacher_lesson.average));
	char date[20];
	cJSON_AddItemToObject(teachersJSON, "birthTown", cJSON_CreateString(teachers->idCard.birthTown));
	sprintf(date, "%d-%d-%d", teachers->idCard.birthday.tm_year, teachers->idCard.birthday.tm_mon, teachers->idCard.birthday.tm_mday);
	cJSON_AddItemToObject(teachersJSON, "birthday", cJSON_CreateString(date));
	return teachersJSON;
}
char * teacher_parseAllToJSON(const teacher * teacherArray, int size) {
	cJSON * teacherArrayJSON = cJSON_CreateArray();
	for (int i = 0; i < size; i++) {
		cJSON * tachJSON = teacher_mJSON(teacherArray + i);
		cJSON_AddItemToArray(teacherArrayJSON, tachJSON);
	}
	char * bufferJSON = cJSON_Print(teacherArrayJSON);
	cJSON_Delete(teacherArrayJSON);
	return bufferJSON;
}

char * teacher_parseToJSON(teacher * self) {
//    printStruct(self);
    cJSON * teachJSON = teacher_mJSON(self);
	char * bufferJSON = cJSON_Print(teachJSON);
	cJSON_Delete(teachJSON);
    return bufferJSON;
}
