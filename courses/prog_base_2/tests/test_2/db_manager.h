#ifndef _DB_MODUL
#define _DB_MODUL
#include "sqlite3.h"
#include "pensioner.h"

typedef struct db_s db_t;

db_t * db_new(const char * dbFile);
void db_free(db_t * self);

int db_insertPensioner(db_t * self, pensioner_t * pensioner);
pensioner_t * db_getPensionerById(db_t * self, int id);
void db_updatePensioner(db_t * self, pensioner_t * pensioner);
void db_deletePensioner(db_t * self, int id);

int db_countPensioner(db_t * self);

int db_getPensionerTask(db_t * self, int K, double P, pensioner_t * arr, int arrMax);

#endif
