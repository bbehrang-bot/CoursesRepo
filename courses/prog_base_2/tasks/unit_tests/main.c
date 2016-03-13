#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "intlist.h"
#include <cmocka.h>
static void getSize_emptyListCheck(void **state)
{
    intList_t list1 = intList_new();
    assert_int_equal(0, intList_getSize(list1));
}
static void getSize_fiveElementsCheck(void **state)
{
    intList_t list1 = intList_new();
    intList_add(list1,-1,0);
    intList_add(list1,1,1);
    intList_add(list1,2,2);
    intList_add(list1,3,3);
    intList_add(list1,4,4);
    assert_int_equal(5, intList_getSize(list1));
}
static void getAtIndex_fiveElementsCheck(void **state)
{
    intList_t list1 = intList_new();
    int i;
    for(i =0;i<5;i++)
    {
        intList_add(list1,i,i);
    }
    for(i=0;i<5;i++)
    {
        assert_int_equal(i, intList_getAtIndex(list1,i));
    }

}
static void removeL_deleteThreeElements(void **state)
{
    intList_t list1 = intList_new();
    intList_add(list1,-1,0);
    assert_int_equal(-1, intList_getAtIndex(list1,0));
    intList_add(list1,1,1);
    assert_int_equal(1, intList_getAtIndex(list1,1));
    intList_add(list1,2,2);
    assert_int_equal(2, intList_getAtIndex(list1,2));
}
static void getMax_checkMaxValue(void **state)
{
    intList_t list1 = intList_new();
    int i;
    for(i =0;i<50;i++)
    {
        intList_add(list1,i,i);
    }
    intList_add(list1,100,50);
     for(i =51;i<70;i++)
    {
        intList_add(list1,i,i);
    }
     assert_int_equal(100, intList_getMax(list1));
}
static void getMax_checkMinValue(void **state)
{
    intList_t list1 = intList_new();
    int i;
    for( i =0;i<50;i++)
    {
        intList_add(list1,i,i);
    }
    intList_add(list1,-100,50);
     for( i =51;i<70;i++)
    {
        intList_add(list1,i,i);
    }
     assert_int_equal(-100, intList_getMin(list1));
}

int main()
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(getSize_emptyListCheck),
        cmocka_unit_test(getSize_fiveElementsCheck),
        cmocka_unit_test(getAtIndex_fiveElementsCheck),
        cmocka_unit_test(removeL_deleteThreeElements),
        cmocka_unit_test(getMax_checkMaxValue),
        cmocka_unit_test(getMax_checkMinValue)

    };
    return cmocka_run_group_tests(tests, NULL, NULL);


}
