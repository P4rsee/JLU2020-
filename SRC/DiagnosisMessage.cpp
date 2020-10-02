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
    int sectionId, bool consultTime[7], int id, int doctorStatus, bool inPositionStatus,int busyDegree) {
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
    doctorInfo.inPostionStatus = inPositionStatus;
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


SingleCost add(SingleCost costA, SingleCost costB) {
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
