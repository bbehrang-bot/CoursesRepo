#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user.h"

struct user_s
{
    char fName[100]; ///firstName
    char lName[100]; ///LastName
    int id; ///ID student = 1, teacher = 2, staff = 3;
};

///Methods
user_t * user_new(char * fName, char * lName, int id)
{
    user_t * user_out = malloc(sizeof(struct user_s));
    if(user_out == NULL)
    {
        puts("Memory error upon creation, User not Created");
        return NULL;
    }
    if(id < 1 || id > 3)
    {
        puts("invalid id range , user not created");
        return NULL;
    }
    strcpy(user_out->fName,fName);
    strcpy(user_out->lName,lName);
    user_out->id = id;

    return user_out;
}
void user_print(user_t * user)
{
    printf("%s ",user->fName);
    printf("%s ",user->lName);
    //printf("%i ",user->id);
}
void user_print_array(size_t size,user_t * user[size])
{
    for(int i = 0; i<size;i++)
        user_print(user[i]);
}
void user_free(user_t * user)
{
    free(user);
}
void user_free_array(size_t size,user_t * user[size])
{
    for(int i=0;i<size;i++)
        user_free(user[i]);
}


