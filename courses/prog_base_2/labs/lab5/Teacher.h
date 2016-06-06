#ifndef TEACHER_H_INCLUDED
#define TEACHER_H_INCLUDED

typedef struct teacher_s teacher_t;
typedef struct teacherList_s teacherList_t;
teacher_t * teacher_new(void);
teacherList_t * teacherList_new(void);
void teacher_listFree(teacherList_t * tList);
void teacher_free(teacher_t *);
void teacher_print(teacher_t *);
char * teacher_toJSON(teacher_t * self);
char * teacher_arrToJSON(teacherList_t * self);
#endif
