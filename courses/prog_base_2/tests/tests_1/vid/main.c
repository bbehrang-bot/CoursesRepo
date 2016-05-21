#include <stdlib.h>
#include <stdio.h>
#include "VideoPlayer.h"
#include "list.h"
#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>
#include "list.h"
/*static void remove_TwoElements_CheckSize(void **state)
{
    list_t list = list_new();
    film_t * film = film_new("Shutter Island",1);
    film_t * film1 = film_new("Shutter",2);
    film_t * film2 = film_new("Island",3);
    film_t * film3 = film_new("Shutterjkhk Island",4);
    list_insert(list, film, 0);
    list_insert(list, film1, 1);
    list_insert(list, film2, 2);
    list_insert(list, film3, 3);
    list_remove(list, 0);
    assert_int_equal(3, list_get_size(list));
    list_remove(list, 0);
    assert_int_equal(2, list_get_size(list));
    list_delete(list);
}
int main(void)
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(remove_TwoElements_CheckSize)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
*/
int main(void)
{
    videoPlayer_t * vid = videoPlayer_new(3);
    film_t * film = film_new("Shutter Island",1);
    film_t * film1 = film_new("Shutter",2);
    film_t * film2 = film_new("Island",3);
    film_t * film3 = film_new("Shutterjkhk Island",4);

    videoPlayer_add(vid,film,0);
    videoPlayer_add(vid,film1,1);
    videoPlayer_add(vid,film2,2);
    videoPlayer_add(vid,film3,3);
    videoPlayer_print(vid);
    videoPlayer_play(vid,0);
    return 0;
}
