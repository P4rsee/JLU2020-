#include "DiagnosisMessage.h"
#include "TimePassing.h"
#include <stdlib.h>
#include "global.h"
#include"ListOperator.h"

extern int bedcost[4];
int actualExpense(TimeRecord startDate, TimeRecord endDate, int bedtype, int nursingtype) {
	int day[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int startMonth = startDate.month, endMonth = endDate.month;
	int countday = endDate.day - startDate.day;
	while (startMonth < endMonth) {
		countday += day[startMonth++];
	}
	int basic = 100;
	if (1 == nursingtype){
		basic += 100;
	}
	return (basic+ bedcost[bedtype])* countday;
}

SingleCost getTotalCost(DiagnosisRecord *head) {
	DiagnosisRecord* tempPtr = head;
	SingleCost totalCost = constructSingleCost(0, 0, 0);
	while (tempPtr != NULL) {
		if (tempPtr->diagnosisSituation.setFlag == 0) {
			totalCost = costAdd(totalCost, tempPtr->diagnosisSituation.diagnosisSituationInfo.checkRecord.totalCost);
		}
		else if (tempPtr->diagnosisSituation.setFlag == 1) {
			totalCost = costAdd(totalCost, tempPtr->diagnosisSituation.diagnosisSituationInfo.prescribeRecord.totalCost);
		}
		else if (tempPtr->diagnosisSituation.setFlag == 2) {
			totalCost = costAdd(totalCost, tempPtr->diagnosisSituation.diagnosisSituationInfo.inHospitalRecord.costByNow);
		}
	}
	return totalCost;
}

void timePass(DiagnosisRecord *head, int day30, int day, int hour, int minute) {
	TimeRecord origin = currentTime;
	int originHour = currentTime.hour;
	currentTime.minute += minute;
	int passingDays = 0;
	while (currentTime.minute >= 60) {
		currentTime.minute -= 60;
		currentTime.hour += 1;
	}
	currentTime.hour += hour;
	while (currentTime.hour >= 24) {
		currentTime.hour -= 24;
		passingDays += 1;
	}
	passingDays += day + day30 * 30;
	currentTime.day += passingDays;
	int Day[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	while (currentTime.day >= Day[currentTime.month]) {
		currentTime.day -= Day[currentTime.month];
		currentTime.month += 1;
		if (currentTime.month >= 13) {
			currentTime.month -= 12;
		}
	}
	passingDays += (originHour < 8) - (currentTime.hour <= 8);
	DiagnosisRecord* tempPtr = head;
	while (tempPtr != NULL) {
		if (tempPtr->diagnosisSituation.setFlag == 2) {
			InHospitalRecord * res = &tempPtr->diagnosisSituation.diagnosisSituationInfo.inHospitalRecord;
			int nursingType = res->sickBedNumber % 100 / 10;
			int bedType = res->sickBedNumber % 10;
			int cost = actualExpense(origin, currentTime, bedType, nursingType);
			DiagnosisRecord* pre = findModifiedNode(DiagnosisRecordHead, tempPtr->patientInfo.registerId);
			InHospitalRecord*pas  = &pre->diagnosisSituation.diagnosisSituationInfo.inHospitalRecord;
			pas->deposit.yuan -= cost;
			pas->costByNow.yuan += cost;
			res->deposit.yuan -= cost;
			res->costByNow.yuan += cost;
			hospitalFund.inHosipitalCost.yuan += cost;
			hospitalFund.allCost.yuan += cost;

		}
		tempPtr = tempPtr->next;
	}
	//更新currentId		和  医生的请假情况
	if (passingDays >= 1){
		DoctorNodePushUp(passingDays);
		currentID = currentTime.month * 100000 + currentTime.day * 1000;
	}
}