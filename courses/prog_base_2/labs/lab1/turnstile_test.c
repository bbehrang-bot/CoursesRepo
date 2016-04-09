#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "Turnstile.h"
static void nnew_id_isSet(void **state)
{
    turnstile_t * ts =turnstile_new(1);
    int idSet = turnstile_get_id(ts);
    int correct = 1;
    turnstile_free(ts);
    assert_int_equal(idSet,correct);
}
static void passed_count_wasEmpty_hasThree(void **state)
{
    turnstile_t * ts =turnstile_new(1);
    int funcRes = turnstile_passed_count(ts);
    int correct = 0;
    assert_int_equal(funcRes,correct);
    user_t * user1 =user_new("Random","guy",3);
    user_t * user2 =user_new("Random","american",3);
    user_t * user3 =user_new("Random","girl",3);
    turnstile_pass(ts,user1);
    turnstile_pass(ts,user2);
    turnstile_pass(ts,user3);
    funcRes = turnstile_passed_count(ts);
    correct = 3;
    user_free(user1);
    user_free(user2);
    user_free(user3);
    turnstile_free(ts);
    assert_int_equal(funcRes,correct);

}
static void passed_Count_byType_wasZero_passedThreeType3(void **state)
{
    turnstile_t * ts =turnstile_new(1);
    int funcRes = turnstile_passed_Count_byType(ts,1);
    int correct = 0;
    assert_int_equal(funcRes,correct);
    user_t * user1 =user_new("Random","guy",3);
    user_t * user2 =user_new("Random","american",3);
    user_t * user3 =user_new("Random","girl",3);
    turnstile_pass(ts,user1);
    turnstile_pass(ts,user2);
    turnstile_pass(ts,user3);
    funcRes = turnstile_passed_Count_byType(ts,3);
    correct = 3;
    assert_int_equal(funcRes,correct);
    user_free(user1);
    user_free(user2);
    user_free(user3);
    turnstile_free(ts);
}
static void get_last_error_wasOk_ok(void **state)
{
    turnstile_t * ts = turnstile_new(1);
    turnstile_passed_count(ts);
    int funcRes = turnstile_get_last_error();
    int correct = TURNSTILE_OK;
    assert_int_equal(funcRes,correct);
    turnstile_free(ts);
}
static void get_last_error_isFull_full(void **state)
{
    turnstile_t * ts = turnstile_new(1);
    for(int i=0;i<200;i++)
    {
        user_t * user1 = user_new("b","e",2);
        turnstile_pass(ts,user1);


    }
    int status = turnstile_get_last_error();
    int correct = 3;
    assert_int_equal(status,correct);
    turnstile_free(ts);

}
void turnstle_unit_test() {

    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(nnew_id_isSet),
        cmocka_unit_test(passed_count_wasEmpty_hasThree),
        cmocka_unit_test(passed_Count_byType_wasZero_passedThreeType3),
        cmocka_unit_test(get_last_error_wasOk_ok),
        cmocka_unit_test(get_last_error_isFull_full)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
