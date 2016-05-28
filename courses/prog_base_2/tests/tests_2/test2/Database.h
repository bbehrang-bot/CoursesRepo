#ifndef DB_MANAGER_H_INCLUDED
#define DB_MANAGER_H_INCLUDED

#include <sqlite3.h>

#include "Freelanser.h"

typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * self);

void db_insertLancer(db_t * self, teacher_t * student);
teacher_t * db_getLancerById(db_t * self, int id);
void db_updateLancer(db_t * self, teacher_t * newLancer,int id);
void db_deleteLancer(db_t * self, int id);
void _fillLancer(sqlite3_stmt * stmt, teacher_t * st);
void db_getAll(db_t *self, teacher_t * arr, int arrMax);

int db_countLancers(db_t * self);

int db_getStudentsTask(db_t * self, int salary,int maxCount, teacher_t * arr, int arrMax);

#endif
