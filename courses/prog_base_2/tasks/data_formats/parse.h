#ifndef PARSE_H
#define PARSE_H
#include <libxml/parser.h>
#include <libxml/tree.h>
void parse(pensioner_t * pPens, char * file);
void description(pensioner_t pPens, xmlNode * xP);

#endif // PARSE_H
