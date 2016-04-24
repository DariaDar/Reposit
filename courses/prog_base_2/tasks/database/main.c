#include "pensioner.h"
#include "db_manager.h"
#include <stdio.h>
#include <windows.h>


#include "sqlite3.h"


int main()
{
	const char * dbFile = "pensioners.db";
    pensioner_t pensionertList[100];

    db_t * db = db_new(dbFile);

    int countAllPensioner = db_countPensioner(db);
    printf("\n>----Pensioners total: %i----<\n", countAllPensioner);

    int filterExperienceCount = 33;
    double filterPensionCount = 2300.0;
    int count = db_getPensionerTask(db, filterExperienceCount, filterPensionCount, pensionertList, 100);
    printf("\n>>----Count Pensioners with Experience > %i and Pension < %f: %i----<<\n", filterExperienceCount, filterPensionCount, count);
    printList_pensioner(pensionertList, count);

	int filterID = 2;
	printf("\n>>----Select pensioner by ID = %d----<<\n", filterID);
	print_pensioner(db_getPensionerById(db, filterID));

	filterID = 2;
	printf("\n>>----Delete pensioner by ID = %d----<<\n\n", filterID);
	db_deletePensioner(db, filterID);

	printf("\n>>----Insert {id, Red, Redson, 71, 39, 2567.5, 1945-09-11}----<<\n");
	pensionertList[0].id = 0;
	sprintf(pensionertList[0].name, "%s", "Red");
	sprintf(pensionertList[0].surname, "%s", "Redson");
	pensionertList[0].year = 71;
	pensionertList[0].experience = 39;
	pensionertList[0].pension = 2567.5;
	sprintf(pensionertList[0].birthday, "%s", "1945-09-11");

	int newPersionerId = db_insertPensioner(db, pensionertList);
	print_pensioner(db_getPensionerById(db, newPersionerId));

	printf("\n>>----Update Red to Carl-------<<\n");
	pensioner_t * p = db_getPensionerById(db, newPersionerId);
	sprintf(p->name, "%s", "Carl");
	db_updatePensioner(db, p);
	print_pensioner(p);

    db_free(db);
	system("pause");
    return 0;
}

