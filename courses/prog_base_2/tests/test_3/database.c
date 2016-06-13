#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sqllite/sqlite3.h"
#include "database.h"
#include "student.h"
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
int db_tableExists(const db_t * self)
{
    int size = 0;
    sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "SELECT * FROM student";
	sqlite3_prepare_v2(self->dbLite, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get Create Table\n");
		exit(1);
	}
	 size = sqlite3_column_count(stmt);
	sqlite3_finalize(stmt);
	return size;
}
int db_creatTable(const db_t * self)
{
    sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "CREATE TABLE `Student` (`FirstName`TEXT,`LastName`TEXT,`MiddleName`TEXT,`Birthday`TEXT,`Number`INTEGER,`id`INTEGER,PRIMARY KEY(id));";
	sqlite3_prepare_v2(self->dbLite, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get Creat Table\n");
		exit(1);
	}
	sqlite3_finalize(stmt);
	return rc;
}
void db_addStudent(db_t * db,student_t * student)
{

    sqlite3_stmt * stmt = NULL;
    char * sqlQuery = "INSERT INTO student ('FirstName','LastName','MiddleName','Birthday','Number') VALUES (?,?,?,?,?);";
    sqlite3_prepare_v2(db->dbLite,sqlQuery,strlen(sqlQuery) + 1,&stmt,NULL);
    sqlite3_bind_text(stmt,1,student->firstName,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,2,student->secondName,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,3,student->middleName,-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,4,student->date,-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt,5,student->number);
    int rc = sqlite3_step(stmt);
    if(rc == SQLITE_ERROR)
    {
        puts("ERROR : Student insert");

    }
    else
        {
            sqlite3_finalize(stmt);
        }

}
db_removeStudent(db_t * db,char * date){
    int size = 0;
    sqlite3_stmt * stmt = NULL;
    char * sqlQuery = "SELECT COUNT(*) FROM student WHERE Birthday < ?";
    sqlite3_prepare_v2(db->dbLite,sqlQuery,strlen(sqlQuery) + 1,&stmt,NULL);
    sqlite3_bind_text(stmt,1,date,-1,SQLITE_STATIC);
    int rc = sqlite3_step(stmt);
    if(rc == SQLITE_ERROR)
    {
        puts("ERROR : Student insert");

    }
    else
        {
            size = sqlite3_column_int(stmt,0);
            printf("SIZE IS %d",size);
            sqlite3_finalize(stmt);
        }
   sqlite3_stmt * stmt2 = NULL;
     sqlQuery = "DELETE * FROM FROM student WHERE Birthday < ?;";
    sqlite3_prepare_v2(db->dbLite,sqlQuery,strlen(sqlQuery) + 1,&stmt2,NULL);
    sqlite3_bind_text(stmt2,1,date,-1,SQLITE_STATIC);
     rc = sqlite3_step(stmt2);
    if(rc == SQLITE_ERROR)
    {
        puts("ERROR : Student insert");

    }
    else
        {
             size = sqlite3_column_int(stmt,0);
            sqlite3_finalize(stmt);
        }
        return size;
}



