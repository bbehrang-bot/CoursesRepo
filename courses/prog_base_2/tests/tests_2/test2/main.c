#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include "parse.h"
#include "server.h"
#include "sqlite3.h"
#include "Database.h"
#include "Freelanser.h"
#include "teacher.h"
#include "socket.h"
#include "winsock.h"
#define BUFFER_SIZE 2000
void getSecret(char *fullAddr, SOCKET recvSocket, char *secretOut)
{
	int recvSize;
	char getMessage[200];
	char buffer[BUFFER_SIZE];

	sprintf(getMessage, "GET %s HTTP/1.1\r\n\r\n", fullAddr);
	if (send(recvSocket, getMessage, strlen(getMessage), 0)<0)
	{
		puts("Send failed");
		return;
	}

	if ((recvSize = recv(recvSocket, buffer, BUFFER_SIZE, 0)) == SOCKET_ERROR)
	{
		puts("Recv Failed");
		return;
	}
	buffer[recvSize] = '\0';
	char *secretLine = "secret=";
	char *secret = strstr(buffer, secretLine);
	int secPos = 0;
	while (secret[secPos] != '=')
		secPos++;
	secPos++;

	int secOutIndex = 0;
	while (secPos <= strlen(secret))
	{
		secretOut[secOutIndex] = secret[secPos];
		secPos++;
		secOutIndex++;
	}
	secretOut[secOutIndex] = '\0';
}
int main() {

    lib_init();


    teacher_t * teacherArray[10];

    fill_teach();


    int size = 1;




    for (int i = 0; i < 10; i++)
        teacherArray[i] = teacher_new();

    parse(teacherArray);

    socket_t * serverSocket = socket_new();
    socket_t * serverSecond = socket_new();


    socket_bind(serverSocket, 5000);
    socket_listen(serverSocket);

    WSADATA data;
	SOCKET recvSocket;
	struct sockaddr_in recvAddr;
	char* hostname = "pb-homework.appspot.com";
	char *var = "/test/var/9?format=json";
	char fullAddr[1000];
	char ip[100];
	char buffer[BUFFER_SIZE];
	struct hostent *he;
	struct in_addr **addr_list;
	int i;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	if ((recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	if ((he = gethostbyname(hostname)) == NULL)
	{
		printf("gethostbyname failed : %d", WSAGetLastError());
		return 1;
	}

	addr_list = (struct in_addr**) he->h_addr_list;
	for (i = 0; addr_list[i] != NULL; i++)
	{
		strcpy(ip, inet_ntoa(*addr_list[i]));
	}
	printf("%s resolved to : %s\n", hostname, ip);

	recvAddr.sin_addr.s_addr = inet_addr(ip);
	recvAddr.sin_family = AF_INET;
	recvAddr.sin_port = htons(80);

	if (connect(recvSocket, (struct sockaddr*)&recvAddr, sizeof(recvAddr)) <0)
	{
		printf("connection failed : %d", WSAGetLastError());
	}
	strcpy(fullAddr, hostname);
	strcat(fullAddr, var);
	getSecret(fullAddr, recvSocket, buffer);

   while (1) {
        socket_t * clientSocket = socket_accept(serverSocket);
        char buf[10000]="";
        SOCKET recvSocket;
        if (!socket_read(clientSocket, buf, sizeof(buf))) {
            puts("Skipping empty request");
            socket_close(clientSocket);
            socket_free(clientSocket);
            continue;
        }
         /*if (!socket_read(secondSocket, buf, sizeof(buf))) {
            puts("Skipping empty request");
            socket_close(secondSocket);
            socket_free(secondSocket);
            continue;
        }*/
        if ((recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        {
		printf("Could not create socket : %d", WSAGetLastError());
        }
        char * secret;
        getSecret("",recvSocket,secret);
        http_request_t req = http_request_parse(buf);

        server_answer(req,clientSocket,teacherArray);

        socket_close(clientSocket);
        socket_free(clientSocket);
    }

    socket_close(serverSocket);
    socket_free(serverSocket);

    lib_free();


/*
    const char * dbFile = "database.db";
    teacher_t LancerList[100];
    teacher_t newLancer;

    //teacher_set(&newLancer,"Vovan","Drush",12,48500,"2010-11-11");

    db_t * db = db_new(dbFile);

    db_getAll(db, LancerList, 100);

    /*db_insertLancer(db, &newLancer);//Already insert
    db_updateLancer(db,&newLancer,3);
    //db_deleteLancer(db,2);//Already deleted

    db_getAll(db, LancerList, 100);

    teacher_print(db_getLancerById(db, 5));

    int countAllStudents = db_countLancers(db);
    printf("Freelancers total: %i\n\n", countAllStudents);
    int filterSalary = 1000;
    int maxCountOfFreelances=3;
    int count = db_getStudentsTask(db, filterSalary,maxCountOfFreelances, LancerList, 100);
    printf("Students with Salary > %i (maximum %i)\n\n", filterSalary, maxCountOfFreelances);
    teacher_printList(LancerList, count);


    db_free(db);

*/
    return 0;
}
