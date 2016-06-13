#include "clinic.h"
#include "list.h"
#include <string.h>

struct patient_s
{
    char name[100];
    char doctor[100];
};

struct doctor_s
{
    char name[100];
	int numOfPatients;
	list_t * patients;
};

struct clinic_s
{
    char * title;
	int numOfDoctors;
	int numOfPatients;
	list_t * doctors;
	list_t * patients;
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
patient_t * patient_new(char * name)
{
	patient_t * p = malloc(sizeof(struct patient_s));
	strcpy(p->doctor, "\0");
	strcpy(p->name, name);
	return p;
}
void patient_delete(patient_t * p)
{
	free(p);
}

void patient_addDoctor(patient_t * p, doctor_t * doc)
{
    strcpy(p->doctor, doc->name);
    list_push_back(doc->patients, p);
    doc->numOfPatients++;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
doctor_t * doctor_new(char * name)
{
    doctor_t * d = malloc(sizeof(struct doctor_s));
    d->numOfPatients = 0;
    d->patients = list_new();
    strcpy(d->name, name);
    return d;
}


doctor_t * clinic_removeDoctor(clinic_t * cl, doctor_t * d)
{
    int index = -1;
    for(int i = 0; i < cl->numOfDoctors; i++)
    {
       doctor_t * doc = list_get(cl->doctors, i);
        if (strcmp(d->name,doc->name) == 0)
        {
            index = i;
            break;
        }
    }
    if(index == -1)
    {
        return NULL;
    }
    else
        return list_remove(cl->doctors, index);
}

list_t * doctor_getPatienceList(doctor_t * doc)
{
    return doc->patients;
}

int doctor_getNumOfPatience(doctor_t * doc)
{
    return doc->numOfPatients;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


clinic_t * clinic_new(char * name)
{
    clinic_t * cl = malloc(sizeof(struct clinic_s));
    cl->numOfDoctors = 0;
    cl->numOfPatients = 0;
    cl->doctors = list_new();
    cl->patients = list_new();
    strcpy(cl->title, name);
    return cl;
}

void clinic_delete(clinic_t * cl)
{
    for(int i = 0; i < cl->numOfPatients; i++)
    {
        list_remove(cl->patients, i);
    }
    list_free(cl->patients);
    for(int i = 0; i < cl->numOfDoctors; i++)
    {
        list_remove(cl->doctors, i);
    }
    list_free(cl->doctors);
    free(cl);
}

char * clinic_getName(clinic_t * cl)
{
    return cl->title;
}

list_t * clinic_getListofPatience(clinic_t * cl)
{
    return cl->patients;
}

list_t * clinic_getListofDoctors(clinic_t * cl)
{
    return cl->doctors;
}

int clinic_getDoctorsCnt(clinic_t * cl)
{
    return cl->numOfDoctors;
}

int clinic_getPatienceCnt(clinic_t * cl)
{
    return cl->numOfPatients;
}


void clinic_addPatient(clinic_t * cl, patient_t * p)
{
    list_push_back(cl->patients,p);
    cl->numOfPatients++;
}

void clinic_addDoctor(clinic_t * cl, doctor_t * d)
{
    list_push_back(cl->doctors, d);
    cl->numOfDoctors++;
}

char * patient_getName(patient_t * pat)
{
    return pat->name;
}
patient_t * clinic_removePatient(clinic_t * cl, patient_t * p)
{
    int index = -1;
    for(int i = 0; i < list_getSize(cl->patients); i++)
    {
        patient_t * pat = list_get(cl->patients, i);
        if (strcmp(p->name, pat->name)== 0)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        return NULL;
    }
    else
        return list_remove(cl->patients,index);
}
