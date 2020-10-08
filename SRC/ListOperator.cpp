#include "DiagnosisMessage.h"
#include <stdlib.h>
#include <stdio.h>
#include"global.h"

void pushBackDiagnosisList(DiagnosisRecord *head, DiagnosisRecord* newRecord) {
	DiagnosisRecord *tempPtr = head;
	while (tempPtr->next != NULL) {
		tempPtr = tempPtr->next;
	}
	tempPtr->next = newRecord;
	newRecord->next = NULL;
}

void freeDiagnosisRecord(DiagnosisRecord* tempRecord) {
	int flag = tempRecord->diagnosisSituation.setFlag;
	if (flag == 0) {
		CheckInfo* tempPtr = tempRecord->diagnosisSituation.
			diagnosisSituationInfo.checkRecord.checkInfoHead;
		while (tempPtr != NULL) {
			CheckInfo *nextPtr = tempPtr->next;
			free(tempPtr);
			tempPtr = nextPtr;
		}
	}
	else if (flag == 1) {
		PrescribeInfo* tempPtr = tempRecord->diagnosisSituation.
			diagnosisSituationInfo.prescribeRecord.prescribeInfoHead;
		while (tempPtr != NULL) {
			PrescribeInfo *nextPtr = tempPtr->next;
			free(tempPtr);
			tempPtr = nextPtr;
		}
	}
	free(tempRecord);
}

void freeDiagnosisSituation(DiagnosisRecord* tempRecord) {
	int flag = tempRecord->diagnosisSituation.setFlag;
	if (flag == 0) {
		CheckInfo* tempPtr = tempRecord->diagnosisSituation.
			diagnosisSituationInfo.checkRecord.checkInfoHead;
		while (tempPtr != NULL) {
			CheckInfo *nextPtr = tempPtr->next;
			free(tempPtr);
			tempPtr = nextPtr;
		}
	}
	else if (flag == 1) {
		PrescribeInfo* tempPtr = tempRecord->diagnosisSituation.
			diagnosisSituationInfo.prescribeRecord.prescribeInfoHead;
		while (tempPtr != NULL) {
			PrescribeInfo *nextPtr = tempPtr->next;
			free(tempPtr);
			tempPtr = nextPtr;
		}
	}
}


bool deleteDiagnosisList(DiagnosisRecord *head, int queryId) {
	DiagnosisRecord *prePtr = head;
	DiagnosisRecord *tempPtr = prePtr->next;
	while (tempPtr != NULL) {
		int registerId = tempPtr->patientInfo.registerId;
		if (registerId == queryId) {
			prePtr->next = tempPtr->next;
			freeDiagnosisRecord(tempPtr);
			return true;
		}
		tempPtr = tempPtr->next;
		prePtr = tempPtr->next;
	}
	return false;
}

void pushBackCheckList(CheckInfo* head, CheckInfo * newCheck) {
	CheckInfo *tempPtr = head;
	while (tempPtr->next != NULL) {
		tempPtr = tempPtr->next;
	}
	CheckInfo *ptr = (CheckInfo*)malloc(sizeof(CheckInfo));
	*ptr = *newCheck;
	ptr->next = NULL;
	tempPtr->next = ptr;
}

void pushBackPrescribeList(PrescribeInfo* head, PrescribeInfo  *newPrescribe) {
	PrescribeInfo *tempPtr = head;
	while (tempPtr->next != NULL) {
		tempPtr = tempPtr->next;
	}
	PrescribeInfo* ptr = (PrescribeInfo*)malloc(sizeof(PrescribeInfo));
	*ptr = *newPrescribe;
	ptr->next = NULL;
	tempPtr->next = ptr;
}

void pushBackDoctorList(DoctorNode* head, DoctorNode *newDoctorNode) {
	DoctorNode *tempPtr = head;
	while (tempPtr->next != NULL) {
		tempPtr = tempPtr->next;
	}
	DoctorNode* ptr = (DoctorNode*)malloc(sizeof(DoctorNode));
	*ptr = *newDoctorNode;
	ptr->next = NULL;
	tempPtr->next = ptr;
}

DiagnosisRecord* queryDiagnosisBySectionId(DiagnosisRecord* head, int sectionId) {
	DiagnosisRecord *tempHead = (DiagnosisRecord*)malloc(sizeof(DiagnosisRecord));
	tempHead->next = NULL;
	DiagnosisRecord *tempPtr = head->next;
	while (tempPtr != NULL) {
		if (tempPtr->doctorInfo.sectionId == sectionId) {
			pushBackDiagnosisList(tempHead, tempPtr);
		}
		tempPtr = tempPtr->next;
	}
	return tempHead;
}

DiagnosisRecord* queryDiagnosisByDoctorId(DiagnosisRecord* head, int doctorId) {
	DiagnosisRecord *tempHead = (DiagnosisRecord*)malloc(sizeof(DiagnosisRecord));
	tempHead->next = NULL;
	DiagnosisRecord *tempPtr = head;
	while (tempPtr != NULL) {
		if (tempPtr->doctorInfo.id == doctorId) {
			pushBackDiagnosisList(tempHead, tempPtr);
		}
		tempPtr = tempPtr->next;
	}
	return tempHead;
}

DiagnosisRecord* queryDiagnosisByRegisterId(DiagnosisRecord* head, int registerId) {
	DiagnosisRecord *tempPtr = head->next;
	while (tempPtr != NULL) {
		if (tempPtr->patientInfo.registerId == registerId) {
			break;
		}
		tempPtr = tempPtr->next;
	}
	if (NULL == tempPtr) 
		return NULL;
	DiagnosisRecord * resPtr = (DiagnosisRecord*)malloc(sizeof(DiagnosisRecord));
	*resPtr = *tempPtr;
	return resPtr;

}

