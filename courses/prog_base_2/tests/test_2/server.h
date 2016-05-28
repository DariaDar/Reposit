#ifndef SERVER_H
#define SERVER_H
#include "socket.h"
#include "db_manager.h"
#include "list.h"

void server_sent(socket_t * clientSocket, char * text);
void server_dB(db_t * db, list_t * lt);

#endif // SERVER_H
