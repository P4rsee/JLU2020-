#include "DiagnosisMessage.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

PatientInfo constructPatientInfo(char name[20], int age, int registerId) {
    PatientInfo patientInfo;
    strcpy(patientInfo.name, name);
    patientInfo.age = age;
    patientInfo.registerId = registerId;
    return patientInfo;
}


Section constructSection(int sectionId, DiagnosisRecord* nowDiagnosis,
    DoctorInfo* DoctorsOfSectionHead, Section* next) {
    Section section;
    section.sectionId = sectionId;
    section.nowDiagnosis = nowDiagnosis;
    section.DoctorsOfSectionHead = DoctorsOfSectionHead;
    section.next = next;
    return section;
};


DoctorInfo constructDoctorInfo(char name[20], int level,
    int sectionId, bool consultTime[7], int id, bool doctorStatus,int busyDegree) {
    DoctorInfo doctorInfo;
    strcpy(doctorInfo.name, name);
    doctorInfo.level = level;
    doctorInfo.sectionId = sectionId;
    doctorInfo.busyDegree = busyDegree;
    for (int i = 0; i < 7; i++) {
        doctorInfo.consultTime[i] = consultTime[i];
    }
    doctorInfo.id = id;
    doctorInfo.doctorStatus = doctorStatus;
    return doctorInfo;
}


DoctorNode constructDoctorNode(DoctorInfo doctorInfo, DoctorNode* next) {
    DoctorNode doctorNode;
    doctorNode.doctorInfo = doctorInfo;
    doctorNode.next = next;
    return doctorNode;
}


SingleCost constructSingleCost(int yuan, int jiao, int fen) {
    SingleCost singleCost;
    singleCost.yuan = yuan;
    singleCost.jiao = jiao;
    singleCost.fen = fen;
    return singleCost;
}

SingleCost constrcutSingleCost(char *costStr) {
    SingleCost singleCost;
    singleCost.yuan = 0;
    int position = 0;
    while(costStr[position] != '.')
        position++;
    for (int i = 0;i < position;i++) {
        singleCost.yuan = singleCost.yuan * 10 + (costStr[i] - '0');
    }
    singleCost.jiao = costStr[position + 1] - '0';
    singleCost.fen = costStr[position + 2] - '0';
    return singleCost;
}

CheckInfo constructCheckInfo(int checkId, SingleCost singleCost, CheckInfo* next) {
    CheckInfo checkInfo;
    checkInfo.singleCost = singleCost;
    checkInfo.next = next;
    return checkInfo;
}


CheckRecord constructCheckRecord(CheckInfo* checkInfoHead,
    int typeNumber, SingleCost totalCost) {
    CheckRecord checkRecord;
    checkRecord.checkInfoHead = checkInfoHead;
    checkRecord.typeNumber = typeNumber;
    checkRecord.totalCost = totalCost;
    return checkRecord;
}


PrescribeInfo constructPrescribeInfo(int drugId, int drugNumber, PrescribeInfo* next) {
    PrescribeInfo prescribeInfo;
    prescribeInfo.drugId = drugId;
    prescribeInfo.drugNumber = drugNumber;
    prescribeInfo.next = next;
    return prescribeInfo;
}


PrescribeRecord constructPrescribeRecord(PrescribeInfo* prescribeInfoHead,
    int typeNumber, SingleCost totalCost) {
    PrescribeRecord prescribeRecord;
    prescribeRecord.totalCost = totalCost;
    prescribeRecord.typeNumber = typeNumber;
    prescribeRecord.prescribeInfoHead = prescribeInfoHead;
    return prescribeRecord;
}


TimeRecord constructTimeRecord(int month, int day, int hour, int minute) {
    TimeRecord timeRecord;
    timeRecord.month = month;
    timeRecord.day = day;
    timeRecord.hour = hour;
    timeRecord.minute = minute;
    return timeRecord;
}

InHospitalRecord constructInHospitalRecord(TimeRecord hospitalizedDate, TimeRecord predictedLeaveDate,
  TimeRecord leaveDate,int sickBedNumber, SingleCost deposit, SingleCost costByNow) {
    InHospitalRecord inHospitalRecord;
    inHospitalRecord.hospitalizedDate = hospitalizedDate;
    inHospitalRecord.predictedLeaveDate = predictedLeaveDate;
    inHospitalRecord.deposit = deposit;
    inHospitalRecord.leaveDate = leaveDate;
    inHospitalRecord.sickBedNumber = sickBedNumber;
    inHospitalRecord.costByNow = costByNow;
    return inHospitalRecord;
}


DiagnosisSituation constructDiagnosisSituation(int setFlag,
    DiagnosisSituationUnion diagnosisSituationInfo) {
    DiagnosisSituation diagnosisSituation;
    diagnosisSituation.setFlag = setFlag;
    diagnosisSituation.diagnosisSituationInfo = diagnosisSituationInfo;
    return diagnosisSituation;
}

DiagnosisRecord constructDiagnosisRecord(TimeRecord recordTime, PatientInfo patientInfo,
    DoctorInfo doctorInfo, DiagnosisSituation diagnosisSituation,
    DiagnosisRecord* next) {
    DiagnosisRecord diagnosisRecord;
    diagnosisRecord.recordTime = recordTime;
    diagnosisRecord.patientInfo = patientInfo;
    diagnosisRecord.doctorInfo = doctorInfo;
    diagnosisRecord.diagnosisSituation = diagnosisSituation;
    diagnosisRecord.next = next;
    return diagnosisRecord;
}

DiagnosisRecord* initDiagnosisRecord() {
    DiagnosisRecord* DiagnosisRecordPtr = (DiagnosisRecord*) malloc(sizeof(DiagnosisRecord));
    DiagnosisRecordPtr->next = NULL;
    DiagnosisRecordPtr->patientInfo = constructPatientInfo("$", -1, -1);
    bool initConsultTime[] = {0,0,0,0,0,0,0};
    DiagnosisRecordPtr->doctorInfo = constructDoctorInfo("$", -1, -1,initConsultTime,-1, 0, -1);
    DiagnosisRecordPtr->recordTime = constructTimeRecord(-1,-1,-1,-1);
    DiagnosisSituationUnion tempUnion;
    tempUnion.checkRecord = constructCheckRecord(NULL,-1,constructSingleCost(-1, -1, -1));
    DiagnosisRecordPtr->diagnosisSituation = constructDiagnosisSituation(-1,tempUnion);
    return DiagnosisRecordPtr;
}

Ward constructWard(int wardId, int nursingType, int bedType, int totalBedNum, int occupiedBedNum,
    bool bedSituation[10], Ward* next) {
    Ward ward;
    ward.wardId = wardId;
    ward.nursingType = nursingType;
    ward.bedType = bedType;
    ward.totalBedNum = totalBedNum;
    ward.occupiedBedNum = occupiedBedNum;
    ward.next = next;
    for (int i = 0; i < 10; i++)
        ward.bedSituation[i] = bedSituation[i];
    return ward;
}


SingleCost costAdd(SingleCost costA, SingleCost costB) {
    costA.fen += costB.fen;
    costA.jiao += costB.jiao;
    costA.yuan += costB.yuan;
    while (costA.fen >= 100) {
        costA.fen -= 100;
        costA.jiao++;
    }
    while (costA.jiao >= 100) {
        costA.jiao -= 100;
        costA.yuan++;
    }
    return costA;
}
