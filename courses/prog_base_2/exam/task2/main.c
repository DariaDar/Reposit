#include <stdio.h>
#include <stdlib.h>
#include "clinic.h"
#include "list.h"

int main()
{
    clinic_t * cl = clinic_new("Hospital");
    printf("%s\n", clinic_getName(cl));

    doctor_t * doc = doctor_new("Sam");
    doctor_t * doc1 = doctor_new("Harry");
    patient_t * pat = patient_new("Jo");
    patient_t * pat1 = patient_new("Ron");

    clinic_addPatient(cl, pat);
    clinic_addPatient(cl, pat1);




    //LIST OF PATIENS
    for(int i = 0; i < clinic_getPatienceCnt(cl); i++)
    {
        patient_t * p = list_get((clinic_getListofPatience(cl)), i);
        printf("%i. %s\n", i, patient_getName(p));
    }

    clinic_removePatient(cl, pat);


     for(int i = 0; i < clinic_getPatienceCnt(cl); i++)
    {
        patient_t * p = list_get((clinic_getListofPatience(cl)), i);
        printf("%i. %s\n", i + 1, patient_getName(p));
    }

    //clinic_addDoctor(cl, doc);
    //clinic_addDoctor(cl, doc1);
/*
    for(int i = 0; i < list_getSize(clinic_getListofDoctors(cl)); i++)
    {

    }
    return 0;*/
}
