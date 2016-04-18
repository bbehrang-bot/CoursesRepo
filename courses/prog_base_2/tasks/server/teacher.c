#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "teacher.h"
void printStruct(teacher * teacher){
     printf("firstName : %s\n", teacher->firstName);
        printf("lastName : %s\n", teacher->lastName);
        printf("id : %i\n",teacher->id);
        printf("lessonName : %i\n",teacher->teacher_lesson.lessonName);
        printf("average : %.2f\n",teacher->teacher_lesson.average);
        printf("birthTown : %s\n",teacher->idCard.birthTown);
        printf("birthday : %d-%d-%d\n",(teacher->idCard.birthday.tm_year),(teacher->idCard.birthday.tm_mon),
                        (teacher->idCard.birthday.tm_mday));
}
void teacher_fill_info(teacher * newTeacher,xmlNode * teacherParrent)
{
    xmlNode * teacherNode = teacherParrent->children;
    char *content;
    for(xmlNode * cur = teacherNode->next;cur != NULL;cur = cur->next)
    if(cur->type == XML_ELEMENT_NODE)
    {
        if(xmlStrEqual(cur->name,"firstName"))
        {
            content = xmlNodeGetContent(cur);
            strcpy(newTeacher->firstName,content);
        }
        else if(xmlStrEqual(cur->name,"lastName"))
        {
            content = xmlNodeGetContent(cur);
            strcpy(newTeacher->lastName,content);
        }
        else if(xmlStrEqual(cur->name,"id"))
        {
            content = xmlNodeGetContent(cur);
            newTeacher->id = atoi(content);
        }
        else if(xmlStrEqual(cur->name,"lesson"))
        {
            char *attr = xmlGetProp(cur,"lessonName");
            content = xmlNodeGetContent(cur);
            strcpy(newTeacher->teacher_lesson.lessonName,attr);
            float avrg = atof(content);
            newTeacher->teacher_lesson.average = avrg;
            free(attr);
        }
        else if(xmlStrEqual(cur->name,"identification"))
        {
            xmlNode * idenNode = cur->children;
            char *idenContent;
            for(xmlNode * curIdenNode = idenNode->next;curIdenNode != NULL;curIdenNode = curIdenNode->next)
            {
                if(curIdenNode->type == XML_ELEMENT_NODE)
                {
                    if(xmlStrEqual(curIdenNode->name,"birthTown"))
                    {
                        idenContent = xmlNodeGetContent(curIdenNode);
                        strcpy(newTeacher->idCard.birthTown,idenContent);
                    }
                    else if(xmlStrEqual(curIdenNode->name,"birthday"))
                    {
                        struct tm birth;
                        memset(&birth, 0, sizeof(struct tm));
                        idenContent = xmlNodeGetContent(curIdenNode);
                        sscanf(idenContent,"%i-%i-%i",
                        &(newTeacher->idCard.birthday.tm_year),&(newTeacher->idCard.birthday.tm_mon),
                        &(newTeacher->idCard.birthday.tm_mday));
                    }
                }
            }
           free(idenContent); //http://stackoverflow.com/questions/4984853/mingw-libxml2-issue
           //xmlFreeNode(idenNode);
        }
        free(content);//http://stackoverflow.com/questions/4984853/mingw-libxml2-issue
    }
    xmlFreeNode(teacherNode);
}
int teacher_fillArray(size_t size,teacher teachers[size])
{
    xmlDoc * doc = NULL;
    xmlNode * rootNode = NULL;
    xmlNode * teachersNode = NULL;
    xmlNode * lessonNode = NULL;
    doc = xmlParseFile("teacher.xml");

    if (doc == NULL ) {
        puts("Document didnt parse successfully");
        xmlCleanupParser();
        return -1;
    }
    rootNode = xmlDocGetRootElement(doc);
    teachersNode = rootNode->children;
    if(rootNode == NULL)
    {
        puts("document is empty");
        xmlCleanupParser();
        return -1;
    }
    int i=0;
    for(xmlNode * curParrent=teachersNode->next;curParrent!=NULL;curParrent = curParrent->next)
    {
        if(curParrent->type == XML_ELEMENT_NODE)
        {
            teacher_fill_info(&teachers[i],curParrent);
            i++;
        }
    }
    xmlCleanupParser();
    return 1;
}
void teacher_init(teacher * teach){

    strcpy(teach->firstName,"");
    strcpy(teach->lastName,"");
    strcpy(teach->teacher_lesson.lessonName,"");
    strcpy(teach->idCard.birthTown,"");
    teach->id = 0;
    teach->teacher_lesson.average = 0;
    teach->idCard.birthday.tm_year = 0;
    teach->idCard.birthday.tm_mday = 0;
    teach->idCard.birthday.tm_mon = 0;
}
