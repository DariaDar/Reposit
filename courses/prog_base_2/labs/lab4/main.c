#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"
#include "server.h"
#include "pensioner.h"
#include "socket.h"



int main()
{
    lib_init();

    socket_t * serverSocket = socket_new();
    printf("Server socket created.\n");
    socket_bind(serverSocket, 5000);
    socket_listen(serverSocket);

    pensioner_t * pensioners[5];

    for(int i = 0; i < 5; i++)
    {
        pensioners[i] = pensioner_new();
    }

    pensioner_set(pensioners[0], 0, "1945-04-24", "Sam", "Brown", 3142.5, 45);
    pensioner_set(pensioners[1], 1, "1942-11-11", "Harry", "Potter", 4512.5, 50);
    pensioner_set(pensioners[2], 2, "1943-09-04", "Jess", "Day", 5312.5, 55);

    resource_t * list = resource_new();

    for(int i = 0; i < 3; i++)
        resource_add(list, pensioners[i]);
    char buf[10000] = "";
    socket_t * clientSocket = NULL;

    while(1)
    {
        clientSocket = socket_accept(serverSocket);
        socket_read(clientSocket, buf, sizeof(buf));

        if(strlen(buf) != 0)
        {
            printf(">> Got request:\n%s\n", buf);
            http_request_t req = http_request_parse(buf);

            if(strcmp(req.method, "DELETE") == 0 && strncmp(req.uri,"/api/pensioners/", 16) == 0)
            {
                server_pensionerDelete(clientSocket, list, &req);
            }else
            if(strcmp(req.uri, "/") == 0)
            {
                server_homepage(clientSocket);
            } else
            if(strcmp(req.uri, "/api/pensioners") == 0)
            {
                server_pensioners(clientSocket, list, &req);
            }else
            if(strncmp(req.uri, "/api/pensioners/", 16) == 0)
            {
               server_pensionerID(clientSocket, list, &req);
            }else

            if(strcmp(req.uri, "/pensioners") == 0)
            {
                server_pensionersHtml(clientSocket, list, &req);
            }else
            if(strncmp(req.uri, "/pensioners/", 12) == 0)
            {
                server_pensionerHtmlID(clientSocket, list, &req);
            }else
            if(strcmp(req.method, "GET") == 0 && strcmp(req.uri, "/new-pensioner") == 0)
            {
                server_pensionersRetPOST(clientSocket, &req, list);
            }
            else
            {
                server_notFound(clientSocket);
            }
        }
    }


    socket_free(clientSocket);
    socket_free(serverSocket);
    resource_free(list);
    lib_free();
    return 0;
}
