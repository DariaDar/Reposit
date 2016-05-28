#ifndef SERVER_H
#define SERVER_H
#include "socket.h"
#include "db_manager.h"
#include "list.h"

/*typedef server_s
{
    char method[8];
    char uri[256];
}server_t;*/



void server_sent(socket_t * clientSocket, char * text);
void server_dB(socket_t * client, db_t * db, list_t * lt);

#endif // SERVER_H
