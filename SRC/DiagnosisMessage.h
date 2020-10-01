#ifndef DIAGNOSISMESSAGE_H
#define DIAGNOSISMESSAGE_H

#define FILE_END -1      //数据末尾值";"
#define INVALID_DATA 0   //不合法值
#define LEGAL_DATA 1     //合法值
#define LACKED_DATA 2    //缺省值默认char*为"$",int为-1

#include <string.h>
#include <stdio.h>

typedef struct DiagnosisRecord;
typedef struct DoctorInfo;


typedef struct PatientInfo {  // 患者信息
    char name[20];  // 姓名
    int age;  // 年龄
    int registerId;  // 挂号(唯一)
};

PatientInfo constructPatientInfo(char name[20], int age, int registerId) {
    PatientInfo patientInfo;
    strcpy(patientInfo.name, name);
    patientInfo.age = age;
    patientInfo.registerId = registerId;
    return patientInfo;
}

typedef struct Section {  // 科室类
    int sectionId;  // 科室Id(唯一)
    DiagnosisRecord* nowDiagnosis; // 正在诊断
    DoctorInfo* DoctorsOfSectionHead; // 科室的医生（暂定最多20个）
    Section* next;
};

Section constructSection(int sectionId, DiagnosisRecord* nowDiagnosis,
    DoctorInfo* DoctorsOfSectionHead, Section* next) {
    Section section;
    section.sectionId = sectionId;
    section.nowDiagnosis = nowDiagnosis;
    section.DoctorsOfSectionHead = DoctorsOfSectionHead;
    section.next = next;
    return section;
};

typedef struct DoctorInfo {  // 医生信息
    char name[20];  // 姓名
    int level;  // 级别
    int sectionId;  // 所属科室编号
    bool consultTime[7];  // 出诊时间
    int id;  // 工号(唯一)
    int doctorStatus; // 医生状态
    bool inPostionStatus = 1;
};

DoctorInfo constructDoctorInfo(char name[20], int level,
    int sectionId, bool consultTime[7], int id, int doctorStatus, bool inPositionStatus) {
    DoctorInfo doctorInfo;
    strcpy(doctorInfo.name, name);
    doctorInfo.level = level;
    doctorInfo.sectionId = sectionId;
    for (int i = 0; i < 7; i++) {
        doctorInfo.consultTime[i] = consultTime[i];
    }
    doctorInfo.id = id;
    doctorInfo.doctorStatus = doctorStatus;
    doctorInfo.inPostionStatus = inPositionStatus;
    return doctorInfo;
}

typedef struct DoctorNode {
    DoctorInfo doctorInfo;
    DoctorNode* next;
};

DoctorNode constructDoctorNode(DoctorInfo doctorInfo, DoctorNode* next) {
    DoctorNode doctorNode;
    doctorNode.doctorInfo = doctorInfo;
    doctorNode.next = next;
    return doctorNode;
}

typedef struct SingleCost {  // 单个项目的价格
    int yuan;
    int jiao;
    int fen;
};

SingleCost constructSingleCost(int yuan, int jiao, int fen) {
    SingleCost singleCost;
    singleCost.yuan = yuan;
    singleCost.jiao = jiao;
    singleCost.fen = fen;
    return singleCost;
}

typedef struct CheckInfo { // 检查信息
    int checkId;
    SingleCost singleCost;
    CheckInfo* next;
};

CheckInfo constructCheckInfo(int checkId, SingleCost singleCost, CheckInfo* next) {
    CheckInfo checkInfo;
    checkInfo.singleCost = singleCost;
    checkInfo.next = next;
    return checkInfo;
}

typedef struct CheckRecord {  // 检查记录
    CheckInfo* checkInfoHead;  // 头指针
    int typeNumber;
    SingleCost totalCost;
};

CheckRecord constructCheckRecord(CheckInfo* checkInfoHead,
    int typeNumber, SingleCost totalCost) {
    CheckRecord checkRecord;
    checkRecord.checkInfoHead = checkInfoHead;
    checkRecord.typeNumber = typeNumber;
    checkRecord.totalCost = totalCost;
    return checkRecord;
}

