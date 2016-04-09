#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "user.h"
static enum USER_STATUS status = USER_OK;
struct user_s
{
    char fName[100];
    char lName[100];
    int id; ///ID student = 1, teacher = 2, staff = 3;
};

///Methods
user_t * user_new_empty()
{
    user_t * user_out = malloc(sizeof(struct user_s));
    return user_out;
}
user_t * user_new(char * fName, char * lName, int id)
{
    user_t * user_out = malloc(sizeof(struct user_s));
    if(user_out == NULL)
    {
        status = USER_ERROR_NO_MEMORY;
        return NULL;
    }
    if(id < 1 || id > 3)
    {
        status = USER_ERROR_INCORRECT_ID;
        return NULL;
    }
    strcpy(user_out->fName,fName);
    strcpy(user_out->lName,lName);
    if(strlen(user_out->fName) == NULL || strlen(user_out->lName) == NULL)
    {
        status = USER_ERROR_INCORRECT_NAME;
        return NULL;
    }
    user_out->id = id;
    status = USER_OK;
    return user_out;
}
int user_get_id(user_t * user)
{
    if(user == NULL)
    {
        status = USER_ERROR_NULL_PTR;
        return;
    }
    status = USER_OK;
    return user->id;
}
void user_print(user_t * user)
{
    char *type;
    if(user->id==1)
        strcpy(type,"type = student");
    else if(user->id==2)
        strcpy(type,"type = teacher");
    else if(user->id==3)
       strcpy(type,"type = staff");
    if(user == NULL)
    {
        status = USER_ERROR_NULL_PTR;
        return;
    }
    printf("%s %s %s ,",user->fName,user->lName,type);
    status = USER_OK;
}
void user_print_array(size_t size,user_t * user[size])
{
    for(int i = 0; i<size;i++)
    {
        if(user[i]==NULL)
        {
        status = USER_ERROR_NULL_PTR;
        return;
        }
        user_print(user[i]);
    }
    status = USER_OK;
}
void user_free(user_t * user)
{
    if(user == NULL)
    {
        status = USER_ERROR_NULL_PTR;
        return;
    }
    free(user);
    status = USER_OK;
}
void user_free_array(size_t size,user_t * user[size])
{
    for(int i=0;i<size;i++)
    {
        if(user[i]==NULL)
        {
        status = USER_ERROR_NULL_PTR;
        return;
        }
        user_free(user[i]);
        status = USER_OK;
    }

}
USER_STATUS user_get_last_error()
{
    return status;
}
const char * turnstile_strstatus(USER_STATUS status)
{

    static const char * strstatus =
    {"USER_OK","USER_ERROR_INCORRECT_ID","USER_ERROR_INCORRECT_NAME", "USER_ERROR_NULL_PTR", "USER_ERROR_NO_MEMORY"};
    return strstatus[status];

}


