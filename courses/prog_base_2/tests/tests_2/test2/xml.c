
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "list.h"
#include "Databse.h"
struct work{
    char shop_name[15];
};

struct person{
    char name[15];
    char surname[15];
    char birthdate[11];
    unsigned age;
    float experience_age;
    struct work work;
};

list_t xml_to_list(char *text) {

	xmlDoc * xDoc;
	xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if(NULL == xDoc){
        printf("error");
        return 0;
    }
	list_t persons = list_new();
	struct person * pers = malloc(sizeof(struct person));
    xmlNode * xRootEl;
    int i = 0;
    xRootEl = xmlDocGetRootElement(xDoc);
	int flag = 0;
    for(xmlNode * xCur = xRootEl->children; NULL != xCur ;xCur = xCur->next){
		struct person * pers = malloc(sizeof(struct person));
		flag = 0;
        for(xmlNode * xJ = xCur->children; NULL != xJ ;xJ = xJ->next){
            if(XML_ELEMENT_NODE == xJ->type){
				flag = 1;
                const char * content = xmlNodeGetContent(xJ);
                if(strcmp(xJ->name, "name") == 0){
                    strcpy(pers->name, content);
                }
                if(strcmp(xJ->name, "surname") == 0){
                    strcpy(pers->surname, content);
                }
                if(strcmp(xJ->name, "birthdate") == 0){
                    strcpy(pers->birthdate, content);
                }
                if(strcmp(xJ->name, "age") == 0){
                    pers->age = atoi(content);
                }
                if(strcmp(xJ->name, "experience_age") == 0){
                    pers->experience_age = atof(content);
                }
                if(strcmp(xJ->name, "work") == 0){
                    xmlNode * xWork = xJ;
                    xmlNode * xShopname = xWork->children->next;
                    char * shop = xmlNodeGetContent(xShopname);
                    strcpy(pers->work.shop_name, shop);
                    i++;
                }

            }

        }
		if (flag)
			list_add(persons, pers, list_size(persons));
    }
	return persons;
}

char * list_to_xml(list_t list) {
    xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
	xmlNode * studentNode = NULL;
	xmlNode * groupNode = NULL;
	char strBuf[100];
	char * text = malloc(sizeof (char) * 10000);
	doc = xmlNewDoc("1.0");
	rootNode = xmlNewNode(NULL, "persons");
	FILE * file = fopen("newBase.xml", "w");

	for (int i = 0;i < list_size(list); i++)
	{
		xmlDocSetRootElement(doc, rootNode);
		studentNode = xmlNewChild(rootNode, NULL, "person", NULL);
		xmlNewChild(studentNode, NULL, "name", ((struct person *)list_get(list, i))->name);
		xmlNewChild(studentNode, NULL, "surname", ((struct person *)list_get(list, i))->surname);
		xmlNewChild(studentNode, NULL, "birthdate", ((struct person *)list_get(list, i))->birthdate);
		sprintf(strBuf, "%i", ((struct person *)list_get(list, i))->age);
		xmlNewChild(studentNode, NULL, "age", strBuf);
		sprintf(strBuf, "%llf", ((struct person *)list_get(list, i))->experience_age);
		xmlNewChild(studentNode, NULL, "experience_age", strBuf);
		groupNode = xmlNewChild(studentNode, NULL, "work", NULL);
		//xmlNewProp(groupNode, "name", ((struct person *)list_get(list, i))->work.name);
		xmlNewChild(groupNode, NULL, "shop_name", ((struct person *)list_get(list, i))->work.shop_name);


	}
	xmlBuffer * bufferPtr = xmlBufferCreate();
		xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
		printf("%s", (const char *)bufferPtr->content);
		fprintf(file, "%s", (const char *)bufferPtr->content);
		strcpy(text, (const char *)bufferPtr->content);
		xmlBufferFree(bufferPtr);
	fclose(file);
      xmlFreeDoc(doc);
	xmlCleanupParser();
	return text;
}

char * info_to_xml(char * name, char * group, char * var)
{
	xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
	doc = xmlNewDoc("1.0");
	rootNode = xmlNewNode(NULL, "persons");
	//FILE * file = fopen("newBase.xml", "w");
	char * text = malloc(sizeof(char) * 1000);
	for (int i = 0; i < 1000; i++)
	{
		text[i] = '\0';
	}
	xmlDocSetRootElement(doc, rootNode);
	xmlNewChild(rootNode, NULL, "student", name);
	xmlNewChild(rootNode, NULL, "group", group);
	xmlNewChild(rootNode, NULL, "variant", var);
	xmlBuffer * bufferPtr = xmlBufferCreate();
	xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
	strcat(text, bufferPtr->content);
	xmlBufferFree(bufferPtr);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	puts(text);
	return text;
}

char * list_to_xml1(list_t list) {
    xmlDoc * doc = NULL;
	xmlNode * rootNode = NULL;
	xmlNode * studentNode = NULL;
	xmlNode * groupNode = NULL;
	char strBuf[100];
	char * text = malloc(sizeof (char) * 10000);
	doc = xmlNewDoc("1.0");
	rootNode = xmlNewNode(NULL, "admins");
	FILE * file = fopen("newBase.xml", "w");

	/*int id;
    char name[256];
    char surname[256];
    int birthdate;
    float rate;
    int creating_year;
    int followers;*/
	for (int i = 0;i < list_size(list); i++)
	{
		if (list_get(list, i) == NULL)
			continue;
		puts(((struct admin_s *)list_get(list, i))->name);
		xmlDocSetRootElement(doc, rootNode);
		studentNode = xmlNewChild(rootNode, NULL, "admin", NULL);
		xmlNewChild(studentNode, NULL, "name", ((struct admin_s *)list_get(list, i))->name);
		xmlNewChild(studentNode, NULL, "surname", ((struct admin_s *)list_get(list, i))->surname);
		sprintf(strBuf, "%i", ((struct admin_s *)list_get(list, i))->birthdate);
		xmlNewChild(studentNode, NULL, "birthdate", strBuf);
		sprintf(strBuf, "%llf", ((struct admin_s *)list_get(list, i))->rate);
		xmlNewChild(studentNode, NULL, "rate", strBuf);
		//groupNode = xmlNewChild(studentNode, NULL, "work", NULL);
		//xmlNewProp(groupNode, "name", ((struct person *)list_get(list, i))->work.name);
		sprintf(strBuf, "%i", ((struct admin_s *)list_get(list, i))->creating_year);
		xmlNewChild(studentNode, NULL, "creating_year",strBuf);
		sprintf(strBuf, "%i", ((struct admin_s *)list_get(list, i))->followers);
		xmlNewChild(studentNode, NULL, "followers", strBuf);
			puts("sdfgsfbsgf");
	}
	xmlBuffer * bufferPtr = xmlBufferCreate();
		xmlNodeDump(bufferPtr, NULL, (xmlNode *)doc, 0, 1);
		printf("%s", (const char *)bufferPtr->content);
		fprintf(file, "%s", (const char *)bufferPtr->content);
		strcpy(text, (const char *)bufferPtr->content);
		xmlBufferFree(bufferPtr);
	fclose(file);
      xmlFreeDoc(doc);
	xmlCleanupParser();
	return text;
}
