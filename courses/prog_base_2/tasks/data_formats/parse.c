#include "pensioner.h"
#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


void description(pensioner_t pPens, xmlNode * xP)
{
    char * name;
    char * surname;
    char * birthdate;
    char * pension;
    char * profession;
    char * experience;
    char * grumpiness;

    xmlNode * x1;
    for(x1 = xP->children; NULL != x1; x1 = x1->next)
    {
        if(XML_ELEMENT_NODE == x1->type)
        {
            if(xmlStrcmp(x1->name, (const xmlChar *)"name") == 0)
                name = (char*)xmlNodeGetContent(x1);
            if(xmlStrcmp(x1->name, (const xmlChar *)"surname") == 0)
                surname = (char*)xmlNodeGetContent(x1);
            if(xmlStrcmp(x1->name, (const xmlChar *)"birthdate") == 0)
                birthdate = (char*)xmlNodeGetContent(x1);
            if(xmlStrcmp(x1->name, (const xmlChar *)"pension") == 0)
                pension = (char*)xmlNodeGetContent(x1);
            if(xmlStrcmp(x1->name, (const xmlChar *)"grumpiness") == 0)
                grumpiness = (char*)xmlNodeGetContent(x1);
            if(xmlStrcmp(x1->name, (const xmlChar *)"work") == 0)
            {
                xmlNode * xPr = x1;
                xmlNode * xEx = xPr->children->next;
                profession = (char*)xmlGetProp(xPr, (const xmlChar*)"profession");
                experience = (char*)xmlNodeGetContent(xEx);
            }
        }
    }
    pensioner_set(pPens, name, surname, birthdate, pension, grumpiness, profession, experience);
}



void parse(pensioner_t * pPens, char * file)
{
    char line[100];
    char text[1000] = "";
    FILE * fr = fopen(file, "r");
    while(fgets(line,100,fr))
    {
        strcat(text, line);
    }

    xmlDoc * xDoc;
    xDoc = xmlReadMemory(text,strlen(text), NULL, NULL,0);
    if(NULL == xDoc)
    {
        printf("Error parsing xml from memory");
        return;
    }

    xmlNode * xPensEl;
    xPensEl = xmlDocGetRootElement(xDoc);
    xmlNode * xP;
    int i;
    for(i = 0, xP = xPensEl->children; NULL != xP; xP = xP->next)
    {
        if(XML_ELEMENT_NODE == xP->type)
        {
            description(pPens[i], xP);
            i++;
        }
    }
}


