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
#include "database.h"
#include "student.h"
int main(int argc,char ** argv)
{
    /*blog_t * blog = blog_new("my blog",1);

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
    */
    char path[100];
    strcpy(path,argv[0]);
    db_t * db = db_new("student.db");

    int rc = db_tableExists(db);
    if(rc == 0)
    {
        db_creatTable(db);
        puts("Doesnt exist Created");
    }
    printf("%d",rc);
    printf("Type 1 to Add new student , Type 2 to delete students\n");
    int choice=0;
    scanf("%d",&choice);
    if(choice == 1)
    {
    char firstName[100];
    char secondName[100];
    char middleName[100];
    char date[10];
    int number;

    puts("Type Name");
    scanf("%s",&firstName);
    puts("Type secondName");
    scanf("%s",&secondName);
    puts("Type middleName");
    scanf("%s",&middleName);
    puts("Type date in this format YY.MM.DD");
    scanf("%s",&date);
    puts("Type Zalik Number");
    scanf("%d",&number);
    student_t * student = student_new(firstName,secondName,middleName,date,number);
    db_addStudent(db,student);
    }
    else if(choice ==2)
    {
        char date[4];
        scanf("%s",&date);

        int deleted = db_removeStudent(db,date);
        printf("DELETED COUNT %d");
    }



    return 0;
}