DoctorNode* queryDoctorByDoctorId(DoctorNode* head, int doctorId) {
	DoctorNode* nowNode = head->next;
	while (nowNode != NULL) {
		if (nowNode->doctorInfo.id == doctorId)return nowNode;
		nowNode = nowNode->next;
	}
	return NULL;
}

DoctorNode* queryDoctorBySectionId(DoctorNode* head, int sectionId) {
	DoctorNode* tempHead = (DoctorNode*)malloc(sizeof(DoctorNode));
	tempHead->next = NULL;
	DoctorNode* tempPtr = head;
	while (tempPtr != NULL) {
		if (tempPtr->doctorInfo.sectionId == sectionId) {
			pushBackDoctorList(tempHead, tempPtr);
		}
		tempPtr = tempPtr->next;
	}
	return tempHead;
}
DiagnosisRecord* findModifiedNode(DiagnosisRecord* head, int registerId) {
	DiagnosisRecord *tempPtr = head->next;
	while (tempPtr != NULL) {
		if (tempPtr->patientInfo.registerId == registerId) {
			return tempPtr;
		}
		tempPtr = tempPtr->next;
	}
	return NULL;
}

void showAllDiagnosisRecords(DiagnosisRecord* head) {
	DiagnosisRecord *tempPtr = head->next;
	while (tempPtr != NULL) {
		printf("患者ID:%d 医生ID:%d 科室ID:%d", tempPtr->patientInfo.registerId,
			tempPtr->doctorInfo.id, tempPtr->doctorInfo.sectionId);
		tempPtr = tempPtr->next;
	}
}

void pushbackWard(Ward* head, Ward* newWard) {
	Ward* tempPtr = head;
	while (tempPtr->next != NULL) {
		tempPtr = tempPtr->next;
	}
	Ward* ptr = (Ward*)malloc(sizeof(DiagnosisRecord));
	*ptr = *newWard;
	ptr->next = NULL;
	tempPtr->next = ptr;
}

Ward * modifyWard(Ward *head, int wardId) {
	Ward *ptr = head->next;
	while (ptr&&ptr->wardId != wardId)
		ptr = ptr->next;
	if (ptr == NULL)
		return NULL;
	else
		return ptr;
}

void freeDiagnosisRecordList(DiagnosisRecord* head) {
	DiagnosisRecord *tempPtr;
	while (head != NULL) {
		tempPtr = head->next;
		free(head);
		head = tempPtr;
	}
}

void freeDoctorList(DoctorNode* head) {
	DoctorNode* tempPtr;
	while (head != NULL) {
		tempPtr = head->next;
		free(head);
		head = tempPtr;
	}
}

void freeWardList(Ward* head) {
	Ward* tempPtr;
	while (head != NULL) {
		tempPtr = head->next;
		free(head);
		head = tempPtr;
	}
}

void freeAllList(DiagnosisRecord* recordHaed, DoctorNode* doctorHead, Ward* wardHead) {
	freeDiagnosisRecordList(recordHaed);
	freeDoctorList(doctorHead);
	freeWardList(wardHead);
}

int sortInHospitalList(DiagnosisRecord* InHospitalHead) {
	DiagnosisRecord * tempPtr = InHospitalHead->next;
	DiagnosisRecord * resPtr = InHospitalHead;
	int cnt = 0;
	while (tempPtr != NULL){
		if (tempPtr->diagnosisSituation.diagnosisSituationInfo
			.inHospitalRecord.deposit.yuan < 1000
			&& InHospitalHead->next != tempPtr){
			cnt++;
			DiagnosisRecord * prePtr = tempPtr->next;
			resPtr->next = prePtr;
			tempPtr->next = InHospitalHead->next;
			InHospitalHead->next = tempPtr;
			tempPtr = prePtr;
			
		}
		else{
			if (InHospitalHead->next == tempPtr)cnt++;
			tempPtr = tempPtr->next;
			resPtr = resPtr->next;
		}
	}
	return cnt;
}


void getSickBedNum(DiagnosisRecord* recordNode) {
	int sectionId = recordNode->doctorInfo.sectionId;
	Ward* currentWard = WardHead;
	while (sectionId--)
		currentWard = currentWard->next;
	int flag = 1;
	int wardId, bedId;
	while (flag) {
		wardId = currentWard->wardId;
		int pos = 0;
		while (pos < currentWard->totalBedNum && currentWard->bedSituation[pos] == 1)
			pos++;
		if (pos == currentWard->totalBedNum) {
			flag = 1;
			if (currentWard->next == NULL)
				currentWard = WardHead->next;
			else
				currentWard = currentWard->next;
		}
		else {
			currentWard->bedSituation[pos] = 1;
			currentWard->occupiedBedNum++;
			flag = 0;
			wardId = currentWard->wardId;
			bedId = pos + 1;
		}
	}
	char buf[5];
	buf[0] = '0' + wardId / 10;
	buf[1] = '0' + wardId % 10;
	buf[2] = '0' + bedId / 10;
	buf[3] = '0' + bedId % 10;
	buf[4] = 0;
	recordNode->diagnosisSituation.
		diagnosisSituationInfo.inHospitalRecord.sickBedNumber = atoi(buf);
}


void freeWardBed(int wardID, int bedId) {
	Ward* currentWard = WardHead;
	while (currentWard->wardId != wardID)
		currentWard = currentWard->next;
	currentWard->bedSituation[bedId - 1] = 0;
	currentWard->occupiedBedNum--;
}