#pragma once
#define FILE_END -1      // 锟斤拷锟斤拷末尾值";"
#define INVALID_DATA 0   // 锟斤拷锟较凤拷值
#define LEGAL_DATA 1     // 锟较凤拷值
#define LACKED_DATA 2    // 缺省值默锟斤拷char*为"$",int为-1
#include <string.h>
#include <stdio.h>

typedef struct DiagnosisRecord;
typedef struct DoctorInfo;

typedef struct PatientInfo {  // 锟斤拷锟斤拷锟斤拷息
  char name[50];  // 锟斤拷锟斤拷
  int age;  // 锟斤拷锟斤拷
  int registerId;  // 锟揭猴拷(唯一)
};

PatientInfo constructPatientInfo(const char * name, int age, int registerId);

typedef struct Section {  // 锟斤拷锟斤拷锟斤拷
  int sectionId;  // 锟斤拷锟斤拷Id(唯一)
  DiagnosisRecord* nowDiagnosis;  // 锟斤拷锟斤拷锟斤拷锟�
  DoctorInfo* DoctorsOfSectionHead;  // 锟斤拷锟揭碉拷医锟斤拷锟斤拷锟捷讹拷锟斤拷锟�20锟斤拷锟斤拷
  Section* next = NULL;
};

Section constructSection(int sectionId, DiagnosisRecord* nowDiagnosis,
  DoctorInfo* DoctorsOfSectionHead, Section* next);

typedef struct DoctorInfo {  // 医锟斤拷锟斤拷息
  char name[50];  // 锟斤拷锟斤拷
  int level;  // 锟斤拷锟斤拷
  int sectionId;  // 锟斤拷锟斤拷锟斤拷锟揭憋拷锟�
  bool consultTime[7];  // 锟斤拷锟斤拷时锟斤拷
  int id;  // 锟斤拷锟斤拷(唯一)
  int doctorStatus;  // 医锟斤拷状态
  int busyDegree;
  int vacationLeft;
};

DoctorInfo constructDoctorInfo(const char * name, int level,
  int sectionId, bool consultTime[7], int id, bool doctorStatus, int busyDegree);

typedef struct DoctorNode {
  DoctorInfo doctorInfo;
  DoctorNode* next = NULL;
};

DoctorNode constructDoctorNode(DoctorInfo doctorInfo, DoctorNode* next);

typedef struct SingleCost {  // 锟斤拷锟斤拷锟斤拷目锟侥价革拷
  int yuan;
  int jiao;
  int fen;
};

SingleCost constructSingleCost(int yuan, int jiao, int fen);

SingleCost constructSingleCost(char *);

typedef struct CheckInfo {  // 锟斤拷锟斤拷锟较�
  int checkId;
  SingleCost singleCost;
  CheckInfo* next = NULL;
};

CheckInfo constructCheckInfo(int checkId, SingleCost singleCost, CheckInfo* next);

typedef struct CheckRecord {  // 锟斤拷锟斤拷录
  CheckInfo* checkInfoHead;  // 头指锟斤拷
  int typeNumber;
  SingleCost totalCost;
};

CheckRecord constructCheckRecord(CheckInfo* checkInfoHead,
  int typeNumber, SingleCost totalCost);

typedef struct PrescribeInfo {
  int drugId;
  int drugNumber;
  PrescribeInfo* next = NULL;
};

PrescribeInfo constructPrescribeInfo(int drugId, int drugNumber, PrescribeInfo* next);

typedef struct PrescribeRecord {  // 锟斤拷药锟斤拷
  PrescribeInfo* prescribeInfoHead; // 头指锟斤拷
  int typeNumber;
  SingleCost totalCost;
};

PrescribeRecord constructPrescribeRecord(PrescribeInfo* prescribeInfoHead,
  int typeNumber, SingleCost totalCost);

typedef struct TimeRecord {  // 锟斤拷锟斤拷
  int month;
  int day;
  int hour;
  int minute;
};

TimeRecord constructTimeRecord(int month, int day, int hour, int minute);

typedef struct InHospitalRecord {  // 住院锟斤拷
  TimeRecord hospitalizedDate;
  TimeRecord predictedLeaveDate;
  TimeRecord leaveDate;
  int sickBedNumber;  // 锟斤拷锟斤拷锟斤拷+锟斤拷位锟斤拷 2+2位锟斤拷
  SingleCost deposit;  // 押锟斤拷为100锟斤拷锟斤拷锟斤拷
  SingleCost costByNow;  // 锟斤拷前锟斤拷锟窖ｏ拷锟斤拷锟窖筹拷院锟斤拷为住院锟杰匡拷锟斤拷
};

InHospitalRecord constructInHospitalRecord(TimeRecord hospitalizedDate, TimeRecord predictedLeaveDate,
  TimeRecord leaveDate, int sickBedNumber, SingleCost deposit, SingleCost costByNow);

typedef union DiagnosisSituationUnion {  // 锟斤拷锟斤拷锟斤拷锟斤拷锟较�
  CheckRecord checkRecord;
  PrescribeRecord prescribeRecord;
  InHospitalRecord inHospitalRecord;
};

typedef struct DiagnosisSituation {  // 锟斤拷锟斤拷锟斤拷锟�
  int setFlag;
  DiagnosisSituationUnion diagnosisSituationInfo;
};

DiagnosisSituation constructDiagnosisSituation(int setFlag,
  DiagnosisSituationUnion diagnosisSituationInfo);

typedef struct DiagnosisRecord {  // 锟斤拷锟狡硷拷录
  TimeRecord recordTime;  // 锟斤拷录时锟斤拷
  PatientInfo patientInfo;  // 锟斤拷锟斤拷锟斤拷息
  DoctorInfo doctorInfo;  // 医锟斤拷锟斤拷息
  DiagnosisSituation diagnosisSituation;  // 锟斤拷锟斤拷锟斤拷锟�
  DiagnosisRecord* next = NULL;
};

DiagnosisRecord constructDiagnosisRecord(TimeRecord recordTime, PatientInfo patientInfo,
  DoctorInfo doctorInfo, DiagnosisSituation diagnosisSituation,
  DiagnosisRecord* next);

typedef struct Ward {
  int wardId;
  int nursingType;
  int bedType;
  int totalBedNum;
  int occupiedBedNum;
  bool bedSituation[10];
  Ward* next = NULL;
};

Ward constructWard(int wardId, int nursingType, int bedType, int totalBedNum, int occupiedBedNum,
  bool bedSituation[10], Ward* next);

bool checkError(DiagnosisRecord);  // 锟斤拷锟斤拷锟斤拷萍锟铰硷拷欠锟斤拷写锟�

DiagnosisRecord* initDiagnosisRecord();

SingleCost costAdd(SingleCost costA, SingleCost costB);

char* convertSingleCostToString(SingleCost);

TimeRecord convertStringToTimeRecord(const char*);

char* convertTimeRecordToString(const TimeRecord);
