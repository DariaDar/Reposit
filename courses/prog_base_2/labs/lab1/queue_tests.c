#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "queue.h"
#include <cmocka.h>

typedef struct command
{
    int userNumb;
    int cmd;
    char * description;

} COMMAND;

static void new_emptyQueue_zeroCount(void ** state)
{
    queue_t queq = queue_new();
    assert_int_equal(queue_getCntElem(queq), 0);
    free(queq);
}

static void enqueue_UserCodeAndNumbOfCommandAndQueue_fullFieldQueue(void ** state)
{
    queue_t queq = queue_new();
    queue_enqueue(queq, 1, 5);
    assert_int_equal(queue_getLastUser(queq), 1);
    assert_int_equal(queue_getLastCommand(queq), 5);
    assert_int_equal(queue_getCntElem(queq), 1);
    free(queq);
}

static void dequeue_Oqueue_StructCommand(void ** state)
{
    queue_t queq = queue_new();
    int a;
    queue_enqueue(queq, 1, 5);
    queue_enqueue(queq, 2, 2);
    a = queue_dequeue(queq).userNumb;
    assert_int_equal(a,1);
    queue_delete(queq);
}

static void getLastUser_Queue_iUserNumb(void ** state)
{
    queue_t queq = queue_new();
    queue_enqueue(queq, 1, 5);
    queue_enqueue(queq, 2, 6);
    assert_int_equal(queue_getLastUser(queq), 2);
    assert_int_equal(queue_getLastCommand(queq), 6);
    free(queq);
}


static void getQEnd_Queue_iQend(void ** state)
{
    queue_t queq = queue_new();
    for(int i = 0; i < 10; i++)
        queue_enqueue(queq, 1, i);
    assert_int_equal(queue_getQEnd(queq), 10);
    free(queq);
}

static void countNull_Queue_zeroCount(void ** state)
{
    queue_t queq = queue_new();
    for(int i = 0; i < 10; i++)
        queue_enqueue(queq, 1, i);
    queue_countNull(queq);
    assert_int_equal(queue_getQEnd(queq), 0);
    free(queq);
}

void queue_tests()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_emptyQueue_zeroCount),
        cmocka_unit_test(enqueue_UserCodeAndNumbOfCommandAndQueue_fullFieldQueue),
        cmocka_unit_test(getLastUser_Queue_iUserNumb),
        cmocka_unit_test(getQEnd_Queue_iQend),
        cmocka_unit_test(countNull_Queue_zeroCount),
        cmocka_unit_test(dequeue_Oqueue_StructCommand)
    };
    cmocka_run_group_tests(tests, NULL, NULL);
}
