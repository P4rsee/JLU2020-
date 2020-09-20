#include "DiagnosisMessage.h"
#include <stdlib.h>

TimeRecord currentTime;
int InhospitalMoney = 0;
int actualExpense(int spendDay) {
    return 100*spendDay;
}
void inHospitalCost(DiagnosisRecord *head, void (*callback)(DiagnosisRecord*)) {
    DiagnosisRecord* tempPtr = head;
    while(tempPtr != NULL) {
        if (tempPtr->diagnosisSituation.setFlag == 2) {
            InHospitalRecord tempRecord = tempPtr->diagnosisSituation.
            diagnosisSituationInfo.inHospitalRecord;
            tempRecord.spendDay++;
            int spendMoney = actualExpense(tempRecord.spendDay);
            tempRecord.deposit.yuan -= spendMoney;
            InhospitalMoney += spendMoney;
            if (tempRecord.deposit.yuan < 1000) {
                (*callback)(tempPtr);
            }
        }
        tempPtr = tempPtr->next;
    }
}

void timePass(DiagnosisRecord *head,void (*callback)(DiagnosisRecord*),
              int day30, int day, int hour, int minute) {
    currentTime.minute += minute;
    while (currentTime.minute >= 60) {
        currentTime.minute-=60;
        currentTime.hour+=1;
    }
    currentTime.hour += hour;
    while (currentTime.hour >= 24) {
        currentTime.hour-=24;
        currentTime.day += 1;
        inHospitalCost(head,callback);
    }
    currentTime.day += day + day30 * 30;
    for (int i = 1;i <= day;i++) {
        inHospitalCost(head,callback);
    }
    int Day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    while (currentTime.day >= Day[currentTime.month]) {
        currentTime.day -= Day[currentTime.month];
        currentTime.month += 1;
        if (currentTime.month >= 13) {
            currentTime.month -= 12;
        }
    }
}

SingleCost getIncome(DiagnosisRecord *head) {
    DiagnosisRecord *tempPtr = head;
    SingleCost totalCost;
    totalCost.yuan = totalCost.jiao = totalCost.fen = 0;
    while(tempPtr != NULL) {
        if (tempPtr->diagnosisSituation.setFlag == 0) {
            CheckRecord tempCheck = tempPtr->diagnosisSituation.
                              diagnosisSituationInfo.checkRecord;
            totalCost = add(totalCost,tempCheck.totalCost);
        }
        else if (tempPtr->diagnosisSituation.setFlag == 1) {
            PrescribeRecord tempPrescribe = tempPtr->diagnosisSituation.
            diagnosisSituationInfo.prescribeRecord;
        totalCost = add(totalCost,tempPrescribe.totalCost);    
        }
        tempPtr = tempPtr->next;
    }
    totalCost.yuan += InhospitalMoney;
    return totalCost;
}