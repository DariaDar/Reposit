#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "db_manager.h"
#include "sqlite3.h"

struct db_s
{
    sqlite3 * db;
};

db_t * db_new(const char * dbFile)
{
    db_t * self = malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbFile, &self->db);
    if (SQLITE_ERROR == rc) {
        printf("can't open database\n");
        exit(1);
    }
    return self;
}

void db_free(db_t * self)
{
    sqlite3_close(self->db);
    free(self);
}

int db_insertPensioner(db_t * self, pensioner_t * pensioner)
{
    int newPersionerId = 1;
	while(1)
	{
		if(db_getPensionerById(self, newPersionerId) != NULL)
			newPersionerId++;
		else
			break;
	}

	sqlite3_stmt * stmt = NULL;
   	const char * sqlQuery = "INSERT INTO Pensioners  VALUES ( ?, ?, ?, ?, ?, ?, ? );";
	sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, newPersionerId);
	sqlite3_bind_text(stmt, 2, pensioner->name, strlen(pensioner->name), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, pensioner->surname, strlen(pensioner->surname), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, pensioner->year);
	sqlite3_bind_int(stmt, 5, pensioner->experience);
	sqlite3_bind_double(stmt, 6, pensioner->pension);
	sqlite3_bind_text(stmt, 7, pensioner->birthday, strlen(pensioner->birthday), SQLITE_STATIC);

	int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
	{
        printf("can't insert\n");
        return NULL;
    }

	sqlite3_finalize(stmt);
    return newPersionerId;
}

pensioner_t * db_getPensionerById(db_t * self, int id)
{
	static pensioner_t ps;
	memset(&ps, 0, sizeof(pensioner_t));

	sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Pensioners WHERE Id = ?;";
	sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
	int rc = sqlite3_step(stmt);
    if ((SQLITE_ERROR == rc)  || (SQLITE_DONE == rc))
	{
        printf("Can't select by ID\n");
        return NULL;
    }

	int Id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    const unsigned char * surname = sqlite3_column_text(stmt, 2);
    int year = sqlite3_column_int(stmt, 3);
    int experience = sqlite3_column_int(stmt, 4);
    double pension = sqlite3_column_double(stmt, 5);
	const unsigned char * birthday = sqlite3_column_text(stmt, 6);
    ps.id = Id;
    strcpy(ps.name, (const char *)name);
    strcpy(ps.surname, (const char *)surname);
    ps.year = year;
    ps.experience = experience;
    ps.pension = (float)pension;
	strcpy(ps.birthday, (const char *)birthday);

	sqlite3_finalize(stmt);
    return &ps;
}

void db_updatePensioner(db_t * self, pensioner_t * pensioner)
{
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "UPDATE Pensioners SET Name = ?, Surname = ?, Year = ?, Experience = ?, Pension = ?, Birthday = ? WHERE Id = ?;";
	sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);

	sqlite3_bind_text(stmt, 1, pensioner->name, strlen(pensioner->name), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, pensioner->surname, strlen(pensioner->surname), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 3, pensioner->year);
	sqlite3_bind_int(stmt, 4, pensioner->experience);
	sqlite3_bind_double(stmt, 5, pensioner->pension);
	sqlite3_bind_text(stmt, 6, pensioner->birthday, strlen(pensioner->birthday), SQLITE_STATIC);

	sqlite3_bind_int(stmt, 1, pensioner->id);

	int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
	{
        printf("Can't UPDATE \n");
        return;
    }
	sqlite3_finalize(stmt);
}

void db_deletePensioner(db_t * self, int id)
{
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "DELETE FROM Pensioners WHERE Id = ?;";
	sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);
	int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
	{
        printf("can't select by ID\n");
        return ;
    }
	sqlite3_finalize(stmt);
	printf("Delete by ID = %d OK\n", id);
}

int db_countPensioner(db_t * self)
{
    sqlite3_stmt * stmt = NULL;
    sqlite3_prepare_v2(self->db, "SELECT COUNT(*) FROM Pensioners;", -1, &stmt, 0);
    int rc = sqlite3_step(stmt);
    if (SQLITE_ERROR == rc)
	{
        printf("can't select count\n");
        exit(1);
    }
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

static void _fillPensioner(sqlite3_stmt * stmt, pensioner_t * ps)
{
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char * name = sqlite3_column_text(stmt, 1);
    const unsigned char * surname = sqlite3_column_text(stmt, 2);
    int year = sqlite3_column_int(stmt, 3);
    int experience = sqlite3_column_int(stmt, 4);
    double pension = sqlite3_column_double(stmt, 5);
	const unsigned char * birthday = sqlite3_column_text(stmt, 6);
    ps->id = id;
    strcpy(ps->name, (const char *)name);
    strcpy(ps->surname, (const char *)surname);
    ps->year = year;
    ps->experience = experience;
    ps->pension = pension;
	strcpy(ps->birthday, (const char *)birthday);
}

int db_getPensionerTask(db_t * self, int K, double P, pensioner_t * arr, int arrMax)
{
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Pensioners WHERE Experience > ? AND Pension < ?;";
    sqlite3_prepare_v2(self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int(stmt, 1, K);
    sqlite3_bind_double(stmt, 2, P);
    int count = 0;
    while (1)
    {
        int rc = sqlite3_step(stmt);
        if (SQLITE_ERROR == rc)
		{
            printf("can't select pensioners\n");
            exit(1);
        }
		else if (SQLITE_DONE == rc)
            break;
		else
		{
            _fillPensioner(stmt, &arr[count]);
            count++;
        }
    }
    sqlite3_finalize(stmt);
    return count;
}
