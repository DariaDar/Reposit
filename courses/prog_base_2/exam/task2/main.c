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
    patient_t * pat2 = patient_new("Sally");

    clinic_addPatient(cl, pat);
    clinic_addPatient(cl, pat1);
    clinic_addPatient(cl, pat2);

    clinic_addDoctor(cl, doc);
    clinic_addDoctor(cl, doc1);

    patient_addDoctor(pat, doc);



    //LIST OF PATIENS
    printf("Patients:\n");
    for(int i = 0; i < clinic_getPatienceCnt(cl); i++)
    {
        patient_t * p = list_get((clinic_getListofPatience(cl)), i);
        printf("%i. %s\n", i, patient_getName(p));
    }

    printf("\nPat cnt: %i\n", clinic_getPatienceCnt(cl));

    printf("\nDoctors:\n");
     for(int i = 0; i < clinic_getDoctorsCnt(cl); i++)
    {
        patient_t * p = list_get((clinic_getListofDoctors(cl)), i);
        printf("%i. %s\n", i, doctor_getName(p));
    }

    clinic_removePatient(cl, pat);

    printf("\nPatients:\n");
     for(int i = 0; i < clinic_getPatienceCnt(cl); i++)
    {
        patient_t * p = list_get((clinic_getListofPatience(cl)), i);
        printf("%i. %s\n", i + 1, patient_getName(p));
    }

    printf("\nDoc cnt: %i\n", clinic_getDoctorsCnt(cl));

    patient_addDoctor(pat, doc);
    clinic_delete(cl);
    return 0;
}
