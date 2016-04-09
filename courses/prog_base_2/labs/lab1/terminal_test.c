#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdio.h>
#include <cmocka.h>
#include "terminal.h"
static void new_id_isSet(void **state)
{
    terminal_t * terminal =terminal_new(1);
    int idSet = terminal_get_id(terminal);
    int correct = 1;
    assert_int_equal(idSet,correct);
    terminal_free(terminal);

}
static void ppassed_count_wasEmpty_hasThree(void **state)
{
    terminal_t * terminal = terminal_new(1);
    int funcRes = terminal_passed_count(terminal);
    int correct = 0;
    assert_int_equal(funcRes,correct);
    user_t * user1 =user_new("Random","guy",3);
    user_t * user2 =user_new("Random","american",3);
    user_t * user3 =user_new("Random","girl",3);
    turnstile_t * ts1 = turnstile_new(1);
    turnstile_pass(ts1,user1);
    turnstile_pass(ts1,user2);
    turnstile_t* ts2 = turnstile_new(2);
    turnstile_pass(ts2,user3);
    terminal_add_turnstile(terminal,ts1);
    terminal_add_turnstile(terminal,ts2);
    funcRes = terminal_passed_count(terminal);
    correct = 3;
    assert_int_equal(funcRes,correct);
    terminal_free(terminal);

}
static void ppassed_Count_byType_wasZero_passedThreeType3(void **state)
{
    terminal_t * terminal = terminal_new(1);
    int funcRes = terminal_passed_count_byType(terminal,3);
    int correct = 0;
    assert_int_equal(funcRes,correct);
    user_t * user1 =user_new("Random","guy",3);
    user_t * user2 =user_new("Random","american",3);
    user_t * user3 =user_new("Random","girl",3);
    turnstile_t * ts1 = turnstile_new(1);
    turnstile_pass(ts1,user1);
    turnstile_pass(ts1,user2);
    turnstile_t* ts2 = turnstile_new(2);
    turnstile_pass(ts2,user3);
    terminal_add_turnstile(terminal,ts1);
    terminal_add_turnstile(terminal,ts2);
    funcRes = terminal_passed_count_byType(terminal,3);
    correct = 3;
    assert_int_equal(funcRes,correct);
    user_free(user1);
    user_free(user2);
    user_free(user3);
    turnstile_free(ts1);
    turnstile_free(ts2);
    terminal_free(terminal);
}
static void gget_last_error_wasOk_ok(void **state)
{
    terminal_t * terminal = terminal_new(1);
    int tmp = terminal_passed_count(terminal);
    int funcRes = terminal_get_last_error();
    int correct = TERMINAL_OK;
    terminal_free(terminal);
    assert_int_equal(funcRes,correct);
}

void terminal_unit_test() {

    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(new_id_isSet),
        cmocka_unit_test(ppassed_count_wasEmpty_hasThree),
        cmocka_unit_test(ppassed_Count_byType_wasZero_passedThreeType3),
        cmocka_unit_test(gget_last_error_wasOk_ok)

    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
