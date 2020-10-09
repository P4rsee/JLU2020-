#include "DoctorInfoProcessor.h"
#include "global.h"
#include "ListOperator.h"
#include<stdio.h>
void generateRegisterID(DiagnosisRecord* DiagnosisRecordPtr) {
	DiagnosisRecordPtr->patientInfo.registerId = ++currentID;
}

double getRecommendedDegree(DoctorNode* doctorNode) {
	return 1.0*doctorNode->doctorInfo.level / (doctorNode->doctorInfo.busyDegree + 1);
}

DoctorNode* doctorRecommendedMergeSort(DoctorNode* head) {
	if (head->next == NULL || head == NULL)
		return head;
	DoctorNode *slow = head, *fast = head;
	while (fast->next != NULL && fast->next->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	DoctorNode *leftHead = head, *rightHead = slow->next;
	slow->next = NULL;
	leftHead = doctorRecommendedMergeSort(leftHead);
	rightHead = doctorRecommendedMergeSort(rightHead);
	DoctorNode* resHead = (DoctorNode*)malloc(sizeof(DoctorNode));
	DoctorNode* currentPtr = resHead;
	while (leftHead != NULL && rightHead != NULL) {
		double leftDegree = getRecommendedDegree(leftHead);
		double rightDegree = getRecommendedDegree(rightHead);
		if (leftDegree >= rightDegree) {
			currentPtr->next = leftHead;
			leftHead = leftHead->next;
			currentPtr = currentPtr->next;
		}
		else {
			currentPtr->next = rightHead;
			rightHead = rightHead->next;
			currentPtr = currentPtr->next;
		}
	}
	if (leftHead != NULL) {
		currentPtr->next = leftHead;
	}
	else {
		currentPtr->next = rightHead;
	}
	currentPtr = resHead->next;
	free(resHead);
	return currentPtr;
}

DoctorNode* getRecommendedDoctors(DoctorNode *head, int sectionId) {
	DoctorNode* tempHead = queryDoctorBySectionId(head, sectionId);
	tempHead->next = doctorRecommendedMergeSort(tempHead->next);
	return tempHead;
}

void combineDoctorIntoDiagnosisRecord(DiagnosisRecord* head,
	DiagnosisRecord *currentRecordPtr, DoctorNode* newDoctorPtr) {
	currentRecordPtr->doctorInfo = newDoctorPtr->doctorInfo;
	pushBackDiagnosisList(head, currentRecordPtr);
	AddBusyDegree(newDoctorPtr->doctorInfo.id,1);
}