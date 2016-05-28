#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sqlite3.h>

#include "Database.h"
#include "Freelanser.h"

struct db_s {
    sqlite3 * db;
};

db_t * db_new(const char * dbFile) {
    db_t * self = malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbFile, & self->db);
    if (SQLITE_ERROR == rc) {
        printf("can't open database\n");
        exit(1);
    }

    return self;
}

void db_free(db_t * self) {
    sqlite3_close(self->db);
    free(self);
}

void db_insertLancer(db_t * self, teacher_t * Lancer) {
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "INSERT INTO database (Name, Surname, age, salary, date) VALUES(?,?,?,?,?);", -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1,Lancer->name, strlen(Lancer->name),SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2,Lancer->surname,strlen(Lancer->surname),SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, Lancer->age);
    sqlite3_bind_double(stmt, 4, Lancer->salary);
    sqlite3_bind_text(stmt, 5,Lancer->date,strlen(Lancer->date),SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);

    if (SQLITE_ERROR == rc) {
        printf("can't get by id\n");
        exit(1);
    }
    sqlite3_finalize(stmt);
}

teacher_t * db_getLancerById(db_t * self, int id) {
    if(id>db_countLancers(self)||id<0)
    {
        puts("Error id");
        exit(1);
    }
    static teacher_t lancer;

    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT * FROM database WHERE id = ?;", -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't get by id\n");
        exit(1);
    }
    else
        _fillLancer(stmt,&lancer);
    sqlite3_finalize(stmt);
    return &lancer;
}

void db_updateLancer(db_t * self, teacher_t * newLancer,int id) {
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "UPDATE database SET Name = ?, Surname = ?, age = ?, salary = ?, date = ? WHERE id = ?;", -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1,newLancer->name, strlen(newLancer->name),SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2,newLancer->surname,strlen(newLancer->surname),SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, newLancer->age);
    sqlite3_bind_double(stmt, 4, newLancer->salary);
    sqlite3_bind_text(stmt, 5,newLancer->date,strlen(newLancer->date),SQLITE_TRANSIENT);

    sqlite3_bind_int(stmt, 6, id);

    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't get by id\n");
        exit(1);
    }
    sqlite3_finalize(stmt);
}

void db_deleteLancer(db_t * self, int id) {
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "DELETE FROM database WHERE id = ?;", -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't get by id\n");
        exit(1);
    }
    sqlite3_finalize(stmt);
}

int db_countLancers(db_t * self) {

    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT COUNT(*) FROM database;", -1, &stmt, 0);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc) {
        printf("can't select count\n");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

void _fillLancer(sqlite3_stmt * stmt, teacher_t * st) {
    int id = sqlite3_column_int(stmt, 5);
    const unsigned char * name = sqlite3_column_text(stmt, 0);
    const unsigned char * surname = sqlite3_column_text(stmt, 1);
    double salary = sqlite3_column_double(stmt, 3);
    int age = sqlite3_column_int(stmt, 2);
    const unsigned char * date = sqlite3_column_text(stmt, 4);
    st->id = id;
    strcpy(st->name, (const char *)name);
    strcpy(st->surname, (const char *)surname);
    st->salary  = salary ;
    st->age = age;
    strcpy(st->date, (const char *)date);
}
void db_getAll(db_t *self, teacher_t * arr, int arrMax)
{
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM database";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);

    int count = 0;
    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't select students\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            _fillLancer(stmt, &arr[count]);
            count++;
        }
    }

    sqlite3_finalize(stmt);
    teacher_printList(arr,count);
}

int db_getStudentsTask(db_t * self, int salary,int maxCount, teacher_t * arr, int arrMax) {
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM database WHERE salary > ? LIMIT ?";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, salary);
    sqlite3_bind_int(stmt, 2, maxCount);
    int count = 0;
    while (1) {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc) {
            printf("can't select students\n");
            exit(1);
        } else if (SQLITE_DONE == rc) {
            break;
        } else {
            _fillLancer(stmt, &arr[count]);
            count++;
        }
    }
    sqlite3_finalize(stmt);
    return count;
}
