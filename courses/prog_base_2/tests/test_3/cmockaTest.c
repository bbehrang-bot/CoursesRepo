#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !
#include "task1.h"
#include <cmocka.h>

static void strings_exist_simple(void ** state) {
    strings_t * str = strings_new("behrang","beh");
    int res = strings_exist(str);
    assert_int_equal(1,res);
    strings_free(str);
}
static void strings_exist_with_Space(void ** state) {
    strings_t * str = strings_new("al i rajabi","ali");
    int res = strings_exist(str);
    assert_int_equal(-1,res);
    strings_free(str);
}
static void strings_exist_with_lineBreak(void ** state) {
    strings_t * str = strings_new("al\ni rajabi","ali");
    int res = strings_exist(str);
    assert_int_equal(1,res);
    strings_free(str);
}
void cmockaTest(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(strings_exist_simple),
		cmocka_unit_test(strings_exist_with_Space),
		cmocka_unit_test(strings_exist_with_lineBreak)
	};
	cmocka_run_group_tests(tests, NULL, NULL);
}
