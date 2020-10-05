#include "ListOperator.h"

void pushBackDiagnosisList(DiagnosisRecord *head, DiagnosisRecord* newRecord) {
    DiagnosisRecord *tempPtr = head;
    while(tempPtr->next != NULL) {
        tempPtr = tempPtr->next;
    }
    DiagnosisRecord* ptr = (DiagnosisRecord*) malloc(sizeof(DiagnosisRecord));
    *ptr = *newRecord;
    ptr->next = NULL;
    tempPtr->next = ptr;
}

void freeDiagnosisRecord(DiagnosisRecord* tempRecord) {
    int flag = tempRecord->diagnosisSituation.setFlag;
    if (flag == 0) {
        CheckInfo* tempPtr = tempRecord->diagnosisSituation.
        diagnosisSituationInfo.checkRecord.checkInfoHead;
        while(tempPtr != NULL) {
            CheckInfo *nextPtr = tempPtr->next;
            free(tempPtr);
            tempPtr = nextPtr;
        }
    } else if (flag == 1) {
        PrescribeInfo* tempPtr = tempRecord->diagnosisSituation.
        diagnosisSituationInfo.prescribeRecord.prescribeInfoHead;
        while(tempPtr != NULL) {
            PrescribeInfo *nextPtr = tempPtr->next;
            free(tempPtr);
            tempPtr = nextPtr;
        }
    }
    free(tempRecord);
}

bool deleteDiagnosisList(DiagnosisRecord *head, int queryId) {
    DiagnosisRecord *prePtr = head;
    DiagnosisRecord *tempPtr = prePtr->next;
    while(tempPtr != NULL) {
        int registerId = tempPtr->patientInfo.registerId;
        if (registerId == queryId) {
            prePtr->next = tempPtr->next;
            freeDiagnosisRecord(tempPtr);
            return true;
        }
    }
    return false;
}

void pushBackCheckList(CheckInfo* head,CheckInfo * newCheck) {
    CheckInfo *tempPtr = head;
    while(tempPtr->next != NULL) {
        tempPtr = tempPtr->next;
    }
    CheckInfo *ptr = (CheckInfo*) malloc(sizeof(CheckInfo));
    *ptr = *newCheck;
    ptr->next = NULL;
    tempPtr->next = ptr;
}

void pushBackPrescribeList(PrescribeInfo* head, PrescribeInfo  *newPrescribe) {
    PrescribeInfo *tempPtr = head;
    while(tempPtr->next != NULL) {
        tempPtr = tempPtr->next;
    }
    PrescribeInfo* ptr = (PrescribeInfo*) malloc(sizeof(PrescribeInfo));
    *ptr = *newPrescribe;
    ptr->next = NULL;
    tempPtr->next = ptr;
}

void pushBackDoctorList(DoctorNode* head, DoctorNode *newDoctorNode) {
    DoctorNode *tempPtr = head;
    while(tempPtr->next != NULL) {
        tempPtr = tempPtr->next;
    }
    DoctorNode* ptr = (DoctorNode*) malloc(sizeof(DoctorNode));
    *ptr = *newDoctorNode;
    ptr->next = NULL;
    tempPtr->next = ptr;
}

DiagnosisRecord* queryDiagnosisBySectionId(DiagnosisRecord* head,int sectionId) {
    DiagnosisRecord *tempHead = (DiagnosisRecord*) malloc(sizeof(DiagnosisRecord));
    tempHead->next = NULL;
    DiagnosisRecord *tempPtr = head->next;
    while(tempPtr != NULL) {
        if (tempPtr->doctorInfo.sectionId == sectionId) {
            pushBackDiagnosisList(tempHead,tempPtr);
        }
        tempPtr = tempPtr->next;
    }
    return tempHead;
}

DiagnosisRecord* queryDiagnosisByDoctorId(DiagnosisRecord* head, int doctorId) {
    DiagnosisRecord *tempHead = (DiagnosisRecord*) malloc(sizeof(DiagnosisRecord));
    tempHead->next = NULL;
    DiagnosisRecord *tempPtr = head;
    while(tempPtr != NULL) {
        if (tempPtr->doctorInfo.id == doctorId) {
            pushBackDiagnosisList(tempHead,tempPtr);
        }
        tempPtr = tempPtr->next;
    }
    return tempHead;
}

DiagnosisRecord* queryDiagnosisByRegisterId(DiagnosisRecord* head,int registerId) {
    DiagnosisRecord *tempPtr = head->next;
    while(tempPtr != NULL) {
        if (tempPtr->patientInfo.registerId == registerId) {
            break;
        }
        tempPtr = tempPtr->next;
    }
    DiagnosisRecord* resPtr = (DiagnosisRecord*) malloc(sizeof(DiagnosisRecord));
    *resPtr = *tempPtr;
    return resPtr;
}

DoctorNode* queryDoctorBySectionId(DoctorNode* head,int sectionId) {
    DoctorNode* tempHead = (DoctorNode*) malloc(sizeof(DoctorNode));
    tempHead->next = NULL;
    DoctorNode* tempPtr = head;
    while(tempPtr != NULL) {
        if (tempPtr->doctorInfo.sectionId == sectionId) {
            pushBackDoctorList(tempHead,tempPtr);
        }
        tempPtr = tempPtr->next;
    }
    return tempHead;
}

DiagnosisRecord* findModifiedNode(DiagnosisRecord* head,int registerId) {
    DiagnosisRecord *tempPtr = head->next;
    while(tempPtr != NULL) {
        if (tempPtr->patientInfo.registerId == registerId) {
            return tempPtr;
        }
        tempPtr = tempPtr->next;
    }
    return NULL;
}

void showAllDiagnosisRecords(DiagnosisRecord* head) {
    DiagnosisRecord *tempPtr = head->next;
    while(tempPtr != NULL) {
        printf("患者ID:%d 医生ID:%d 科室ID:%d",tempPtr->patientInfo.registerId,
        tempPtr->doctorInfo.id, tempPtr->doctorInfo.sectionId);
        tempPtr = tempPtr->next;
    }
}

void pushbackWard(Ward* head,Ward* newWard) {
    Ward* tempPtr = head;
    while(tempPtr->next != NULL) {
        tempPtr = tempPtr->next;
    }
    Ward* ptr = (Ward*) malloc(sizeof(DiagnosisRecord));
    *ptr = *newWard;
    ptr->next = NULL;
    tempPtr->next = ptr;
}

bool modifyWard(Ward *head, int wardId, Ward *newWard) {
    Ward *ptr = head->next;
    while(ptr->wardId != wardId)
        ptr = ptr->next;
    if (ptr == NULL)
        return false;
    *ptr = *newWard;
    return true;
}
