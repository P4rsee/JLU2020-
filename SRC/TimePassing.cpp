#include "DiagnosisMessage.h"
#include "TimePassing.h"
#include <stdlib.h>
#include "global.h"


int actualExpense(TimeRecord startDate, TimeRecord endDate) {
    int day[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int startMonth = startDate.month, endMonth = endDate.month;
    int countday = day[startMonth] - startDate.day + endDate.day;
    startMonth++;
    while(startMonth < endMonth) {
        countday += day[startMonth++];
    }
    return 100 * countday;
}

SingleCost getTotalCost(DiagnosisRecord *head) {
    DiagnosisRecord* tempPtr = head;
    SingleCost totalCost = constructSingleCost(0,0,0);
    while(tempPtr != NULL) {
        if (tempPtr->diagnosisSituation.setFlag == 0) {
            totalCost = costAdd(totalCost, tempPtr->diagnosisSituation.diagnosisSituationInfo.checkRecord.totalCost);
        } else if (tempPtr->diagnosisSituation.setFlag == 1) {
            totalCost = costAdd(totalCost, tempPtr->diagnosisSituation.diagnosisSituationInfo.prescribeRecord.totalCost);
        } else if (tempPtr->diagnosisSituation.setFlag == 2) {
            totalCost = costAdd(totalCost, tempPtr->diagnosisSituation.diagnosisSituationInfo.inHospitalRecord.costByNow);
        }
    }
    return totalCost;
}

void timePass(DiagnosisRecord *head, int day30, int day, int hour, int minute) {
    int originHour = currentTime.hour;
    currentTime.minute += minute;
    int passingDays = 0;
    while (currentTime.minute >= 60) {
        currentTime.minute-=60;
        currentTime.hour+=1;
    }
    currentTime.hour += hour;
    while (currentTime.hour >= 24) {
        currentTime.hour-=24;
        passingDays += 1;
    }
    passingDays += day + day30 * 30;
    currentTime.day += passingDays;
    int Day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    while (currentTime.day >= Day[currentTime.month]) {
        currentTime.day -= Day[currentTime.month];
        currentTime.month += 1;
        if (currentTime.month >= 13) {
            currentTime.month -= 12;
        }
    }
    passingDays += (originHour < 8) - (currentTime.hour <= 8);
    DiagnosisRecord* tempPtr = head;
    while(tempPtr != NULL) {
        if (tempPtr->diagnosisSituation.setFlag == 2) {
            tempPtr->diagnosisSituation.diagnosisSituationInfo.inHospitalRecord.leaveDate;
        }
        tempPtr = tempPtr->next;
    }
}
