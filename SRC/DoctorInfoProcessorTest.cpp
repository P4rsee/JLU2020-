/*
#include "DoctorInfoProcessor.h"
#include "ListOperator.h"
#include <stdio.h>

int main() {
    DoctorNode* head = (DoctorNode*) malloc(sizeof(DoctorNode));
    head->next = NULL;
    DoctorNode* tempPtr;
    tempPtr = (DoctorNode*) malloc(sizeof(DoctorNode));
    bool consultTime[] = {0,1,1,0,0,0,0};
    DoctorInfo tempDoctorInfo = constructDoctorInfo("2st",4,2,consultTime,2,1,0);
    *tempPtr = constructDoctorNode(tempDoctorInfo,0);
    pushBackDoctorList(head,tempPtr);
    tempDoctorInfo = constructDoctorInfo("1st",5,2,consultTime,1,1,0);
    *tempPtr = constructDoctorNode(tempDoctorInfo,0);
    pushBackDoctorList(head,tempPtr);
    tempDoctorInfo = constructDoctorInfo("4ed",1,2,consultTime,4,1,2);
    *tempPtr = constructDoctorNode(tempDoctorInfo,0);
    pushBackDoctorList(head,tempPtr);
    tempDoctorInfo = constructDoctorInfo("3rd",3,2,consultTime,3,1,2);
    *tempPtr = constructDoctorNode(tempDoctorInfo,0);
    pushBackDoctorList(head,tempPtr);
    DoctorNode* mergeHead =  getRecommendedDoctors(head,2);
    mergeHead = mergeHead->next;
    printf("Recommended Degree merge sort test:\n");
    while(mergeHead != NULL) {
        printf("%s\n",mergeHead->doctorInfo.name);
        mergeHead = mergeHead->next;
    }
    printf("generate Register ID test:\n");
    DiagnosisRecord* tempRecordPtr = (DiagnosisRecord*) malloc(sizeof(DiagnosisRecord));
    generateRegisterID(tempRecordPtr);
    printf("currentID is :%d\n",tempRecordPtr->patientInfo.registerId);
    return 0;
}

*/

/*
Run Result

Recommended Degree merge sort test:
1st
2st
3rd
4ed
generate Register ID test:
currentID is :1001
*/
