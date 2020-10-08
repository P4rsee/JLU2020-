#pragma once
#include "DiagnosisMessage.h"

void generateRegisterID(DiagnosisRecord*);

DoctorNode* getRecommendedDoctors(DoctorNode*, int);

void combineDoctorIntoDiagnosisRecord(DiagnosisRecord* head,
  DiagnosisRecord *currentRecordPtr, DoctorNode* newDoctorPtr);

DoctorNode* doctorRecommendedMergeSort(DoctorNode*);
