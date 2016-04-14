#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>
#include "user.h"

 static void new_iUserCode_oneIntegerNum(void ** state)
 {
    int iUserCode = 1;
    user_t user = user_new(iUserCode);
    assert_int_equal(user_getUserCode(user), 1);
    free(user);
 }

 static void new_NegUserCode_NULL(void ** state)
 {
     user_t user = user_new(-1);
     assert_null(user);
     free(user);
 }

 static void getUserCode_UserStructure_iUserCode(void ** state)
 {
     user_t user = user_new(2);
     assert_int_equal(user_getUserCode(user), 2);
     free(user);
 }

void user_tests()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_iUserCode_oneIntegerNum),
        cmocka_unit_test(getUserCode_UserStructure_iUserCode),
        cmocka_unit_test(new_NegUserCode_NULL)
    };
    cmocka_run_group_tests(tests, NULL, NULL);
}
