#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
typedef struct db_s db_t;
db_t * db_new(const char * dbName);
void db_free(db_t * db);


#endif // DATABASE_H_INCLUDED
