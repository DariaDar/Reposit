/*#ifndef RESOURCE_H
#define RESOURCE_H

typedef struct node_s node_t;
typedef struct resource_s resource_t;
typedef struct pensioner_s pensioner_t;

resource_t * resource_new();
void resource_delete(resource_t * r);
void resource_fillList(resource_t * res);
pensioner_t * resource_getById(resource_t * res, int id);
void resource_insert(resource_t * res, pensioner_t * pens);
int resource_update(resource_t * res, pensioner_t * pens);
int resource_deletePens(resource_t * res, int id);
int resource_getCnt(resource_t * res);
pensioner_t * resource_getList(resource_t * res);

#endif // RESOURCE_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"


typedef struct pensioner_s
{
	int		id;
    char	name[256];
    char	surname[256];
	int		year;
	int		experience;
	float	pension;
	char	birthday[20];
};

struct node_s
{
    pensioner_t * pens;
    node_t * next;
};

struct resource_s
{
    pensioner_t * head;
    pensioner_t * tail;
    int size;
};

resource_t * resource_new()
{
    resource_t * rs = calloc(1, sizeof(struct resource_s));
    rs->size = 0;
    rs->head = node_new(NULL);
    rs->tail = node_new(NULL);
    rs->head = rs->tail;
    rs->tail = rs-head;
    //rs->tail = !!!!
    //resource_fillList(rs);
    return rs;
}

void resource_delete(resource_t * r)
{
    free(r);
}
*/
/*void resource_fillList(resource_t * res)
{
    for(int i = 0; i < 5; i++)
	{
		memcpy(&res->pArr[i], &ps[i], sizeof(struct pensioner_s));
	}
	res->cnt = 5;
}*/
/*
void resource_push_back(resource_t * res, pensioner_t * pens)
{
    node_t * newNode = node_new(pens);
    if(size == 0)
    {
        res->head = newNode;
    }
    else
    {
        node_t * cur = res->head;
        while(cur->next != NULL)
        cur = cur->next;
        cur->next = newNode;
    }
    res->size++;
}

void resourse_insert(resource_t * res, pensioner_t * pens, int index)
{
    if(index < 0 || index > res->size)
    {
        return;
    }
    if(index == res->size)
    {
        resource_push_back(res, pens);
        return;
    }
    node_t * cur = res->head;
    for(int i = 0; i < index; i++)
    {
        cur = cur.next;
    }
    node_t * newNode = node_new(pens);
    newNode->next = cur->next;
    cur->next = newNode;
    res->size++;
}

pensioner_t * resource_pop_back(resource_t * res) //!!
{
    if(res->size == 0)
    {
        return NULL;
    }
    node_t * delNode = res->tail;
    pensioner_t * pens = delNode->pens;
    res->head = res->head->next;

    node_free(delNode);
    res->size--;
    return pens;
}

pensioner_t * resource_remove(resourse_t * res, int index)
{
    if(index < 0 || index >= res->size)
    {
        return NULL;
    }
    node_t * cur = res->head;
    for(int i = 1; i < res->size; i++)
    {
        cur = cur->next;
    }
    node_t * delNode = cur->next;
    pensioner_t * pens = delNode->pens;
    cur->next = delNode->next;
    node_free(delNode);
    res->size--;
    return pens;
}

pensioner_t * resource_get(resource_t * res, int index)
{
    if(index < 0 || index >= res->size)
        return NULL;
    node_t * cur = res->head;
    for(int i = 0; i < index; i++)
    {
        cur = cur->next;
    }
    return cur->next->pens;
}

int resource_getSize(resource_t * res)
{
    return res->size;
}


static node_t * node_new(pensioner_t * pens)
{
    node_t * n = calloc(1, sizeof(struct node_s));
    n->next = NULL;
    memcpy(&n->pens, pens, sizeof(struct pensioner_s));
    return n;
}

static void node_free(node_t * n)
{
    free(n);
}


pensioner_t * resource_getById(resource_t * res, int id)
{
    for(int i = 0; i < res->cnt; i++)
    {
        if(res->pArr[i].id == id)
        {
            return &res->pArr[i];
        }
    }
    return NULL;
}

void resource_insert(resource_t * res, pensioner_t * pens)
{
    int newPensId = 1;
    while(1)
    {
        if(resource_getById(res, newPensId) != NULL)
            newPensId++;
        else
            break;
    }
    memcpy(&res->pArr[res->cnt], pens, sizeof(struct pensioner_s));
    res->pArr[res->cnt].id = newPensId;
    res->cnt++;
}

int resource_update(resource_t * res, pensioner_t * pens)
{
    for(int i = 0; i < res->cnt; i++)
    {
        if(res->pArr[i].id == pens->id)
        {
            memmove(&res->pArr[i], pens, sizeof(struct pensioner_s));
            return 1;
        }
    }
    return 0;
}

int resource_deletePens(resource_t * res, int id)
{
    if(res->cnt == 0)
    {
        return 0;
    }
    for(int i = 0; i < res->cnt; i++)
    {
        if(res->pArr[i].id == id)
        {
            if(i < res->cnt - 1)
            {
                memmove(&res->pArr[i], &ps[i + 1], (res->cnt - i - 1) * sizeof(struct pensioner_s));
                res->cnt--;
                memset(&res->pArr[res->cnt], 0, sizeof(struct pensioner_s));
            }
            else
            {
                memset(&res->pArr[i], 0, sizeof(struct pensioner_s));
                res->cnt--;
            }
            return i;
        }
    }
    return 0;
}

int resource_getCnt(resource_t * res)
{
    return res->cnt;
}

pensioner_t * resource_getList(resource_t * res)
{
    return res->pArr;
}
*/
