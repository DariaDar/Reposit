#ifndef USER_H_
#define USER_H_
#include "queue.h"

typedef struct user_s * user_t;

user_t user_new(int userCode);
void user_delete(user_t pStruct);
int user_getUserCode(user_t pUser);


#endif // USER_H


