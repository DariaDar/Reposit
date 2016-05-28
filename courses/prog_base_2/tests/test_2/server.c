#include "server.h"
#include "socket.h"
#include <stdio.h>
#include <string.h>
#include "cJSON.h"
#include "pensioner.h"


#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>

/**
*   @return the existence of directory
*/
int dir_exists(const char * dirname) {
    struct stat buffer;
    return (stat (dirname, &buffer) == 0) && S_ISDIR(buffer.st_mode);
}

/**
*   Prints out list of files in directory
*
*   @return number of files
*/
int dir_printFiles(const char * dirname) {
    DIR *dp;
    struct dirent *ep;
    int file_count = 0;
    dp = opendir (dirname);
    if (dp != NULL) {
        while ((ep = readdir (dp))) {
            if(32 == dp->dd_dta.attrib) {
                puts(dp->dd_dir.d_name);
                file_count++;
            }
        }
        (void) closedir (dp);
        return file_count;
    }
    else {
        return -1;
    }
}

/**
*   @return the existence of file
*/
int file_exists(const char * filename)
{
    struct stat buffer;
    return (stat (filename, &buffer) == 0);
}

/**
*   @return -1 if file not found
*/
long long file_getSize(const char * filename) {
    struct stat st;
    if (0 != stat(filename, &st)) {
        return -1;
    }
    long long size = st.st_size;
    return size;
}

time_t file_getCreateTime(const char * filename) {
    struct stat st;
    if (0 != stat(filename, &st)) {
        return (time_t)0;
    }
    return st.st_ctime;
}

/**
*   @return success of the action
*/
int file_create(const char * filename) {
    FILE * fp;
    int success = NULL != (fp = fopen(filename, "ab+"));
    if (!success) {
        return 0;
    }
    fclose(fp);
    return 1;
}

/**
*   @return success of the action
*/
int file_remove(const char * filename) {
    return 0 == remove(filename);
}



///_______________________


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

    for(int i = 1; i < list_getSize(lt); i++)
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
    free(Jtext);
}


void server_file(socket_t * client, http_request_t * req)
{
    char buf[1000];
    list_t * list = list_new();
    if(strcmp(req->method, "GET") == 0)
    {
        char * str;
        str = strtok(req->uri, "/");
        while (str != NULL)
        {
            list_push_back(list, str);
            str = strtok(NULL,"/");
        }

        char * fileName = list_get(list, 2);
        int fileSt = file_exists(fileName);
        if(fileSt == 1)
        {
            FILE * fp = fopen(fileName, "r");
            if(fp == NULL)
            {
                printf("Error!");
                return;
            }
            fseek(fp,0,SEEK_END);
            long length = ftell(fp);
            fseek(fp,0,SEEK_SET);
            fread(buf, length, sizeof(char), fp);
            fclose(fp);

        }





    }
    list_free(list);
}
