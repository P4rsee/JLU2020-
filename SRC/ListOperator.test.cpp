/*
#include "ListOperator.cpp"
#include <stdio.h>

int main() {

    TimeRecord tempTimeRecord = constructTimeRecord(2,2,2,2);
    PatientInfo tempPatientInfo = constructPatientInfo("TK-WANG",24,1);
    bool constructId[7] = {0,0,1,1,1,0,1};
    DoctorInfo  tempDoctorInfo = constructDoctorInfo("ss",2,1,constructId,1,1);
    SingleCost tempSingleCost = constructSingleCost(1,1,1);
    CheckRecord tempCheckRecord = constructCheckRecord(0,1,tempSingleCost);
    DiagnosisSituationUnion tempUnion;
    tempUnion.checkRecord = tempCheckRecord;
    DiagnosisSituation tempDiagnosisSituation = constructDiagnosisSituation(0,tempUnion);
    DiagnosisRecord* head = (DiagnosisRecord*) malloc(sizeof(DiagnosisRecord));
    head->next = NULL;
    DiagnosisRecord RecordA = constructDiagnosisRecord(tempTimeRecord, tempPatientInfo,
    tempDoctorInfo, tempDiagnosisSituation, 0);
    DiagnosisRecord *RecordPtr = (DiagnosisRecord*) malloc(sizeof(DiagnosisRecord));
    *RecordPtr = RecordA;
    DiagnosisRecord RecordB = RecordA;
    RecordB.patientInfo.registerId = 2;
    pushBackDiagnosisList(head,RecordPtr);
    printf("%d\n",head->next->patientInfo.registerId);
    *RecordPtr = RecordB;
    pushBackDiagnosisList(head,RecordPtr);
    printf("添加两个点后\n");
    printf("第一个点的ID:%d 第二个点的ID:%d\n",queryDiagnosisByRegisterId(head,1)->patientInfo.registerId,head->next->next->patientInfo.registerId);
    DiagnosisRecord* sectionQuerytest = queryDiagnosisBySectionId(head,1);
    printf("以科室号查询\n");
    showAllDiagnosisRecords(sectionQuerytest);
    deleteDiagnosisList(head,1);
    printf("删除第一个点后\n第一个点的ID:%d\n",head->next->patientInfo.registerId);
    return 0;
}
*/