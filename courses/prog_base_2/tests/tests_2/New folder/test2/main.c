#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "socket.h"
#include "parse.h"
#include "server.h"

int main() {
    lib_init();


    lanser * freeLanser[10];

    for (int i = 0; i < 10; i++)
        freeLanser[i] = Freelanser_new();

    parse(freeLanser);

    socket_t * serverSocket = socket_new();
    socket_bind(serverSocket, 5000);
    socket_listen(serverSocket);


   while (1) {
        socket_t * clientSocket = socket_accept(serverSocket);

        char buf[10000]="";

        if (!socket_read(clientSocket, buf, sizeof(buf))) {
            puts("Skipping empty request");
            socket_close(clientSocket);
            socket_free(clientSocket);
            continue;
        }

        http_request_t req = http_request_parse(buf);

        server_answer(req,clientSocket,freeLanser);

        socket_close(clientSocket);
        socket_free(clientSocket);
    }

    socket_close(serverSocket);
    socket_free(serverSocket);

    lib_free();
    return 0;
}
