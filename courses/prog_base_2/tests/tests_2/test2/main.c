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
#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480
typedef struct {
    char * author;
    char * book;
    char * time;
}author_t;
char *getDateTime()
{
    char *array = (char*)malloc(sizeof(char)*20);
    memset (array, 0, 20);
    time_t rawtime;
    rawtime = time(NULL);
    struct tm  *timeinfo = localtime (&rawtime);
    strftime(array, 20, "20%y.%m.%d", timeinfo);
    array[20] = '\0';
    return array;
}
char * getSecret(char *fullAddr, SOCKET recvSocket, char *secretOut)
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
	/*
	char *secretLine = "{";
	char *secret = strstr(buffer, secretLine);
	int i=0;
	int length=0;
    while(secret[i]!='}')
    {
        i++;
        length++;
    }
    length++;
    secret[length]='\0';
    strcpy(secretOut,secret);
    FILE * fp = fopen("j.json","w");
    if(fp==NULL)
        puts("CANT OPEN");
    int p = fputs(secret,fp);
    fclose(fp);*/
    //char *array = (char*)malloc(sizeof(char)*20);
    //array=getDateTime();
    char * json=strstr(buffer,"{");
    cJSON * SI = cJSON_CreateObject();

    SI=cJSON_Parse(json);
    teacher_t * author=malloc(sizeof(teacher_t));

   // author->name=malloc(strlen(cJSON_GetObjectItem(SI,"author")->valuestring)+1);
    strcpy(author->name,cJSON_GetObjectItem(SI,"author")->valuestring);

    //author->surname=malloc(strlen(cJSON_GetObjectItem(SI,"book")->valuestring)+1);
    strcpy(author->surname,cJSON_GetObjectItem(SI,"book")->valuestring);

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    //author->time=malloc(strlen(asctime(timeinfo)));
    strcpy(author->time,asctime(timeinfo));
    author->time[strlen(author->time)-1]='\0';

    cJSON * SM = cJSON_CreateObject();
    cJSON_AddItemToObject(SM, "author", cJSON_CreateString(author->name));
    cJSON_AddItemToObject(SM, "book", cJSON_CreateString(author->surname));
    cJSON_AddItemToObject(SM, "time", cJSON_CreateString(author->time));
    char * jsonSM = cJSON_Print(SM);
    return jsonSM;

}
int main() {


    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int status;
    int numrcv = 0;
    struct hostent * remoteHost;
    char * ip;
    const char * host_name = "pb-homework.appspot.com";
    char buffer[MAXBUFLEN];
    memset(buffer,0,MAXBUFLEN);
    // Initialize Windows Socket DLL
    status = WSAStartup(MAKEWORD(2, 2), &Data);
    if(status != 0)
    {
        printf("ERROR: WSAStartup unsuccessful\r\n");
        return 0;
    }
	// Get IP address from host name
	remoteHost = gethostbyname(host_name);
	ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
	printf("IP address is: %s.\n", ip);
    memset(&recvSockAddr, 0, sizeof(recvSockAddr)); // zero the sockaddr_in structure
    recvSockAddr.sin_port=htons(PORT); // specify the port portion of the address
    recvSockAddr.sin_family=AF_INET; // specify the address family as Internet
    recvSockAddr.sin_addr.s_addr= inet_addr(ip); // specify ip address
	// Create socket
	recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(recvSocket == INVALID_SOCKET)
	{
		printf("ERROR: socket unsuccessful\r\n");
             WSACleanup();
		system("pause");
		return 0;
	}
    // Connect
    if(connect(recvSocket,(SOCKADDR*)&recvSockAddr,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("ERROR: socket could not connect\r\n");
        closesocket(recvSocket);
        WSACleanup();
        return 0;
    }
    // Send request
    char request[200];
    sprintf(request, "GET /test/var/9?format=json HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);  // add Host header with host_name value
    send(recvSocket, request, strlen(request), 0);

	// Receieve
    numrcv = recv(recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\r\n");
        status = closesocket(recvSocket);
        if(status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\r\n");
        system("pause");
        return(1);
    }
	// Print out receieved socket data
    printf("%s\r\n", buffer);

    char * json=strstr(buffer,"{");


    cJSON * SI = cJSON_CreateObject();

    SI=cJSON_Parse(json);


    author_t * author=malloc(sizeof(author_t));

    author->author=malloc(strlen(cJSON_GetObjectItem(SI,"author")->valuestring)+1);
    strcpy(author->author,cJSON_GetObjectItem(SI,"author")->valuestring);

    author->book=malloc(strlen(cJSON_GetObjectItem(SI,"book")->valuestring)+1);
    strcpy(author->book,cJSON_GetObjectItem(SI,"book")->valuestring);

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    author->time=malloc(strlen(asctime(timeinfo)));
    strcpy(author->time,asctime(timeinfo));
    author->time[strlen(author->time)-1]='\0';

    char * array = getDateTime();
    strcpy(author->time,array);

    cJSON * SM = cJSON_CreateObject();
    cJSON_AddItemToObject(SM, "author", cJSON_CreateString(author->author));
    cJSON_AddItemToObject(SM, "book", cJSON_CreateString(author->book));
    cJSON_AddItemToObject(SM, "time", cJSON_CreateString(author->time));
    char * jsonSM = cJSON_Print(SM);



    socket_t * serverSocket = socket_new();
    socket_bind(serverSocket, 5000);
    socket_listen(serverSocket);
    teacher_t * teacherArray[10];

    for (int i = 0; i < 10; i++)
        teacherArray[i] = teacher_new();

    parse(teacherArray,"Freelanser.json");
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

        http_request_t req = http_request_parse(buf);

        server_answer(req,clientSocket,teacherArray,jsonSM);

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

    db_insertLancer(db, &newLancer);//Already insert
    db_updateLancer(db,&newLancer,3);
    db_deleteLancer(db,2);//Already deleted

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
