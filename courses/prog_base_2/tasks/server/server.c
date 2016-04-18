#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http.h"
#include <ctype.h>
#include "teacher.h"
#include "server.h"
teacher teachers[4];
void fill_teach(){
int p = teacher_fillArray(4,teachers);
}

int teacher_getSize(void) {
    return (sizeof(teachers)/sizeof(teachers[0]));
}
int teacher_getId(int i){
    int p = teachers[i].id;
    return teachers[i].id;
}
void server_homepage(socket_t * client)
{
    char homebuffer[10000];
    char * homePage = "Welcome,type /teacher for further steps";
    sprintf(homebuffer,"HTTP/1.1 200 OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"Connection: keep-alive\n"
		"\n%s",strlen(homePage),homePage);
		socket_write_string(client,homebuffer);
		socket_close(client);
}
void server_teachers(socket_t * client, http_request_t * req)
{
    char buffer[10240];
	if (strcmp(req->method, "GET") == 0) {

		int amount = teacher_getSize();
		char * teachersJSON = teacher_parseAllToJSON(teachers, amount);
		sprintf(buffer,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(teachersJSON), teachersJSON);
		free(teachersJSON);
	}
	else {
		char * errText = "Invalid command!";
		sprintf(buffer,
			"HTTP/1.1 404 \n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"\n%s", strlen(errText), errText);
	}
	socket_write_string(client, buffer);
	socket_close(client);
}
void server_teacherId(socket_t * client, http_request_t * req, int index) {
	char strbuf[10000];
	if (strcmp(req->method, "GET") == 0) {
            for(int i=0;i<5;i++)
            {
                printStruct(&teachers[index]);
                printf("\n");
            }

		char * teachJSON = teacher_parseToJSON(&teachers[index]);
		sprintf(strbuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(teachJSON), teachJSON);
		free(teachJSON);
	}
	else if (strcmp(req->method, "POST") == 0) {
		char * str = http_request_getArg(req, "firstName");
		if(str==NULL)
        {
             server_error(client);
             return;
        }

		if (str != NULL && strlen(str) < 25) {
            strcpy(teachers[index].firstName,str);
		}
		str = http_request_getArg(req, "lastName");
		if (str != NULL && strlen(str) < 25) {
			  strcpy(teachers[index].lastName,str);
		}
		str = http_request_getArg(req, "id");
		if (str != NULL && isdigit(str[0]) != 0 && strlen(str) < 7) {
			teachers[index].id = atof(str);
		}
		str = http_request_getArg(req, "lessonName");
		if (str != NULL && strlen(str) < 25) {
		     strcpy(teachers[index].teacher_lesson.lessonName,str);
		}
		str = http_request_getArg(req, "average");
		if (str != NULL) {
		    float p = atof(str);
			teachers[index].teacher_lesson.average = p;
		}
		str = http_request_getArg(req, "birthTown");
		if (str != NULL && strlen(str) < 25) {
		     strcpy(teachers[index].idCard.birthTown,str);
		}
		str = http_request_getArg(req, "birthday");
		const char tmp[strlen(str)];
		strcpy(tmp,str);
		if (str != NULL) {
			if (str[5] != NULL && str[4] == '-' && atoi(str) > 1900 && atoi(str) < 2016) {
				str = strtok(str, "-");
				str = strtok(NULL, "-");
				if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 12)) {
					str = strtok(NULL, "-");
					if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 31)) {
						str = http_request_getArg(req, "birthday");
						teachers[index].idCard.birthday.tm_year = atoi(str);
						strcpy(str,tmp);
						str = strtok(str, "-");
						str = strtok(NULL, "-");
						teachers[index].idCard.birthday.tm_mon = atoi(str);
						str = strtok(NULL, "-");
						teachers[index].idCard.birthday.tm_mday = atoi(str);
					}
				}
			}
		}


        printStruct(&teachers[index]);
		char * tJSON = teacher_parseToJSON(&teachers[index]);
		printf("New student with id %i , type /teachers/%i to get full info", teachers[index].id,teachers[index].id , tJSON);
		sprintf(strbuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(tJSON), tJSON);
		free(tJSON);
	}
	else if (strcmp(req->method, "DELETE") == 0) {

         teacher_init(&teachers[index]);
         for(int i=0;i<5;i++)
        {
            printStruct(&teachers[i]);
        }

		char * delTeachJSON = teacher_parseToJSON(&teachers[index]);
		printf("Deleted student (%i-th one):\n%s\n", index, delTeachJSON);
		char * delText = "Student deleted successfully!";
		sprintf(strbuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(delText), delText);
		free(delTeachJSON);
	}
	else {
		char * errText = "Invalid command!";
		sprintf(strbuf,
			"HTTP/1.1 404 \n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"\n%s", strlen(errText), errText);
	}
	socket_write_string(client, strbuf);
	socket_close(client);
}
void server_error(socket_t * client) {
	char replyBuf[1000];
	char * errText = "ERROR";
	sprintf(replyBuf,
		"HTTP/1.1 404 \n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"\n%s", strlen(errText), errText);
	socket_write_string(client, replyBuf);
	socket_close(client);
}
