#ifndef COMMENT_H_INCLUDED
#define COMMENT_H_INCLUDED
typedef struct comment_s comment_t;
comment_t * comment_new(char * body,int id);
void comment_free(comment_t *  self);
int comment_getId(comment_t * self);
void comment_print(comment_t * self);
void comment_edit(comment_t * self);

#endif // COMMENT_H_INCLUDED
