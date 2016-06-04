#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // ptrdiff_t
#include <string.h>
#include <ctype.h>
#include "server.h"
#include "resource.h"
#include "pensioner.h"

int check(char * id, char * name, char * surname, char * birthday, char * pension, char * experience, resource_t * lt);

char * textToBuf_HTML(char * text)
{
    char * buffer = malloc(sizeof(char) * 10240);

    sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %u\n"
            "\n%s", strlen(text), text);

    return buffer;
}

char * textToBuf_JSON(char * text)
{
    char * buffer = malloc(sizeof(char) * 10240);

    sprintf(buffer,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %u\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(text), text);

    return buffer;
}


///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
http_request_t http_request_parse(const char * const request)
{
    http_request_t req;
    // get method
    ptrdiff_t methodLen = strstr(request, " ") - request;  // find first whitespace
    memcpy(req.method, request, methodLen);
    req.method[methodLen] = '\0';
    // get uri
    const char * uriStartPtr = request + strlen(req.method) + 1;
    const char * uriEndPtr = strstr(uriStartPtr, " ");  // find second whitespace
    ptrdiff_t uriLen = uriEndPtr - uriStartPtr;
    memcpy(req.uri, uriStartPtr, uriLen);
    req.uri[uriLen] = '\0';


    req.form = malloc(sizeof(keyvalue_t));
    const char * bodyStartPtr = strstr(request, "\r\n\r\n") + strlen("\r\n\r\n");
    const char * cur = bodyStartPtr;
    const char * pairEndPtr = cur;
    const char * eqPtr = cur;
    while (strlen(cur) > 0)
    {
        pairEndPtr = strchr(cur, '&');
        if (NULL == pairEndPtr)
        {
            pairEndPtr = cur + strlen(cur);
        }
        keyvalue_t kv;
        // get key
        eqPtr = strchr(cur, '=');
        ptrdiff_t keyLen = eqPtr - cur;
        memcpy(kv.key, cur, keyLen);
        kv.key[keyLen] = '\0';
        // get value
        eqPtr++;
        ptrdiff_t valueLen = pairEndPtr - eqPtr;
        memcpy(kv.value, eqPtr, valueLen);
        kv.value[valueLen] = '\0';
        // insert key-value pair into request form list
        req.formLength += 1;
        req.form = realloc(req.form, sizeof(keyvalue_t) * req.formLength);
        req.form[req.formLength - 1] = kv;
        cur = pairEndPtr + ((strlen(pairEndPtr) > 0) ? 1 : 0);
    }
    return req;
}

const char * http_request_getArg(http_request_t * self, const char * key)
{
    for (int i = 0; i < self->formLength; i++)
    {
        if (strcmp(self->form[i].key, key) == 0)
        {
            return self->form[i].value;
        }
    }
    return NULL;
}
///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void server_homepage(socket_t * client)
{
     char * pageText = "<h1 style=\"color:blue\">Hello, world of web!</h1>"
     "<a href=\"http://127.0.0.1:5000/pensioners\">All pensioners</a>";

    char buf[1024] = "";
    char * text = textToBuf_HTML(pageText);
    strcat(buf, text);
    free(text);

    socket_write_string(client, buf);
    socket_close(client);
}

