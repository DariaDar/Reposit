#include <stdlib.h>
#include "list.h"
#include "webpage.h"

struct webpage_s
{
    list_t * event_notification;
};

webpage_t * webpage_new()
{
    webpage_t * wp = malloc(sizeof(struct webpage_s));
    wp->event_notification = list_new();
    return wp;
}

void webpage_free(webpage_t * wp)
{
    int count = list_getCount(wp->event_notification);
    for(int i = 0; i < count; i++)
    {
        event_t * ev = list_pop_back(wp->event_notification);
        free(ev);
    }
    list_free(wp->event_notification);
    free(wp);
}

void webpage_subscribeNotification(webpage_t * wp, void * receiver, cb_notification fn)
{
    event_t * sb = malloc(sizeof(struct event_s));
    sb->receiver = receiver;
    sb->callback = fn;
    list_push_back(wp->event_notification, sb);
}

void webpage_sendMessage(webpage_t * wp, char * message)
{
    int count = list_getCount(wp->event_notification);
    for(int i = 0; i < count; i++)
    {
        event_t * ev = event_getElem(wp->event_notification, i);
        if(NULL != ev->callback)
        {
            cb_notification fn = (cb_notification)ev->callback;
            fn(ev->receiver, message);
        }
    }
}
