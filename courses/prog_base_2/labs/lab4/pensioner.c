#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pensioner.h"


pensioner_t * pensioner_new()
{
    pensioner_t * pens = calloc(1, sizeof(struct pensioner_s));
    return pens;
}

void pensioner_delete(pensioner_t * pens)
{
    free(pens);
}

pensioner_t * pensioner_set(pensioner_t * pens, int id, char * birthday, char * name,
                            char * lastname, double pension, int experience)
{
    pens->id = id;
    strcpy(pens->name, name);
    strcpy(pens->surname, lastname);
    strcpy(pens->birthday, birthday);
    pens->experience = experience;
    pens->pension = pension;
    return pens;
}

int pensioner_getID(pensioner_t * ps)
{
    return ps->id;
}

char * pensioner_getName(pensioner_t * ps)
{
    return ps->name;
}
char *  pensioner_getSurname(pensioner_t * ps)
{
    return ps->surname;
}

int pensioner_getExperience(pensioner_t * ps)
{
    return ps->experience;
}
char * pensioner_getYear(pensioner_t * ps)
{
    return ps->birthday;
}

double pensioner_getPension(pensioner_t * ps)
{
    return ps->pension;
}

char * pensioner_toJSON(pensioner_t * pens)
{
    cJSON * pensJ = cJSON_CreateObject();
    cJSON_AddItemToObject(pensJ, "name", cJSON_CreateString(pens->name));
    cJSON_AddItemToObject(pensJ, "surname", cJSON_CreateString(pens->surname));
    cJSON_AddItemToObject(pensJ, "experience", cJSON_CreateNumber(pens->experience));
    cJSON_AddItemToObject(pensJ, "pension", cJSON_CreateNumber(pens->pension));
    cJSON_AddItemToObject(pensJ, "birthdate", cJSON_CreateString(pens->birthday));
    char * pensText = cJSON_Print(pensJ);
    return pensText;
}

char * pensioner_toHTML(pensioner_t * pens, int id)
{
    char * text = malloc(sizeof(char) * 10240);

    sprintf(text,
            "<p>"
            "ID: %i <br>"
            "Name: %s <br>"
            "Surname: %s <br>"
            "Birthdate: %s <br>"
            "Pension : %.2f <br>"
            "Experience: %i"
            "</p>",
            pens->id,
            pens->name, pens->surname,
            pens->birthday, pens->pension,
            pens->experience);

        char * pageTextLink = "<a href=\"#\" onclick=\"doDelete()\"/>Delete pensioner<br><br></a>\n";
        strcat(text, pageTextLink);

        char pageTextScript[1024];
        sprintf(pageTextScript,
                "<script>"
                "function doDelete() {"
                "var xhttp = new XMLHttpRequest();"
                "xhttp.open(\"DELETE\", \"http://127.0.0.1:5000/pensioners/%i\", true);"
                "xhttp.send();"
                "}"
                "</script>", id);
    strcat(text, pageTextScript);

    return text;
}
