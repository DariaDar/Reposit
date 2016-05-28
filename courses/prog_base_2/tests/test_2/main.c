#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include <sqlite3.h>
#include "socket.h"
#include "server.h"
#include "db_manager.h"
#include "list.h"
#include "http.h"


int main(void) {
///______INFO__________

    cJSON * jStudent = cJSON_CreateObject();
    cJSON_AddItemToObject(jStudent, "Name", cJSON_CreateString("Daria"));
	cJSON_AddItemToObject(jStudent, "Surname", cJSON_CreateString("Diachuck"));
	cJSON_AddItemToObject(jStudent, "Group", cJSON_CreateString("KP-51"));
	cJSON_AddItemToObject(jStudent, "Var", cJSON_CreateNumber(10));
	char * Jtext = cJSON_Print(jStudent);

///______________________

    lib_init();

    socket_t * serverSocket = socket_new();
    if(serverSocket == NULL)
    {
        puts("Error init socket");
        return 0;
    }

    if(socket_bind(serverSocket, 8888) == -1)
    {
        printf("error");
        exit(1);
    }
    socket_listen(serverSocket);

    char buf[10000];
    socket_t * clientSocket = NULL;

    char * dbFile = "pensioners.db";
    db_t * db = db_new(dbFile);

    list_t * listPens = list_new();

    while(1)
    {
        clientSocket = socket_accept(serverSocket);
        socket_read(clientSocket, buf, sizeof(buf));

        if(strlen(buf)!= 0)
        {
            printf(">> Got request:\n%s\n", buf);
            http_request_t req = http_request_parse(buf);

            if(strcmp(req.uri, "/info") == 0)
            {
                server_sent(clientSocket, Jtext);
            }
            if(strcmp(req.uri, "/database") == 0)
            {
                server_dB(clientSocket, db,listPens);
            }

            if(strncmp(req.uri, "/files/", 7) == 0)
            {
                server_file(clientSocket, &req);
            }

        }

    }

    socket_free(clientSocket);
    socket_free(serverSocket);
    list_free(listPens);
    db_free(db);
    lib_free();
    return 0;
}
