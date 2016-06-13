#include <stdio.h>
#include <stdlib.h>
#include "blog.h"
#include "list.h"
#include "post.h"
#include "comment.h"
struct comment_s{
    char body[10000];
    int id
};
comment_t * comment_new(char * body,int id)
{
    comment_t * cmt = malloc(sizeof(struct comment_s));
    strcpy(cmt->body,body);
    cmt->id = id;
}
void comment_free(comment_t *  self){
    free(self);
}
int comment_getId(comment_t * self){
    return self->id;
}
void comment_print(comment_t * self){
    printf("comment id : %d\nComment Body : %s",self->id,self->body);
}
void comment_delet(comment_t * self){
    strcpy(self->body,"Empty");
    self->id = -1;
}
