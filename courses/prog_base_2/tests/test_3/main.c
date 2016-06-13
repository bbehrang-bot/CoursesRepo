#include <stdio.h>
#include <stdlib.h>
#include "task1.h"
#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !
#include <cmocka.h>
#include "user.h"
#include "blog.h"
#include "list.h"
#include "post.h"
int main()
{
    blog_t * blog = blog_new("my blog",1);

    //cmockaTest();
    user_t * user1 = user_new(1,"behrang","Iran",18);
    user_t * user2 = user_new(2,"Ruslan","Gadiniak",18);
    user_t * user3 = user_new(3,"Misha","Ivanov",18);

    blog_addUser(blog,user1);
    blog_addUser(blog,user2);
    blog_addUser(blog,user3);

    blog_printUsers(blog);

    blog_deleteUser(blog,3);
    puts("Removing Id 3");
    blog_printUsers(blog);
    puts("Getting Id 2");
    user_t * user4 = blog_getUser(blog,2);
    user_print(user4);



    return 0;
}
