#include <stdio.h>
#include <stdlib.h>
#include "user.h"
struct user_s{
    int id;
    char name[100];
    char country[100];
    int age;
};
user_t * user_new(int id,char * login,char * country,int age){
    user_t * self = malloc(sizeof(struct user_s));
    self->id = id;
    strcpy(self->name,login);
    strcpy(self->country,country);
    self->age = age;
    return self;
}
void free(user_t *  self){
    free(self);
}
int user_getId(user_t * self){
    int id = self->id;
    return id;
}
