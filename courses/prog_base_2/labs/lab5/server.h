#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "socket.h"
#include "Teacher.h"
#include "../cJSON/cJSON.h"
#include "database.h"
#include "../http/http.h"
void server_analyzeRequest(http_request_t * request, socket_t * client, db_t * db);

void server_API_homepage(socket_t * client, char * message);
void server_API_allTeacher(db_t * db, socket_t * client, http_request_t * req);
void server_API_investorByID(db_t * db, socket_t * client, http_request_t * req, int ID);

void server_HTML_homepage(socket_t * client, char * message);
void server_HTML_allTeachers(db_t * db, socket_t * client, http_request_t * req);
void server_HTML_newTeacher(db_t * db, socket_t * client);
void server_HTML_teacherByID(db_t * db, socket_t * client, http_request_t * req, int ID);

void server_invalidResponce(socket_t * client, char * message);


#endif
