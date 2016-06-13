#ifndef POST_H_INCLUDED
#define POST_H_INCLUDED
typedef struct post_s post_t;
post_t * post_new(char * body,int id);
void post_free(post_t *  self);
int post_getId(post_t * self);
void post_print(post_t * post);

#endif // POST_H_INCLUDED
