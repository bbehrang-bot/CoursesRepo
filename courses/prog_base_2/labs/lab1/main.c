#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "terminal.h"
#include "windows.h"
void user_unit_test();
void turnstle_unit_test();
void terminal_unit_test();
int main()
{

     user_unit_test();
     puts(""); puts("");
     turnstle_unit_test();
     puts("");puts("");
     terminal_unit_test();
     puts("");puts("");


     user_t * userStudentArray[30] =
     {
     ///Adding Students
     user_new("Behrang","Behvandi",1), user_new("Mikhaeil","Ivanon",1),
     user_new("Maxim","Gonchar",1),user_new("Valery","Babenko",1),user_new("Sasha","Voloshenko",1),
     user_new("Denis","Medvedski",1),user_new("Anton","Mazun",1),user_new("Sergey","Romaniuk",1),
     user_new("Fedya","Andrienko",1),user_new("Kolia","Sherstiuk",1),
     ///
     ///Adding Teachers
     user_new("Ruslan","Hadinyak",2), user_new("Joey","BadA$$",2),
     user_new("Kendrick","Lamar",2),user_new("Lil","Wayne",2),user_new("Chance","TheRapper",2),
     user_new("J","Cole",2),user_new("Young","Thug",2),user_new("Young","Metro",2),
     user_new("808","Mafia",2),user_new("Erfan","Paydar",2),
     ///
     ///Adding Staff
     user_new("Random","guy",3), user_new("Random","american",3),
     user_new("Random","girl",3),user_new("Random","persian",3),user_new("Random","mad",2),
     user_new("Random","chinese",3),user_new("Random","italian",3),user_new("Random","Metro",2),
     user_new("Random","african",3),user_new("Random","ukrainian",3),
     };

     turnstile_t * ts1 = turnstile_new(1);
     turnstile_pass(ts1,userStudentArray[0]);
     turnstile_pass(ts1,userStudentArray[3]);
     turnstile_pass(ts1,userStudentArray[5]);
     turnstile_pass(ts1,userStudentArray[15]);
     turnstile_pass(ts1,userStudentArray[21]);

     turnstile_t * ts2 = turnstile_new(2);
     turnstile_pass(ts2,userStudentArray[14]);
     turnstile_pass(ts2,userStudentArray[13]);
     turnstile_print(ts1);
     puts("");
     turnstile_print(ts2);
     turnstile_print_byType(ts1,1);
     puts("");
     terminal_t* terminal1 = terminal_new(1);
     terminal_add_turnstile(terminal1,ts1);
     terminal_add_turnstile(terminal1,ts2);
     //printf("passed terminal %i \n",terminal_passed_count(terminal1));
     terminal_print_passed_count(terminal1);

     //printf("Terminal passed type %i\n",terminal_passed_count_byType(terminal1,2));
     terminal_print_passed_byType(terminal1,2);
     puts(""); puts("");
     terminal_print(terminal1);
     user_free_array(30,userStudentArray);
     turnstile_free(ts1);
     turnstile_free(ts2);
     terminal_free(terminal1);

     return 0;
}
