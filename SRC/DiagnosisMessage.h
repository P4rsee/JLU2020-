#ifndef DIAGNOSISMESSAGE_H
#define DIAGNOSISMESSAGE_H

typedef struct PatientInfo {  // 患者信息
    char name[20];  // 姓名
    int age;  // 年龄
    int registerId;  // 挂号(唯一)
};

typedef struct DoctorInfo {  // 医生信息
    char name[20];  // 姓名
    int level;  // 级别
    int section;  // 科室
    bool consultTime[7];  // 出诊时间
    int id;  // 工号(唯一)
};

typedef struct SingleCost {  // 单个项目的价格
    int yuan;
    int jiao;
    int fen;
};

typedef struct CheckInfo { // 开药信息
    int checkId;
    SingleCost singleCost;
    CheckInfo* next;
};

typedef struct CheckRecord {  // 检查记录
    CheckInfo* checkInformationHead;  // 头指针
    int typeNumber;
    SingleCost totalCost;   
};

typedef struct PrescribeInfo { // 开药信息
    int drugId;
    int drugNumber;
    PrescribeInfo* next;
};

typedef struct PrescribeRecord {  // 开药类
    PrescribeInfo* prescribeInformationHead; // 头指针
    int typeNumber;
    SingleCost totalCost;
};

typedef struct TimeRecord {  // 日期
    int month;
    int day;
    int hour;
    int minute;
};

typedef struct InHospitalRecord {  // 住院类
    TimeRecord hospitalizedDate;
    TimeRecord predictedLeaveDate;
    SingleCost deposit;
};

typedef struct DiagnosisSituation {  // 诊疗情况
    int setFlag;
    union {  // 诊疗情况信息
        CheckRecord checkRecord;
        PrescribeRecord prescribeRecord;
        InHospitalRecord inHospitalRecord;
    } diagnosisSituationInfo;
};

typedef struct DiagnosisRecord {  // 诊疗记录
    TimeRecord recordTime; // 记录时间
    PatientInfo patientInfo;  // 患者信息
    DoctorInfo doctorinfo;  // 医生信息
    DiagnosisSituation diagnosisSituation;  // 诊疗情况
    DiagnosisRecord* next;
};

bool checkError(DiagnosisRecord); // 检查诊疗记录是否有错

void FileInput(); // 从文件导入诊疗记录

#endif
