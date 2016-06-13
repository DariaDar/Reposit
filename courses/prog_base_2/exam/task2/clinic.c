#include "clinic.h"
#include "list.h"
#include <string.h>

struct patient_s
{
    char * name;
    char * doctor;
};

struct doctor_s
{
    char * name;
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
patient_t * patient_new(char * name, char * dName)
{
	patient_t * p = malloc(sizeof(struct patient_s));
	strcpy(p->doctor, dName);
	strcpy(p->name, name);
	return p;
}
void patient_delete(patient_t * p)
{
	free(p);
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

void doctor_delete(doctor_t * d)
{

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

void clinic_delete()
{

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
}

void clinic_addDoctor(clinic_t * cl, doctor_t * d)
{
    list_push_back(cl->doctors,d);
}


patient_t * clinic_removePatient(clinic_t * cl, patient_t * p)
{
    int index = -1;

}

doctor_t * clinic_removeDoctor(clinic_t * cl, doctor_t * d)
{
    int index = -1;
    for(int i = 0; i < cl->numOfDoctors; i++){

}


