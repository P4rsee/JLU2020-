#include "OutRecord.h"

void OutCheckRecord(FILE* fp, DiagnosisSituationUnion* tempInfo) {
    CheckInfo* nowPos = tempInfo->checkRecord.checkInformationHead;
    fprintf(fp, "%d %d %d %d",
        tempInfo->checkRecord.totalCost.yuan,
        tempInfo->checkRecord.totalCost.jiao,
        tempInfo->checkRecord.totalCost.fen,
        tempInfo->checkRecord.typeNumber
    );
    for (int i = 0; i < tempInfo->checkRecord.typeNumber; i++) {
        nowPos = nowPos->next;
        fprintf(fp, " %d %d %d %d",
            nowPos->checkId, nowPos->singleCost.yuan,
            nowPos->singleCost.jiao, nowPos->singleCost.fen);
    }
}

// 输出开药类型到诊疗记录中
void OutPrescribeRecord(FILE* fp, DiagnosisSituationUnion* tempInfo) {
    PrescribeInfo* nowPos = tempInfo->prescribeRecord.prescribeInformationHead;
    fprintf(fp, "%d %d %d %d",
        tempInfo->prescribeRecord.totalCost.yuan,
        tempInfo->prescribeRecord.totalCost.jiao,
        tempInfo->prescribeRecord.totalCost.fen,
        tempInfo->prescribeRecord.typeNumber
    );
    for (int i = 0; i < tempInfo->prescribeRecord.typeNumber; i++) {
        nowPos = nowPos->next;
        fprintf(fp, " %d %d", nowPos->drugId, nowPos->drugNumber);
    }
}

// 输出住院类型到诊疗记录中
void OutInHospitalRecord(FILE* fp, DiagnosisSituationUnion* tempInfo) {
    fprintf(fp, "%02d%02d%02d%02d %02d%02d%02d%02d %d",
        tempInfo->inHospitalRecord.hospitalizedDate.month,
        tempInfo->inHospitalRecord.hospitalizedDate.day,
        tempInfo->inHospitalRecord.hospitalizedDate.hour,
        tempInfo->inHospitalRecord.hospitalizedDate.minute,
        tempInfo->inHospitalRecord.predictedLeaveDate.month,
        tempInfo->inHospitalRecord.predictedLeaveDate.day,
        tempInfo->inHospitalRecord.predictedLeaveDate.hour,
        tempInfo->inHospitalRecord.predictedLeaveDate.minute,
        tempInfo->inHospitalRecord.deposit.yuan
    );
}

// 输出数据到诊疗记录中
void OutRecord(FILE* fp, DiagnosisRecord* record) {
    //                           日期       挂号 姓名 年龄 工号 科室 姓名 级别
    fprintf(fp, "# %02d%02d%02d%02d %07d %s %d %04d %02d %s %d ",
        record->TimeRecord.month,
        record->TimeRecord.day,
        record->TimeRecord.hour,
        record->TimeRecord.minute,
        record->patientInfo.registerId,
        record->patientInfo.name,
        record->patientInfo.age,
        record->doctorInfo.id,
        record->doctorInfo.section,
        record->doctorInfo.name,
        record->doctorInfo.level
    );
    //80
    for (int i = 0; i < 7; i++)             // 写入出诊时间的二进制码
        fprintf(fp, "%d", record->doctorInfo.consultTime[i] ? 1 : 0);
    fprintf(fp, " %d ", record->diagnosisSituation.setFlag); // 写入诊疗类型编号
    // 以下diagnosisSituationInfo全用该变量代替 
    DiagnosisSituationUnion* tempInfo =
        &record->diagnosisSituation.diagnosisSituationInfo;
    if (record->diagnosisSituation.setFlag == 0) {  // 检查类
        OutCheckRecord(fp, tempInfo);
    }
    else if (record->diagnosisSituation.setFlag == 1) {  // 开药类
        OutPrescribeRecord(fp, tempInfo);
    }
    else if (record->diagnosisSituation.setFlag == 2) {  // 住院类
        OutInHospitalRecord(fp, tempInfo);
    }
    fprintf(fp, " #\n");
}