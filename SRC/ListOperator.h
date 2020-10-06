#pragma once
#include "DiagnosisMessage.h"
#include <stdlib.h>
#include <stdio.h>

void pushBackDiagnosisList(DiagnosisRecord *head, DiagnosisRecord* newRecord);

void freeDiagnosisRecord(DiagnosisRecord* tempRecord);

void freeDiagnosisRecordList(DiagnosisRecord*);

void freeDiagnosisSituation(DiagnosisRecord*);

bool deleteDiagnosisList(DiagnosisRecord *head, int queryId);

void pushBackCheckList(CheckInfo* head,CheckInfo * newCheck);

void pushBackPrescribeList(PrescribeInfo* head, PrescribeInfo  *newPrescribe);

void pushBackDoctorList(DoctorNode* head, DoctorNode *newDoctorNode);

DiagnosisRecord* queryDiagnosisBySectionId(DiagnosisRecord* head,int sectionId);

DiagnosisRecord* queryDiagnosisByDoctorId(DiagnosisRecord* head, int doctorId);

DiagnosisRecord* queryDiagnosisByRegisterId(DiagnosisRecord* head,int registerId);

DoctorNode* queryDoctorBySectionId(DoctorNode* head,int sectionId);

void freeDoctorList(DoctorNode* head);

DiagnosisRecord* findModifiedNode(DiagnosisRecord* head,int registerId);

void showAllDiagnosisRecords(DiagnosisRecord* head);

void pushbackWard(Ward* head,Ward* newWard);

bool modifyWard(Ward *head, int wardId, Ward *newWard);

void freeWardList(Ward*);

void freeAllList(DiagnosisRecord*, DoctorNode*, Ward*);