typedef struct PrescribeInfo {
    int drugId;
    int drugNumber;
    PrescribeInfo* next;
};

PrescribeInfo constructPrescribeInfo(int drugId, int drugNumber, PrescribeInfo* next) {
    PrescribeInfo prescribeInfo;
    prescribeInfo.drugId = drugId;
    prescribeInfo.drugNumber = drugNumber;
    prescribeInfo.next = next;
    return prescribeInfo;
}

typedef struct PrescribeRecord {  // 开药类
    PrescribeInfo* prescribeInfoHead; // 头指针
    int typeNumber;
    SingleCost totalCost;
};

PrescribeRecord constructPrescribeRecord(PrescribeInfo* prescribeInfoHead,
    int typeNumber, SingleCost totalCost) {
    PrescribeRecord prescribeRecord;
    prescribeRecord.totalCost = totalCost;
    prescribeRecord.typeNumber = typeNumber;
    prescribeRecord.prescribeInfoHead = prescribeInfoHead;
    return prescribeRecord;
}

typedef struct TimeRecord {  // 日期
    int month;
    int day;
    int hour;
    int minute;
};

TimeRecord constructTimeRecord(int month, int day, int hour, int minute) {
    TimeRecord timeRecord;
    timeRecord.month = month;
    timeRecord.day = day;
    timeRecord.hour = hour;
    timeRecord.minute = minute;
    return timeRecord;
}

typedef struct InHospitalRecord {  // 住院类
    TimeRecord hospitalizedDate;
    TimeRecord predictedLeaveDate;
    SingleCost deposit;
    int spendDay;
};

InHospitalRecord constructInHospitalRecord(TimeRecord hospitalizedDate,
    TimeRecord predictedLeaveDate, SingleCost deposit, int spendDay) {
    InHospitalRecord inHospitalRecord;
    inHospitalRecord.hospitalizedDate = hospitalizedDate;
    inHospitalRecord.predictedLeaveDate = predictedLeaveDate;
    inHospitalRecord.deposit = deposit;
    inHospitalRecord.spendDay = spendDay;
    return inHospitalRecord;
}

typedef union DiagnosisSituationUnion {  // 诊疗情况信息
    CheckRecord checkRecord;
    PrescribeRecord prescribeRecord;
    InHospitalRecord inHospitalRecord;
};

typedef struct DiagnosisSituation {  // 诊疗情况
    int setFlag;
    DiagnosisSituationUnion diagnosisSituationInfo;
};

DiagnosisSituation constructDiagnosisSituation(int setFlag,
    DiagnosisSituationUnion diagnosisSituationInfo) {
    DiagnosisSituation diagnosisSituation;
    diagnosisSituation.setFlag = setFlag;
    diagnosisSituation.diagnosisSituationInfo = diagnosisSituationInfo;
    return diagnosisSituation;
}

typedef struct DiagnosisRecord {  // 诊疗记录
    TimeRecord recordTime; // 记录时间
    PatientInfo patientInfo;  // 患者信息
    DoctorInfo doctorinfo;  // 医生信息
    DiagnosisSituation diagnosisSituation;  // 诊疗情况
    DiagnosisRecord* next;
};

DiagnosisRecord constructDiagnosisRecord(TimeRecord recordTime, PatientInfo patientInfo,
    DoctorInfo doctorInfo, DiagnosisSituation diagnosisSituation,
    DiagnosisRecord* next) {
    DiagnosisRecord diagnosisRecord;
    diagnosisRecord.recordTime = recordTime;
    diagnosisRecord.patientInfo = patientInfo;
    diagnosisRecord.doctorinfo = doctorInfo;
    diagnosisRecord.diagnosisSituation = diagnosisSituation;
    diagnosisRecord.next = next;
    return diagnosisRecord;
}

typedef struct Ward {
    int wardId;
    int nursingType;
    int bedType;
    int totalBedNum;
    int occupiedBedNum;
    bool bedSituation[10];
    Ward* next;
};

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
}

bool checkError(DiagnosisRecord); // 检查诊疗记录是否有错

void FileInput(); // 从文件导入诊疗记录

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

#endif