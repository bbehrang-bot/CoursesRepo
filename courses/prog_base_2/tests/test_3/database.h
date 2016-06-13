#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include "student.h"
typedef struct db_s db_t;
db_t * db_new(const char * dbName);
void db_free(db_t * db);
int db_tableExists(const db_t * self);
db_removeStudent(db_t * db,char * date);
void db_addStudent(db_t * db,student_t * student);

#endif // DATABASE_H_INCLUDED
