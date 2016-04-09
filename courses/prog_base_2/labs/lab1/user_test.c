#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdio.h>
#include <cmocka.h>
#include "user.h"
static void get_id_isStudent_Student(void **state)
{
    user_t * user1 =user_new("Behrang","Behvandi",1);
    int funcRes = user_get_id(user1);
    int correct = 1;
    user_free(user1);
    assert_int_equal(funcRes,correct);
}
static void get_id_isTeacher_Teacher(void **state)
{
    user_t * user2 =user_new("Maxim","Gonchar",2);
    int funcRes = user_get_id(user2);
    int correct = 2;
    assert_int_equal(funcRes,correct);
    user_free(user2);
}
static void get_id_isStaff_Staff(void **state)
{
    user_t * user3 =user_new("Valery","Babenko",3);
    int funcRes = user_get_id(user3);
    int correct = 3;
    assert_int_equal(funcRes,correct);
    user_free(user3);
}
static void get_last_error_setOutOfRange_invalid(void **state)
{
    user_t * user1 =user_new("Behrang","Behvandi",4);
    int funcRes = user_get_last_error();
    int correct = USER_ERROR_INCORRECT_ID;
    assert_int_equal(funcRes,correct);
    user_free(user1);
}
static void get_last_error_emptyName_incorrectName(void **state)
{
    user_t * user1 =user_new("","",1);
    int funcRes = user_get_last_error();
    int correct = USER_ERROR_INCORRECT_NAME;
    assert_int_equal(funcRes,correct);
    user_free(user1);
}

void user_unit_test() {

    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(get_id_isStudent_Student),
        cmocka_unit_test(get_id_isTeacher_Teacher),
        cmocka_unit_test(get_id_isStaff_Staff),
        cmocka_unit_test(get_last_error_setOutOfRange_invalid),
        cmocka_unit_test(get_last_error_emptyName_incorrectName)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
