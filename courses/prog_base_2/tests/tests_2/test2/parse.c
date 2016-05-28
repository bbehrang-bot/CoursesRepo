#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "parse.h"

void parse(teacher_t ** teacherArray,char * fileName)
{
    FILE * file = fopen(fileName, "r");
    char text[10000];
    char line[100];
    strcpy(text,"");
    while(fgets(line, 100, file) != NULL)
    {
        strcat(text, line);
    }
    fclose(file);

    cJSON * jList = cJSON_Parse(text);
    if (!jList)
    {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        return;
    }

    for (int i = 0; i < cJSON_GetArraySize(jList); i++)
    {
        cJSON * jItem = cJSON_GetArrayItem(jList, i);
        char * name = cJSON_GetObjectItem(jItem, "name")->valuestring;
        char * surname = cJSON_GetObjectItem(jItem, "surname")->valuestring;
        char * date = cJSON_GetObjectItem(jItem, "date")->valuestring;
        int salary = cJSON_GetObjectItem(jItem, "salary")->valueint;
        double age = cJSON_GetObjectItem(jItem, "age")->valuedouble;
        teacher_set(teacherArray[i], name, surname, age, salary, date);
    }
    cJSON_Delete(jList);
}
void parseTest(teacher_t ** teacherArray,char * fileName)
{
    FILE * file = fopen(fileName, "r");
    char text[10000];
    char line[100];
    strcpy(text,"");
    while(fgets(line, 100, file) != NULL)
    {
        strcat(text, line);
    }
    fclose(file);

    cJSON * jList = cJSON_Parse(text);
    if (!jList)
    {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        return;
    }

    for (int i = 0; i < cJSON_GetArraySize(jList); i++)
    {
        cJSON * jItem = cJSON_GetArrayItem(jList, i);
        char * name = cJSON_GetObjectItem(jItem, "author")->valuestring;
        char * surname = cJSON_GetObjectItem(jItem, "book")->valuestring;
       // char * date = cJSON_GetObjectItem(jItem, "date")->valuestring;
        //int salary = cJSON_GetObjectItem(jItem, "salary")->valueint;
        //double age = cJSON_GetObjectItem(jItem, "age")->valuedouble;
        char * date;
        strcpy(date,"");
        int salary = 0;
        double age =0;
        teacher_set(teacherArray[i], name, surname, age, salary, date);
    }
    cJSON_Delete(jList);
}

