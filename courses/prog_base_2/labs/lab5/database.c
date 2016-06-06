#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../sqllite/sqllite/sqlite3.h"
#include "database.h"
#include "teacherFields.h"
#include "teacherListFields.h"
#include "../list/list.h"
struct db_s
{
    sqlite3 * dbLite;
};
static char * teacher_createStringFromDate(char * out, teacher_t * self)
{
    sprintf(out, "%d-%d-%d\n", self->hireDate.tm_year, self->hireDate.tm_mday, self->hireDate.tm_mon);
    return out;
}
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
int db_getSize(db_t * db)
{
    sqlite3_stmt * stmt = NULL;
    char * sqlQuery = "SELECT  COUNT(*) FROM Teacher";
    sqlite3_prepare_v2(db->dbLite,sqlQuery,strlen(sqlQuery) + 1,&stmt,NULL);
    int rc = sqlite3_step(stmt);
    if(rc == SQLITE_ERROR)
    {
        puts("Error : Select Count");
        exit(1);
    }
    int size = sqlite3_column_int(stmt,0);

    sqlite3_finalize(stmt);
    return size;
}
void db_addTeacher(db_t * db,teacher_t * teacher)
{

    sqlite3_stmt * stmt = NULL;
    char * sqlQuery = "INSERT INTO Teacher ('Name','Salary','Experience','HireDate') VALUES (?,?,?,?);";
    sqlite3_prepare_v2(db->dbLite,sqlQuery,strlen(sqlQuery) + 1,&stmt,NULL);

    sqlite3_bind_text(stmt,1,teacher->name,-1,SQLITE_STATIC);
    sqlite3_bind_double(stmt,2,teacher->salary);
    sqlite3_bind_double(stmt,3,teacher->experience);
    char date[10];
    char * formattedDate = teacher_createStringFromDate(date,teacher);
    sqlite3_bind_text(stmt,4,formattedDate,-1,SQLITE_STATIC);
    int rc = sqlite3_step(stmt);
    if(rc == SQLITE_ERROR)
    {
        puts("ERROR : teacher insert");

    }
    else
        {
            sqlite3_finalize(stmt);
        }

}
int db_isId(db_t * db,int id)
{
    sqlite3_stmt * stmt = NULL;
    char * sqlQuery = "SELECT COUNT(*) FROM Teacher WHERE Teacher.Id = ?;";
    sqlite3_prepare_v2(db->dbLite, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ERROR)
    {
        printf("Cannot get info from Teacher table.\n");
        exit(1);
    }
    int size = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    if(size== 1)
        return 1;//true
    else
        return 0;//false

}
static void teacher_getFromDb(sqlite3_stmt * stmt,teacher_t * self)
{
    int id = sqlite3_column_int(stmt,0);
    if(id<=0)
        return;
    char * name = sqlite3_column_text(stmt,1);
    double salary = sqlite3_column_double(stmt,2);
    double expreience = sqlite3_column_double(stmt,3);
    char * hiredate = sqlite3_column_text(stmt,4);
    self->id = id;
    strcpy(self->name,name);
    self->salary = salary;
    self->experience = expreience;
    self->hireDate.tm_year = atoi(hiredate);
    hiredate = strtok(hiredate, "-");
    hiredate = strtok(NULL, "-");
    self->hireDate.tm_mday = atoi(hiredate);
    hiredate = strtok(NULL, "-");
    self->hireDate.tm_mon = atoi(hiredate);
}
teacher_t * db_setNewTeacher(db_t * db,int id)
{
    sqlite3_stmt * stmt = NULL;
    teacher_t * teach = teacher_new();
    char * sqliteQuery = "SELECT * FROM Teacher WHERE Teacher.Id = ?;";
    sqlite3_prepare_v2(db->dbLite,sqliteQuery,strlen(sqliteQuery) + 1,&stmt,NULL);
    sqlite3_bind_int(stmt,1,id);
    int rc = sqlite3_step(stmt);
    if(rc == SQLITE_ERROR)
    {
        puts("ERROR : Teacher Read");
        return;
    }
    teacher_getFromDb(stmt,teach);
    sqlite3_finalize(stmt);
    return teach;


}
teacherList_t * db_getAllTeachFromDB(db_t * self)
{
    sqlite3_stmt * stmt = NULL;
    int size = db_getSize(self);
    teacherList_t * teachList = teacherList_new();
    char * sqlQuery = "SELECT * FROM Teacher;";
    sqlite3_prepare_v2(self->dbLite, sqlQuery, strlen(sqlQuery) + 1, &stmt, NULL);
    int index =0;
    for(int i = 0; i<size; i++)
    {
        int rc = sqlite3_step(stmt);
        if (rc == SQLITE_ERROR)
        {
            printf("Cannot get Teacher table.\n");
            exit(1);
        }
        else
        {
            list_push_back(teachList->tList, teacher_new());
			teacher_getFromDb(stmt, (teacher_t *)list_get(teachList->tList, i));

        }
    }
     sqlite3_finalize(stmt);
     return teachList;
}
void db_deleteTeacher(db_t * db,int id)
{
    sqlite3_stmt * stmt = NULL;
    char * sqlQuery = "DELETE FROM Teacher WHERE id = ?;";
    sqlite3_prepare_v2(db->dbLite,sqlQuery,strlen(sqlQuery)+1,&stmt,NULL);
    sqlite3_bind_int(stmt,1,id);
    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ERROR) {
		printf("Cannot delete Teacher\n");
	}
    else
    {
			sqlite3_finalize(stmt);
    }
}
teacherList_t * database_getTeachArrFromDB_WHERE(const db_t * self, int moneyInv, int moneyInvSign, int exp, int expSign) {
	// Condition, given by user
	char mnySign;
	char xpSign;
	if (moneyInvSign == 1) {
		mnySign = '>';
	}
	else if (moneyInvSign == 0) {
		mnySign = '<';
	}
	if (expSign == 1) {
		xpSign = '>';
	}
	else if (expSign == 0) {
		xpSign = '<';
	}
	sqlite3_stmt * stmt = NULL;
	char * sqlRequestSize = calloc(500, sizeof(char));
	sprintf(sqlRequestSize,
		"SELECT COUNT(*) FROM Teacher "
		"WHERE (Experience %c ? AND Salary %c ?);",
		mnySign, xpSign);

	sqlite3_prepare_v2(self->dbLite, sqlRequestSize, strlen(sqlRequestSize) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, moneyInv);
	sqlite3_bind_int(stmt, 2, exp);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		free(sqlRequestSize);
		printf("Cannot get size of Teacher table.\n");
		exit(1);
	}
	int sizeFilter = sqlite3_column_int(stmt, 0);

	sqlite3_reset(stmt);

	char * sqlRequestTeachers = calloc(500, sizeof(char));
	sprintf(sqlRequestTeachers,
		"SELECT * FROM Teacher "
		"WHERE (Experience %c ? OR Salary %c ?) ;",
		mnySign, xpSign);

	sqlite3_prepare_v2(self->dbLite, sqlRequestTeachers, strlen(sqlRequestTeachers) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, moneyInv);
	sqlite3_bind_int(stmt, 2, exp);
	teacherList_t * tList = teacherList_new();
	for (int i = 0; i < sizeFilter;i++) {
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR) {
			free(sqlRequestSize);
			free(sqlRequestTeachers);
			printf("Cannot get Teacher table.\n");
			exit(1); // Exit instead of return to instantly abort the running program
		}
		else {
			list_push_back(tList->tList, teacher_new());
            teacher_getFromDb(stmt, (teacher_t *)list_get(tList->tList, i));
			teacher_print((teacher_t *)list_get(tList->tList, i));
		}
	}
	free(sqlRequestSize);
	free(sqlRequestTeachers);
	sqlite3_finalize(stmt);
	//
	return tList;
}

