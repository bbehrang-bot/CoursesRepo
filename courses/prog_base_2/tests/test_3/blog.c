#include <stdio.h>
#include <stdlib.h>
#include "blog.h"
#include "post.h"
#include "list.h"
#include "user.h"
struct blog_s{
    char title[100];
    post_t * postsArr[100];
    user_t * userArr[100];
    int userSize;
    int postSize;
    int id;
};
blog_t * blog_new(char * title,int id){
    blog_t * blog = malloc(sizeof(struct blog_s));
    strcpy(blog->title,title);
    blog->id = id;
    blog->postSize = 0;
    blog->userSize = 0;
    return blog;
}
void blog_addUser(blog_t * blog,user_t * user)
{
    int size = blog->userSize;
    blog->userArr[blog->userSize] = user;
    blog->userSize++;
}
blog_t * blog_addPost(blog_t * blog,post_t * post)
{
     blog->postsArr[blog->postSize] = post;
     blog->postSize++;
}
void blog_free(blog_t *  self){
    free(self);
}
int blog_getId(blog_t * self){
    return self->id;
}
void blog_printUsers(blog_t* self)
{
    for(int i=0;i<self->userSize;i++)
    {
        int id = user_getId(self->userArr[i]);
         if(id != -1)
             user_print(self->userArr[i]);
    }

}
void blog_deleteUser(blog_t * self,int id)
{
    for(int i=0;i<self->userSize;i++)
    {
        int idU = user_getId(self->userArr[i]);
        if(idU == id)
        {
            user_edit(self->userArr[i],-1,"unknown","unknown",-1);
            self->userSize--;
        }

    }
}
void blog_printPost(blog_t* self)
{
    for(int i=0;i<self->postSize;i++)
    {
        int idU = post_getId(self->postsArr[i]);
        if(idU != -1)
        {
            post_print(self->postsArr[i]);
        }

    }

}
void blog_deletePost(blog_t* self,int id)
{
    for(int i=0;i<self->postSize;i++)
    {
        int idU = post_getId(self->postsArr[i]);
        if(idU == id)
        {
            post_edit(self->postsArr[i],"empty",-1);
            self->postSize--;
        }

    }

}
user_t * blog_getUser(blog_t * self,int id)
{
    int v = self->userSize;
    for(int i=0;i<self->userSize;i++)
    {
        int idU = user_getId(self->userArr[i]);
        if(idU == id)
        {
            return self->userArr[i];
        }

    }
    user_t * user3 = user_new(0,"NOT FOUNT","NOT FOUND",0);
    return user3;
}
