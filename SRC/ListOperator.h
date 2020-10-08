#pragma once
#include "DiagnosisMessage.h"
#include <stdlib.h>
#include <stdio.h>

void pushBackDiagnosisList(DiagnosisRecord *head, DiagnosisRecord* newRecord);

void freeDiagnosisRecord(DiagnosisRecord* tempRecord);

bool deleteDiagnosisList(DiagnosisRecord *head, int queryId);

void pushBackCheckList(CheckInfo* head, CheckInfo * newCheck);

void pushBackPrescribeList(PrescribeInfo* head, PrescribeInfo  *newPrescribe);

void pushBackDoctorList(DoctorNode* head, DoctorNode *newDoctorNode);

DiagnosisRecord* queryDiagnosisBySectionId(DiagnosisRecord* head, int sectionId);

DiagnosisRecord* queryDiagnosisByDoctorId(DiagnosisRecord* head, int doctorId);

DiagnosisRecord* queryDiagnosisByRegisterId(DiagnosisRecord* head, int registerId);

DoctorNode* queryDoctorByDoctorId(DoctorNode* head, int doctorId);

DoctorNode* queryDoctorBySectionId(DoctorNode* head, int sectionId);

DiagnosisRecord* findModifiedNode(DiagnosisRecord* head, int registerId);

void showAllDiagnosisRecords(DiagnosisRecord* head);

void pushbackWard(Ward* head, Ward* newWard);

Ward * modifyWard(Ward *head, int wardId);

void freeDiagnosisRecordList(DiagnosisRecord*);

void freeDoctorList(DoctorNode* head);

void freeWardList(Ward*);

void freeAllList(DiagnosisRecord*, DoctorNode*, Ward*);

void freeDiagnosisSituation(DiagnosisRecord*);

int sortInHospitalList(DiagnosisRecord*);

void getSickBedNum(DiagnosisRecord* recordNode);

void freeWardBed(int wardID, int bedId);