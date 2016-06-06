#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include "teacher.h"
typedef struct db_s db_t;
db_t * db_new(const char * dbName);
void db_free(db_t * db);
void db_addTeacher(db_t * db,teacher_t * teacher);
int db_getSize(db_t * db);
teacher_t * db_setNewTeacher(db_t * db,int id);
void db_deleteTeacher(db_t * db,int id);
teacherList_t * db_getAllTeachFromDB(db_t * self);

#endif // DATABASE_H_INCLUDED
