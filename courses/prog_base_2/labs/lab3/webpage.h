#ifndef WEBPAGE_H
#define WEBPAGE_H

typedef struct webpage_s webpage_t;

typedef void (*cb_notification)(void * receiver, char * message);

webpage_t * webpage_new();
void webpage_free(webpage_t * wp);
void webpage_subscribeNotification(webpage_t * wp, void * receiver, cb_notification fn);
void webpage_sendMessage(webpage_t * wp, char * message);



#endif // WEBPAGE_H
