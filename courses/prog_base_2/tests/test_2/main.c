#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include <sqlite3.h>
#include "socket.h"
#include "server.h"


int main(void) {

    cJSON * jStudent = cJSON_CreateObject();
    cJSON_AddItemToObject(jStudent, "Name", cJSON_CreateString("Daria"));
	cJSON_AddItemToObject(jStudent, "Surname", cJSON_CreateString("Diachuck"));
	cJSON_AddItemToObject(jStudent, "Group", cJSON_CreateString("KP-51"));
	cJSON_AddItemToObject(jStudent, "Var", cJSON_CreateNumber(10));

    lib_init();

    socket_t * serverSocket = socket_new();

    socket_bind(serverSocket, 5000);
    socket_listen(serverSocket);

    char buf[10000];
    socket_t * clientSocket = NULL;

    server_sent(clientSocket,jStudent);

    while(1)
    {
        socket_read(clientSocket, buf, sizeof(buf));
        if(strlen(buf)!= 0)
        {
           server_sent(clientSocket,jStudent);

        }


        if(socket_read(clientSocket, buf, 102400) == 0) {
            socket_close(clientSocket);
            socket_free(clientSocket);
            puts("Skipping empty request");
            continue;
        }


    }
}
