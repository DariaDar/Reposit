#ifndef CLINIC_H
#define CLINIC_H

#include "list.h"
typedef struct clinic_s clinic_t;
typedef struct patient_s patient_t;
typedef struct doctor_s doctor_t;

patient_t * patient_new(char * name);
void patient_delete(patient_t * p);
doctor_t * doctor_new(char * name);
void doctor_delete(doctor_t * d);
clinic_t * clinic_new(char * name);
void clinic_delete();
list_t * clinic_getListofPatience(clinic_t * cl);
list_t * clinic_getListofDoctors(clinic_t * cl);
int clinic_getDoctorsCnt(clinic_t * cl);
int clinic_getPatienceCnt(clinic_t * cl);
void clinic_addPatient(clinic_t * cl, patient_t * p);
void clinic_addDoctor(clinic_t * cl, doctor_t * d);
patient_t * clinic_removePatient(clinic_t * cl, patient_t * p);
doctor_t * clinic_removeDoctor(clinic_t * cl, doctor_t * d);


#endif // CLINIC_H
