#ifndef BLOG_H_INCLUDED
#define BLOG_H_INCLUDED
typedef struct blog_s blog_t;
blog_t * blog_new(char * title,int id);
void blog_free(blog_t *  self);
int blog_getId(blog_t * self);


#endif // BLOG_H_INCLUDED
