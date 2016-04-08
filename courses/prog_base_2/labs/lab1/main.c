#include <stdio.h>
#include <stdlib.h>
#include "Turnstile.h"
#include "windows.h"

int main()
{
     user_t * userStudentArray[20] =
     {
     user_new("Behrang","Behvandi",1), user_new("Mikhaeil","Ivanon",1),
     user_new("Maxim","Gonchar",1),user_new("Valery","Babenko",1),user_new("Sasha","Voloshenko",1),
     user_new("Denis","Medvedski",1),user_new("Anton","Mazun",1),user_new("Sergey","Romaniuk",1),
     user_new("Fedya","Andrienko",1),user_new("Kolia","Sherstiuk",1),
     user_new("Ruslan","Hadinyak",2), user_new("Joey","BadA$$",2),
     user_new("Kendrick","Lamar",2),user_new("Lil","Wayne",2),user_new("Chance","TheRapper",2),
     user_new("J","Cole",2),user_new("Young","Thug",2),user_new("Young","Metro",2),
     user_new("808","Mafia",2),user_new("Erfan","Paydar",2),
     };
     turnstile_t * ts1 = turnstile_new(1,0);
     turnstile_pass(ts1,userStudentArray[0]);
     turnstile_pass(ts1,userStudentArray[3]);
     turnstile_pass(ts1,userStudentArray[5]);
     turnstile_pass(ts1,userStudentArray[15]);
     turnstile_pass(ts1,userStudentArray[19]);
     turnstile_print(ts1);
     turnstile_print_byId(ts1,1);

    return 0;
}
