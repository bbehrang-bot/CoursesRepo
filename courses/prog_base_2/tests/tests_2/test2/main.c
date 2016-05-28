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

    //socket_bind(serverSecond,6000);
    socket_bind(serverSocket, 5000);
    socket_listen(serverSocket);
    //socket_listen(serverSecond);


   while (1) {
        socket_t * clientSocket = socket_accept(serverSocket);
       // socket_t * secondSocket = socket_accept(serverSecond);
        char buf[10000]="";

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

        server_answer(req,clientSocket,teacherArray);

        socket_close(clientSocket);
        socket_free(clientSocket);
    }

    socket_close(serverSocket);
    socket_free(serverSocket);

    lib_free();



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
    */

    db_free(db);


    return 0;
}
