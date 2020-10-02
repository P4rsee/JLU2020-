#pragma once

#define FILE_END -1      //����ĩβֵ";"
#define INVALID_DATA 0   //���Ϸ�ֵ
#define LEGAL_DATA 1     //�Ϸ�ֵ
#define LACKED_DATA 2    //ȱʡֵĬ��char*Ϊ"$",intΪ-1

#include <string.h>
#include <stdio.h>

typedef struct DiagnosisRecord;
typedef struct DoctorInfo;


typedef struct PatientInfo {  // ������Ϣ
    char name[20];  // ����
    int age;  // ����
    int registerId;  // �Һ�(Ψһ)
};

PatientInfo constructPatientInfo(char name[20], int age, int registerId);

typedef struct Section {  // ������
    int sectionId;  // ����Id(Ψһ)
    DiagnosisRecord* nowDiagnosis; // �������
    DoctorInfo* DoctorsOfSectionHead; // ���ҵ�ҽ�����ݶ����20����
    Section* next;
};

Section constructSection(int sectionId, DiagnosisRecord* nowDiagnosis,
    DoctorInfo* DoctorsOfSectionHead, Section* next);

typedef struct DoctorInfo {  // ҽ����Ϣ
    char name[20];  // ����
    int level;  // ����
    int sectionId;  // �������ұ��
    bool consultTime[7];  // ����ʱ��
    int id;  // ����(Ψһ)
    int doctorStatus; // ҽ��״̬
    bool inPostionStatus = 1;
    int busyDegree;
};

DoctorInfo constructDoctorInfo(char name[20], int level,
    int sectionId, bool consultTime[7], int id, int doctorStatus, bool inPositionStatus, int busyDegree);

typedef struct DoctorNode {
    DoctorInfo doctorInfo;
    DoctorNode* next;
};

DoctorNode constructDoctorNode(DoctorInfo doctorInfo, DoctorNode* next);

typedef struct SingleCost {  // ������Ŀ�ļ۸�
    int yuan;
    int jiao;
    int fen;
};

SingleCost constructSingleCost(int yuan, int jiao, int fen);

typedef struct CheckInfo { // �����Ϣ
    int checkId;
    SingleCost singleCost;
    CheckInfo* next;
};

CheckInfo constructCheckInfo(int checkId, SingleCost singleCost, CheckInfo* next);

typedef struct CheckRecord {  // ����¼
    CheckInfo* checkInfoHead;  // ͷָ��
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

typedef struct PrescribeRecord {  // ��ҩ��
    PrescribeInfo* prescribeInfoHead; // ͷָ��
    int typeNumber;
    SingleCost totalCost;
};

PrescribeRecord constructPrescribeRecord(PrescribeInfo* prescribeInfoHead,
    int typeNumber, SingleCost totalCost);

typedef struct TimeRecord {  // ����
    int month;
    int day;
    int hour;
    int minute;
};

TimeRecord constructTimeRecord(int month, int day, int hour, int minute);

typedef struct InHospitalRecord {  // סԺ��
    TimeRecord hospitalizedDate;
    TimeRecord predictedLeaveDate;
    TimeRecord leaveDate;
    int sickBedNumber; // ��λ��
    SingleCost deposit; // Ѻ��Ϊ100������
    SingleCost costByNow;  // ��ǰ���ѣ����ѳ�Ժ��ΪסԺ�ܿ���
};

InHospitalRecord constructInHospitalRecord(TimeRecord hospitalizedDate, TimeRecord predictedLeaveDate,
  TimeRecord leaveDate,int sickBedNumber, SingleCost deposit, SingleCost costByNow);

typedef union DiagnosisSituationUnion {  // ���������Ϣ
    CheckRecord checkRecord;
    PrescribeRecord prescribeRecord;
    InHospitalRecord inHospitalRecord;
};

typedef struct DiagnosisSituation {  // �������
    int setFlag;
    DiagnosisSituationUnion diagnosisSituationInfo;
};

DiagnosisSituation constructDiagnosisSituation(int setFlag,
    DiagnosisSituationUnion diagnosisSituationInfo);

typedef struct DiagnosisRecord {  // ���Ƽ�¼
    TimeRecord recordTime; // ��¼ʱ��
    PatientInfo patientInfo;  // ������Ϣ
    DoctorInfo doctorInfo;  // ҽ����Ϣ
    DiagnosisSituation diagnosisSituation;  // �������
    DiagnosisRecord* next;
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
    Ward* next;
};

Ward constructWard(int wardId, int nursingType, int bedType, int totalBedNum, int occupiedBedNum,
    bool bedSituation[10], Ward* next);

bool checkError(DiagnosisRecord); // ������Ƽ�¼�Ƿ��д�

void FileInput(); // ���ļ��������Ƽ�¼

SingleCost add(SingleCost costA, SingleCost costB);
