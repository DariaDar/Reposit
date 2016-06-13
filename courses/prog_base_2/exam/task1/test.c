#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>
int getNumber(char * str);

static void getNumber_EmptyString_NegatNum(void ** state)
{
    char str[] = "";
    assert_int_equal(getNumber(str), -1);
}

static void getNumber_StringWithoutNumber_ZeroNum(void ** state)
{
    char str[] = "helloBlaBla";
    assert_int_equal(getNumber(str), 0);
}

static void getNumber_StringWithIntNumber_ZeroNum(void ** state)
{
    char str[] = "HelloWorld3";
    assert_int_equal(getNumber(str), 0);
}
static void getNumber_EmptyString_NotNull(void ** state)
{
    char str[] = "";
    assert_non_null(str);
}
static void getNumber_StringWithNumbers_cnt(void ** state)
{
    char str[] = "BlahBlah2.0h7.2";
    assert_int_equal(getNumber(str), 2);
}

void test()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(getNumber_EmptyString_NegatNum),
        cmocka_unit_test(getNumber_StringWithoutNumber_ZeroNum),
        cmocka_unit_test(getNumber_StringWithIntNumber_ZeroNum),
        cmocka_unit_test(getNumber_EmptyString_NotNull),
        cmocka_unit_test(getNumber_StringWithNumbers_cnt)
    };
    cmocka_run_group_tests(tests, NULL, NULL);
}
