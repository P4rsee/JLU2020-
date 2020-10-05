#pragma once
#include "DiagnosisMessage.h"

void generateRegisterID(DiagnosisRecord*);

DoctorNode* getRecommendedDoctors(DoctorNode*,int);

void freeRecommendedDoctors(DiagnosisRecord*);

void combineDoctorIntoDiagnosisRecord(DiagnosisRecord* head,
    DiagnosisRecord *currentRecordPtr, DoctorNode* newDoctorPtr);

DoctorNode* doctorRecommendedMergeSort(DoctorNode*);
