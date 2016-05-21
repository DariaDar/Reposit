#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "list.h"
#include <cmocka.h>


static void new_void_Struct(void ** state)
{
    list_t * lt = list_new();
    assert_null(list_getCount(lt));
    free(lt);
};

static void push_back_ListAndEvent_CountElem(void ** state)
{
    list_t * lt = list_new();
    event_t * ev = calloc(1, sizeof(struct event_s));
    ev->receiver = NULL;
    ev->callback = NULL;
    list_push_back(lt, ev);
    assert_int_equal(list_getCount(lt), 1);
    free(ev);
    free(lt);
}


static void push_back_ListAndEvent_PushedEvent(void ** state)
{
    list_t * lt = list_new();
    event_t * ev = calloc(1, sizeof(struct event_s));
    ev->receiver = NULL;
    ev->callback = NULL;
    list_push_back(lt, ev);
    assert_memory_equal(list_getElem(lt, 0), ev, 0);
    free(ev);
    free(lt);
}

static void pop_back_List_ZeroCount(void ** state)
{
    list_t * lt = list_new();
    event_t * ev = calloc(1, sizeof(struct event_s));
    ev->receiver = NULL;
    ev->callback = NULL;
    list_push_back(lt, ev);
    list_pop_back(lt);
    assert_int_equal(list_getCount(lt), 0);
    free(ev);
    free(lt);
}

static void pop_back_List_Event(void ** state)
{
    list_t * lt = list_new();
    event_t * ev = calloc(1, sizeof(struct event_s));
    ev->receiver = NULL;
    ev->callback = NULL;
    list_push_back(lt, ev);
    assert_memory_equal(list_pop_back(lt), ev, 0);
    free(ev);
    free(lt);
}


void user_tests()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_void_Struct),
        cmocka_unit_test(push_back_ListAndEvent_CountElem),
        cmocka_unit_test(push_back_ListAndEvent_PushedEvent),
        cmocka_unit_test(pop_back_List_ZeroCount),
        cmocka_unit_test(pop_back_List_Event)
    };
    cmocka_run_group_tests(tests, NULL, NULL);
}
