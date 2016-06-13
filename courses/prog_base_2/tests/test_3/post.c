#include <stdio.h>
#include <stdlib.h>
#include "blog.h"
#include "list.h"
struct post_s{
    char body[10000];
    int id;
};
post_t * post_new(char * body,int id){
    post_t * post = malloc(sizeof(struct post_s));
    strcpy(post->body,body);
    post->id = id;
}
void free(post_t *  self){
    free(self);
}
int post_getId(post_t * self){
    return self->id;
}
