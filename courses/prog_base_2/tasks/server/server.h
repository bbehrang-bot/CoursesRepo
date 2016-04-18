#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#include <winsock.h>
#include "socket.h"
#include "teacher.h"
#include <string.h>
#include "http.h"
void server_homepage(socket_t * client);
int teacher_getId(int i);
void fill_teach();
int teacher_getSize(void);
void server_teachers(socket_t * client, http_request_t * req);
void server_teacherId(socket_t * client, http_request_t * req, int index);
void server_error(socket_t * client);

#endif // SERVER_H_INCLUDED
