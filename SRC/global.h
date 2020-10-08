#pragma once
#include "DiagnosisMessage.h"

typedef struct HospitalFund {
	SingleCost checkCost, drugCost, inHosipitalCost, allCost;
	char stringOfCheck[30], stringOfDrug[30];
	char stringOfInHospital[30], stringOfAll[30];
};

extern HospitalFund hospitalFund; // 医院资金

extern int currentID;

extern TimeRecord currentTime;

extern char doctorType[4][15];

extern char doctorSection[7][15];

extern DoctorNode* DoctorHead;

void FundPushUp(); // 更新全局的Fund

void DoctorNodePushUp(int passDay);

// LYN
extern DiagnosisRecord* DiagnosisRecordHead;
extern DiagnosisRecord* InHospitalHead;
extern DiagnosisRecord* OthersHead;
//extern DoctorNode* DoctorHead;
extern Ward* WardHead;
extern int drugPriceList[31];
extern int checkPriceList[31];
extern char nursingType[3][8];
extern char bedType[4][8];