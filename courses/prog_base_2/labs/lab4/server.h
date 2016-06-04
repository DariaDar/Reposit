#ifndef SERVER_H
#define SERVER_H

#include "socket.h"
#include "resource.h"

typedef struct {
    char key[256];
    char value[256];
} keyvalue_t;

typedef struct {
    char method[20];
    char uri[256];
    keyvalue_t * form;
    int formLength;

} http_request_t;

http_request_t http_request_parse(const char * const request);
const char * http_request_getArg(http_request_t * req, const char * key);
const char * keyvalue_toString(keyvalue_t * self);




void server_homepage(socket_t * client);
char * textToBuf_HTML(char * text);
void server_notFound(socket_t * client) ;
void server_pensioners(socket_t * client, resource_t * lt, http_request_t * req);
void server_pensionerID(socket_t * client, resource_t * lt, http_request_t * req);
void server_pensionerDelete(socket_t * client, resource_t * lt, http_request_t * req);
void server_pensionersHtml(socket_t * client, resource_t * lt, http_request_t * req);
void server_pensionerHtmlID(socket_t * client, resource_t * lt, http_request_t * req);
void server_pensionersRetPOST(socket_t * client, http_request_t * req, resource_t * lt);

#endif // SERVER_H


