#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sqllite/sqlite3.h"
#include "database.h"
struct db_s
{
    sqlite3 * dbLite;
};

db_t * db_new(const char * dbName)
{
    db_t *db = malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbName,&db->dbLite);
    if(rc == SQLITE_ERROR)
    {
        puts("Cant open DB");
        exit(1);
    }
    return db;
}
void db_free(db_t * db)
{
    sqlite3_close(db);
    free(db);
}


