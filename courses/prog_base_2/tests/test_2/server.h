#ifndef SERVER_H
#define SERVER_H
#include "socket.h"
#include "db_manager.h"
#include "list.h"
#include "http.h"

/*typedef server_s
{
    char method[8];
    char uri[256];
}server_t;*/



void server_sent(socket_t * clientSocket, char * text);
void server_dB(socket_t * client, db_t * db, list_t * lt);
void server_file(socket_t * client, http_request_t * req);

#endif // SERVER_H
