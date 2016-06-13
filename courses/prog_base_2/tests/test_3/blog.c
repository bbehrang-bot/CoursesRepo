#include <stdio.h>
#include <stdlib.h>
#include "blog.h"
#include "post.h"
#include "list.h"
struct blog_s{
    char title[100];
    list_t * posts;
    user_t * userArray[100];
    int userSize;
    int id;
};
blog_t * blog_new(char * title,int id){
    blog_t * blog = malloc(sizeof(struct blog_s));
    strcpy(blog->title,title);
    blog->id = id;
    blog->posts = list_new();
    blog->userSize = 0;
    return blog;
}
void blog_addUser(blog_t * blog,user_t * user)
{
    blog->userArray[userSize] = user;
    blog->userSize++;
}
blog_t * blog_addPost(blog_t * blog,post_t * post)
{
    list_push_back(blog->posts,post);
}
void blog_free(blog_t *  self){
    free(self);
}
int blog_getId(blog_t * self){
    return self->id;
}
