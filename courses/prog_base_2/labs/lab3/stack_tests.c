#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "stack.h"
#include <cmocka.h>


static void new_iNumber_Struct(void ** state)
{
    stack_t * self = stack_new(1);
    assert_int_equal(stack_getCount(self), -1);
    assert_int_equal(stack_getStackNum(self), 1);
    free(self);
}

static void push_StackIntValue_PushedValue(void ** state)
{
    stack_t * st = stack_new(1);
    int val = 25;
    stack_push(st, val);
    assert_int_equal(stack_peek(st), 25);
    free(st);
}

static void pop_StackIntVal_PopedVal(void ** state)
{
    stack_t * st = stack_new(1);
    stack_push(st, 15);
    assert_int_equal(stack_pop(st), 15);
    free(st);
}

static void getCount_Stack_IntNum(void ** state)
{
    stack_t * st = stack_new(1);
    for(int i = 0; i < 5; i++)
        stack_push(st, i);
    assert_int_equal(stack_getCount(st), 4);
    free(st);
}

static void peek_Stack_intNum(void ** state)
{
    stack_t * st = stack_new(1);
    stack_push(st, 2);
    assert_int_equal(stack_peek(st), 2);
    free(st);
}


void user_tests()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_iNumber_Struct),
        cmocka_unit_test(push_StackIntValue_PushedValue),
        cmocka_unit_test(pop_StackIntVal_PopedVal),
        cmocka_unit_test(getCount_Stack_IntNum),
        cmocka_unit_test(peek_Stack_intNum)
    };
    cmocka_run_group_tests(tests, NULL, NULL);
}
