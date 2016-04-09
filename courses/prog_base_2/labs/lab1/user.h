#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include <stdlib.h>
typedef struct user_s user_t; //User type
typedef enum user_type { STUDENT = 1 , TEACHER , STAFF} user_type;
typedef enum USER_STATUS
{USER_OK, USER_ERROR_INCORRECT_ID,USER_ERROR_INCORRECT_NAME, USER_ERROR_NULL_PTR, USER_ERROR_NO_MEMORY} USER_STATUS;//Store last status
user_t * user_new_empty();
user_t * user_new(char * fName, char * lName, int id); //User constructor , firstname,lastname,id
void user_free(user_t * user);//free user memory
int user_get_id(user_t * user);//get user id
void user_print(user_t * user);//print user
void user_print_array(size_t size ,user_t * user[size]);//print an array of users
void user_free_array(size_t size,user_t * user[size]);//free memory of an array of users


USER_STATUS user_get_last_error(); //GET last error status
const char * user_strstatus(USER_STATUS status);//get error message
#endif // USER_H_INCLUDED
