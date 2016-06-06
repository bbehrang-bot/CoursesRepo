#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "Teacher.h"
#include "teacherFields.h"
#include "teacherListFields.h"
#include "../list/list.h"
#include "../cJSON/cJSON.h"
/*struct teacher_s {
    int id;
    char * name;
    char * address;
    char * email;
    int telephone;
    float salary;
    float experience;
    struct tm hireDate;
};*/

teacher_t * teacher_new(void) {
    teacher_t * teacher=malloc(sizeof(struct teacher_s));
    teacher->id = -1;
    strcpy(teacher->name,"Empty");
    teacher->salary = 0;
    teacher->experience = 0;
    teacher->hireDate.tm_year = 1000;
    teacher->hireDate.tm_mday = 1;
    teacher->hireDate.tm_mon = 1;
    return teacher;
}

void teacher_free(teacher_t * self) {
    free(self);
}
teacherList_t * teacherList_new(void)
{
    teacherList_t * tList = malloc(sizeof(struct teacherList_s));
	tList->tList = list_new();
	return tList;
}
static cJSON * teacher_makeJSON(teacher_t * self)
{
    if(self->id == -1)
        return;
    cJSON * teachJSON = cJSON_CreateObject();
    cJSON_AddItemToObject(teachJSON,"id",cJSON_CreateNumber(self->id));
    cJSON_AddItemToObject(teachJSON,"name",cJSON_CreateString(self->name));
    cJSON_AddItemToObject(teachJSON,"salary",cJSON_CreateNumber(self->salary));
    cJSON_AddItemToObject(teachJSON,"experience",cJSON_CreateNumber(self->experience));
    char date[20];
    sprintf(date,"%d-%d-%d",self->hireDate.tm_year,self->hireDate.tm_mon,self->hireDate.tm_mday);
    cJSON_AddItemToObject(teachJSON,"date",cJSON_CreateString(date));
    return teachJSON;
}
char * teacher_toJSON(teacher_t * self)
{
    cJSON * teacherJSON = teacher_makeJSON(self);
    char * buffJSON = cJSON_Print(teacherJSON);
    cJSON_Delete(teacherJSON);
    return buffJSON;
}
char * teacher_arrToJSON(teacherList_t * self)
{
    cJSON * tListJSON = cJSON_CreateArray();
    for(int i = 0 ; i<list_getSize(self->tList);i++)
    {
        teacher_t * teach_tmp = (teacher_t *)list_get(self->tList,i);
        cJSON * teachJSON_tmp = teacher_makeJSON(teach_tmp);
        cJSON_AddItemToArray(tListJSON,teachJSON_tmp);
    }
    char * buffJSON = cJSON_Print(tListJSON);
    cJSON_Delete(tListJSON);
    return buffJSON;
}

void teacher_print(teacher_t * self)
{
    printf("%d %s %lf %lf %d-%d-%d ",self->id,self->name,self->salary,self->experience,self->hireDate.tm_year,
           self->hireDate.tm_mon,self->hireDate.tm_mday);
}
