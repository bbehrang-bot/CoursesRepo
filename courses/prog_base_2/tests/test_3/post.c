#include <stdio.h>
#include <stdlib.h>
#include "blog.h"
#include "list.h"
#include "post.h"
#include "comment.h"
struct post_s{
    char body[10000];
    comment_t * cmtArr[100];
    int cmtSize;
    int id;

};
post_t * post_new(char * body,int id){
    post_t * post = malloc(sizeof(struct post_s));
    strcpy(post->body,body);
    post->cmtSize = 0;
    post->id = id;
}
void post_free(post_t *  self){
    free(self);
}
int post_getId(post_t * self){
    return self->id;
}
void post_edit(post_t * self,char * body,int id)
{
    self->id = id;
    strcpy(self->body,body);
}
void post_print(post_t * post)
{
    printf("Id = %d\nBody %s\n",post->id,post->body);
}
void post_printCmt(post_t * post)
{
    for(int i = 0 ; i<post->cmtSize;i++)
    {
        int id = comment_getId(post->cmtArr[i]);
        if(id!=-1)
            comment_print(post->cmtArr[i]);
    }
}
void post_deleteCmt(post_t * post,int id)
{
    for(int i = 0 ; i<post->cmtSize;i++)
    {
        int idd = comment_getId(post->cmtArr[i]);
        if(idd ==id )
            comment_print(post->cmtArr[i]);
    }
}
void post_addCmt(post_t * post,comment_t * cmt)
{
    post->cmtArr[post->cmtSize] = cmt;
}