void server_notFound(socket_t * client)
{
    char homeBuf[1024] = "";
    char * pageText = "<h1 style=\"color:red\">404 Page Not Found!</h1>";
    char * text = textToBuf_HTML(pageText);

    strcat(homeBuf, text);
    free(text);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void server_pensioners(socket_t * client, resource_t * lt, http_request_t * req)
{
    char buf[10200] = "";
    if(strcmp(req->method, "GET") == 0)
    {
        cJSON * arr = cJSON_CreateArray();

        for(int i = 0; i < resource_getCnt(lt); i++)
        {
            cJSON * pens = cJSON_CreateObject();
            pensioner_t * ps = resource_getPens(lt, i);
            cJSON_AddItemToObject(pens, "id", cJSON_CreateNumber(pensioner_getID(ps)));
            cJSON_AddItemToObject(pens, "name", cJSON_CreateString(pensioner_getName(ps)));
            cJSON_AddItemToObject(pens, "surname", cJSON_CreateString(pensioner_getSurname(ps)));
            cJSON_AddItemToObject(pens, "year", cJSON_CreateString(pensioner_getYear(ps)));
            cJSON_AddItemToObject(pens, "experience", cJSON_CreateNumber(pensioner_getExperience(ps)));
            cJSON_AddItemToObject(pens, "pension", cJSON_CreateNumber(pensioner_getPension(ps)));
            cJSON_AddItemToArray(arr, pens);
        }
    char * Jtext = cJSON_Print(arr);
    char * textP = textToBuf_JSON(Jtext);

    strcat(buf, textP);
    free(textP);
    }
    else if(strcmp(req->method, "POST") == 0)
    {
        pensioner_t * pens = pensioner_new();
        char * id = (char *)http_request_getArg(req, "id");
        char * name = (char *)http_request_getArg(req, "name");
        char * surname = (char *)http_request_getArg(req, "surname");
        char * birthdate = (char *)http_request_getArg(req, "birthday");
        char * pension = (char *)http_request_getArg(req, "pension");
        char * experience = (char *)http_request_getArg(req, "experience");

        pensioner_set(pens, atoi(id), birthdate, name, surname, atof(pension), atoi(experience));
        resource_add(lt, pens);
        char * Jst = pensioner_toJSON(pens);
        char * pageT = textToBuf_JSON(Jst);
        strcat(buf, pageT);
        free(pageT);
    }

    socket_write_string(client, buf);
    socket_close(client);
}

void server_pensionerID(socket_t * client, resource_t * lt, http_request_t * req)
{
    char buf[2000] = "";
    char * p = strstr(req->uri, "/api/pensioners/");
    p = p + 16;
    int index = atoi(p);

    if(index >= 0)
    {
        for(int i = 0; i < resource_getCnt(lt); i++)
        {
            if(index == resource_getID(lt, i))
            {
                char * text = pensioner_toJSON(resource_getbyId(lt, index));
                char * textP = textToBuf_JSON(text);
                strcat(buf, textP);
                free(textP);
            }
        }
        char * pageText = "{\n    \"Error\": \"ID Not Found\"\n}";
        char * textHTML = textToBuf_JSON(pageText);
        strcat(buf, textHTML);
        free(textHTML);
    }
    else
    {
        char * pageText = "{\n    \"Error\": \"ID Not Found\"\n}";
        char * textHTML = textToBuf_JSON(pageText);
        strcat(buf, textHTML);
        free(textHTML);
    }

        socket_write_string(client, buf);
        socket_close(client);

}

void server_pensionerDelete(socket_t * client, resource_t * lt, http_request_t * req)
{
    char buf[2000] = "";
    char * p = strstr(req->uri, "/api/pensioners/");
    p = p + 16;
    int index = atoi(p);

    if(index >= 0)
    {
        for(int i = 0; i < resource_getCnt(lt); i++)
        {
            if(index == resource_getID(lt, i))
            {
                pensioner_t * pens = resource_deletePens(lt, index);
                char * text = pensioner_toJSON(pens);
                char * textP = textToBuf_JSON(text);
                strcat(buf, textP);
                free(textP);
            }
        }
    }
    else
    {
        char * pageText = "{\n    \"Error\": \"ID Not Found\"\n}";
        char * textP = textToBuf_JSON(pageText);
        strcat(buf, textP);
        free(textP);
    }

    socket_write_string(client, buf);
    socket_close(client);
}
///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void server_pensionersHtml(socket_t * client, resource_t * lt, http_request_t * req)
{
    char buf[10000] = "";

    if(strcmp(req->method, "GET") == 0)
    {
        char text[4000] = "";
        for(int i = 0; i < resource_getCnt(lt); i++)
        {
            char pageText[300] = "";
            sprintf(pageText, "<a href=\"http://127.0.0.1:5000/pensioners/%i\">%s %s<br></a>\n", pensioner_getID(resource_getPens(lt, i)),
                    pensioner_getName(resource_getPens(lt, i)), pensioner_getSurname(resource_getPens(lt, i)));
            strcat(text, pageText);
        }

        char * pageText = "<a href=\"http://127.0.0.1:5000/new-pensioner\"><br>New pensioner</a>";
        strcat(text, pageText);

        char * textHTML = textToBuf_HTML(text);
        strcat(buf, textHTML);
        free(textHTML);
    }
    else if(strcmp(req->method, "POST") == 0)
    {
        char * id = (char *) http_request_getArg(req, "id");
        char * name = (char *)http_request_getArg(req, "name");
        char * surname = (char *)http_request_getArg(req, "surname");
        char * birthday = (char *)http_request_getArg(req, "birthday");
        char * pension = (char *)http_request_getArg(req, "pension");
        char * experience = (char *)http_request_getArg(req, "experience");

        int ch = check(id, name, surname, birthday, pension, experience, lt);
        char * message;
        switch(ch)
         {
         case 1:
            {
                pensioner_t * pens = pensioner_new();
                pensioner_set(pens, atoi(id), birthday, name, surname, atof(pension), atoi(experience));
                resource_add(lt, pens);
                message = "<h3>Success</h3>"
                "<a href=\"http://127.0.0.1:5000/pensioners\"><br>Back to the list.</a>";
                break;
            }
         case 2:
            {
                message = "<h3 style=\"color:green\">This index is already occupied.</h3>";
                break;
            }
         case 3:
            {
                message = "<h3 style=\"color:green\">Wrong index. Number must be > 0.</h3>";
                break;
            }
         case 4:
            {
                message = "<h3 style=\"color:green\">Wrong data format.</h3>";
                break;
            }
         default:
                message = "<h3 style=\"color:green\">Wrong input or empty field.</h3>";
                break;
         }
            char * textHtml = textToBuf_HTML(message);
            strcat(buf, textHtml);
            free(textHtml);
    }


        socket_write_string(client, buf);
        socket_close(client);
}

void server_pensionerHtmlID(socket_t * client, resource_t * lt, http_request_t * req)
{
    char buf[10000] = "";
    char * p = strstr(req->uri, "/pensioners/");
    p = p + 12;
    int index = atoi(p);

    if(index >= 0)
    {
        for(int i = 0; i < resource_getCnt(lt); i++)
        {
            if(index == resource_getID(lt, i))
            {
                if(strcmp(req->method, "GET") == 0)
                {
                    char pText[1000] = "";
                    char * text = pensioner_toHTML(resource_getbyId(lt, index), index);
                    strcat(pText, text);

                    char * pageText = "<a href=\"http://127.0.0.1:5000/pensioners\"><br>Back to the list.</a>";
                    strcat(pText, pageText);

                    char * textHtml = textToBuf_HTML(pText);
                    strcat(buf, textHtml);
                    free(textHtml);
                }
                else if(strcmp(req->method, "DELETE") == 0)
                {
                    char pText[1000] = "";
                    char * text = pensioner_toHTML(resource_deletePens(lt, index), index);
                    strcat(pText, text);
                    free(text);

                    sprintf(buf,
                            "HTTP/1.1 200 OK\n"
                            "Access-Control-Allow-Origin: *\n"
                            "Access-Control-Allow-Methods: DELETE\n"
                            "\n");
                }
            }
        }
        char * message = "<h3 style=\"color:orange\">ID not found!</h3>";
        char * textHtml = textToBuf_HTML(message);
        strcat(buf, textHtml);
        free(textHtml);

    }
    else
    {
        char * message = "<h3 style=\"color:orange\">ID not found!</h3>";
        char * textHtml = textToBuf_HTML(message);
        strcat(buf, textHtml);
        free(textHtml);

    }
    socket_write_string(client, buf);
    socket_close(client);
}

void server_pensionersRetPOST(socket_t * client, http_request_t * req, resource_t * lt)
{
    char buf[10240] = "";

    char * pageText = "<form action=\"http://127.0.0.1:5000/pensioners\" method=\"POST\">"
                        "id:<br>"
                        "<input type=\"text\" name=\"id\" value='3'><br>"
                        "Name:<br>"
                        "<input type=\"text\" name=\"name\" value='Ivan'><br>"
                        "Surname:<br>"
                        "<input type=\"text\" name=\"surname\" value='Ivanov'><br>"
                        "Birthdate:<br>"
                        "<input type=\"text\" name=\"birthday\" value='1945-12-12'><br>"
                        "Pension:<br>"
                        "<input type=\"text\" name=\"pension\" value='2010.25'><br>"
                        "Experience:<br>"
                        "<input type=\"text\" name=\"experience\" value='60'><br><br>"
                        "<input type=\"submit\" value='Send POST request' />"
                        "</form>";

        char * textHtml = textToBuf_HTML(pageText);
        strcat(buf, textHtml);
        free(textHtml);
        socket_write_string(client, buf);
        socket_close(client);
}

int check(char * id, char * name, char * surname, char * birthday, char * pension, char * experience, resource_t * lt)
{
    if(id == NULL || name == NULL || surname == NULL || pension == 0 || experience == 0)
        return 0;
    if(atoi(id) < 0)
        return 3;
    for(int i = 0; i < resource_getCnt(lt); i++)
        if(atoi(id) == resource_getID(lt, i))
            return 2;

    for(int i = 0; i < 4; i++)
    {
        if(!isdigit(birthday[i]))
            return 4;
    }
    if(birthday[4] != '-')
        return 4;
    for(int i = 5; i < 7; i++)
    {
        if(!isdigit(birthday[i]))
            return 4;
        if(birthday[5] > 1)
            return 4;
    }
    if(birthday[7] != '-')
        return 4;

    for(int i = 8; i < 10; i++)
    {
        if(!isdigit(birthday[i]))
            return 4;
        if(birthday[8] > 3 && birthday[9]> 1)
            return 4;
        if(birthday[8] > 3)
            return 4;
    }
    return 1;
}
