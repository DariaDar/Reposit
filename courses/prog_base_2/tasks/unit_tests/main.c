#include <stdio.h>
#include "text.h"
#include <string.h>

#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <cmocka.h>

  static void new_CntMaxAndString_OneString(void ** state)
{
    text_t text = text_new(15, "hello");
    assert_int_equal(text_getRealCntStr(text), 1);
    text_delete(text);
}

static void Insert_hasIndexAndString_returnsCntTwo(void ** state)
{
    text_t text = text_new(15, "hello");
    int index = 1;
    char * str = "London";
    text_Insert(text,index,str);
    assert_int_equal(text_getRealCntStr(text), 2);
    text_delete(text);
}

static void deleteStr_hasOneValue_returnsZeroValue(void ** state)
{
    text_t text = text_new(15, "hello");
    text_deleteStr(text, 0);
    assert_int_equal(text_getRealCntStr(text), 0);
    text_delete(text);
}

static void setFormat_indexAndFormatNumber_FormatNumber(void ** state)
{
    text_t text = text_new(15, "hello");
    for(int formatNumber = 0; formatNumber < 3; formatNumber++)
    {
        text_setFormat(0, formatNumber, text);
        assert_int_equal(text_getFormat(text,0), formatNumber);
    }
    text_delete(text);
}

static void getStrSpecForm_formatAndStruct_ArrayOfPointersWthStrSpecialFormat(void ** state)
{
    text_t text = text_new(15, "hello");
    int index = 1;
    int formatNumber = 1;
    char * str = "Denmark";
    text_Insert(text,index,str);
    text_setFormat(index, formatNumber, text);
    char ** arr = text_getStrSpecForm(text,formatNumber);
    assert_int_equal(strlen(arr[formatNumber]),strlen(str));

}
static void getFormat_IndexOfString_formatOfString(void ** state)
{
    text_t text = text_new(15, "hello");
    int index = 0;
    assert_int_equal(text_getFormat(text,index), 0);
    text_delete(text);
}
static void getString_IndexOfString_SelectedStr(void ** state)
{
    text_t text = text_new(15, "hello");
    int index = 1;
    char * str = "Sim";
    text_Insert(text,index,str);
    assert_int_equal(strlen(text_getString(text, 1)), 3);
    text_delete(text);
}

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_CntMaxAndString_OneString),
        cmocka_unit_test(Insert_hasIndexAndString_returnsCntTwo),
        cmocka_unit_test(deleteStr_hasOneValue_returnsZeroValue),
        cmocka_unit_test(setFormat_indexAndFormatNumber_FormatNumber),
        cmocka_unit_test(getStrSpecForm_formatAndStruct_ArrayOfPointersWthStrSpecialFormat),
        cmocka_unit_test(getFormat_IndexOfString_formatOfString),
        cmocka_unit_test(getString_IndexOfString_SelectedStr)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
