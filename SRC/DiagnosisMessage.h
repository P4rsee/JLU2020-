#pragma once

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

PatientInfo constructPatientInfo(char name[20], int age, int registerId);

typedef struct Section {  // 科室类
    int sectionId;  // 科室Id(唯一)
    DiagnosisRecord* nowDiagnosis; // 正在诊断
    DoctorInfo* DoctorsOfSectionHead; // 科室的医生（暂定最多20个）
    Section* next;
};

Section constructSection(int sectionId, DiagnosisRecord* nowDiagnosis,
    DoctorInfo* DoctorsOfSectionHead, Section* next);

typedef struct DoctorInfo {  // 医生信息
    char name[20];  // 姓名
    int level;  // 级别
    int sectionId;  // 所属科室编号
    bool consultTime[7];  // 出诊时间
    int id;  // 工号(唯一)
    bool doctorStatus; // 医生状态
    int busyDegree; //繁忙程度
};

DoctorInfo constructDoctorInfo(char name[20], int level,
    int sectionId, bool consultTime[7], int id, bool doctorStatus, int busyDegree);

typedef struct DoctorNode {
    DoctorInfo doctorInfo;
    DoctorNode* next;
};

DoctorNode constructDoctorNode(DoctorInfo doctorInfo, DoctorNode* next);

typedef struct SingleCost {  // 单个项目的价格
    int yuan;
    int jiao;
    int fen;
};

SingleCost constructSingleCost(int yuan, int jiao, int fen);

SingleCost constructSingleCost(char *);

typedef struct CheckInfo { // 检查信息
    int checkId;
    SingleCost singleCost;
    CheckInfo* next;
};

CheckInfo constructCheckInfo(int checkId, SingleCost singleCost, CheckInfo* next);

typedef struct CheckRecord {  // 检查记录
    CheckInfo* checkInfoHead;  // 头指针
    int typeNumber;
    SingleCost totalCost;
};

CheckRecord constructCheckRecord(CheckInfo* checkInfoHead,
    int typeNumber, SingleCost totalCost);

typedef struct PrescribeInfo {
    int drugId;
    int drugNumber;
    PrescribeInfo* next;
};

PrescribeInfo constructPrescribeInfo(int drugId, int drugNumber, PrescribeInfo* next);

typedef struct PrescribeRecord {  // 开药类
    PrescribeInfo* prescribeInfoHead; // 头指针
    int typeNumber;
    SingleCost totalCost;
};

PrescribeRecord constructPrescribeRecord(PrescribeInfo* prescribeInfoHead,
    int typeNumber, SingleCost totalCost);

typedef struct TimeRecord {  // 日期
    int month;
    int day;
    int hour;
    int minute;
};

TimeRecord constructTimeRecord(int month, int day, int hour, int minute);

typedef struct InHospitalRecord {  // 住院类
    TimeRecord hospitalizedDate;
    TimeRecord predictedLeaveDate;
    TimeRecord leaveDate;
    int sickBedNumber; // 床位号
    SingleCost deposit; // 押金为100的整数
    SingleCost costByNow;  // 当前花费，若已出院则为住院总开销
};

InHospitalRecord constructInHospitalRecord(TimeRecord hospitalizedDate, TimeRecord predictedLeaveDate,
  TimeRecord leaveDate,int sickBedNumber, SingleCost deposit, SingleCost costByNow);

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
    DiagnosisSituationUnion diagnosisSituationInfo);

typedef struct DiagnosisRecord {  // 诊疗记录
    TimeRecord recordTime; // 记录时间
    PatientInfo patientInfo;  // 患者信息
    DoctorInfo doctorInfo;  // 医生信息
    DiagnosisSituation diagnosisSituation;  // 诊疗情况
    DiagnosisRecord* next;
};

DiagnosisRecord constructDiagnosisRecord(TimeRecord recordTime, PatientInfo patientInfo,
    DoctorInfo doctorInfo, DiagnosisSituation diagnosisSituation,
    DiagnosisRecord* next);

DiagnosisRecord* initDiagnosisRecord();

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
    bool bedSituation[10], Ward* next);

bool checkError(DiagnosisRecord); // 检查诊疗记录是否有错

void FileInput(); // 从文件导入诊疗记录

SingleCost costAdd(SingleCost costA, SingleCost costB);
