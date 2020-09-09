#ifndef DIAGNOSISMESSAGE_H
#define DIAGNOSISMESSAGE_H

typedef struct PatientInformation {  // 患者信息
    char name[20];  // 姓名
    int age;  // 年龄
    int registerId;  // 挂号(唯一)
};

typedef struct DoctorInformation {  // 医生信息
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

typedef struct CheckInformation { // 开药信息
    int checkId;
    SingleCost singleCost;
    CheckInformation* next;
};

typedef struct CheckRecord {  // 检查记录
    CheckInformation* checkInformationHead;  // 头指针
    int typeNumber;
    SingleCost totalCost;   
};

typedef struct PrescribeInformation { // 开药信息
    int drugId;
    int drugNumber;
    PrescribeInformation* next;
};

typedef struct PrescribeRecord {  // 开药类
    PrescribeInformation* prescribeInformationHead; // 头指针
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
    } diagnosisSituationInformation;
};

typedef struct DiagnosisRecord {  // 诊疗记录
    TimeRecord recordTime; // 记录时间
    PatientInformation patientInformation;  // 患者信息
    DoctorInformation doctorinformation;  // 医生信息
    DiagnosisSituation diagnosisSituation;  // 诊疗情况
    DiagnosisRecord* next;
};

bool checkError(DiagnosisRecord); // 检查诊疗记录是否有错

void FileInput(); // 从文件导入诊疗记录

#endif
