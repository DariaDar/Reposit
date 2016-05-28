#include "server.h"
#include "socket.h"
#include <stdio.h>
#include <string.h>
#include "cJSON.h"
#include "pensioner.h"


void server_sent(socket_t * clientSocket, char * info)
{
    char buf[10000];
    sprintf(buf,"\nHTTP1.1 200 OK\n"
    "Content-Type: application/json\n"
    "Content-Length: %i\r\n\r\n"
    "%s\n",strlen(info),info);
    socket_write_string(clientSocket,buf);
}


void server_dB(socket_t * client, db_t * db, list_t * lt)
{
    int cntPens = db_countPensioner(db);
    for(int i = 0; i < cntPens; i++)
    {
        list_push_back(lt, db_getPensionerById(db, i));
    }

    cJSON * arr = cJSON_CreateArray();

    for(int i = 0; i < cntPens; i++)
    {
        cJSON * pens = cJSON_CreateObject();
        pensioner_t * ps = list_get(lt, i);
        cJSON_AddItemToObject(pens, "name", cJSON_CreateString(pensioner_getName(ps)));
        cJSON_AddItemToObject(pens, "surname", cJSON_CreateString(pensioner_getSurname(ps)));
        cJSON_AddItemToObject(pens, "year", cJSON_CreateNumber(pensioner_getAge(ps)));
        cJSON_AddItemToObject(pens, "experience", cJSON_CreateNumber(pensioner_getExperience(ps)));
        cJSON_AddItemToObject(pens, "pension", cJSON_CreateNumber(pensioner_getPension(ps)));
        cJSON_AddItemToObject(pens, "surname", cJSON_CreateString(pensioner_getYear(ps)));
        cJSON_AddItemToArray(arr, pens);
    }
    char * Jtext = cJSON_Print(arr);
    server_sent(client, Jtext);
}
