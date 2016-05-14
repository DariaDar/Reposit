#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "stack.h"
#include <cmocka.h>


static void new_void_list(void ** state)
{
    list_t * lt = list_new();
    assert_int_equal(list_getCount(lt), 0);
    free(lt);
}


static void pushBack_ListEvent_PushedVal(void ** state)
{
    list_t * lt = list_new();
    event_t * ev =
}
static void popBack_List_EventElem(void ** state)
{
    list_t * lt = list_new();

}





void list_tests()
{
     const struct CMUnitTest tests[] =
     {
         cmocka_unit_test(new_void_list)
     };
     cmocka_run_group_tests(tests, NULL, NULL);
}
