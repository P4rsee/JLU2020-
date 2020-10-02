#include "OutRecord.h"

void OutCheckRecord(FILE* fp, DiagnosisSituationUnion* tempInfo) {
    CheckInfo* nowPos = tempInfo->checkRecord.checkInfoHead;
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

// �����ҩ���͵����Ƽ�¼��
void OutPrescribeRecord(FILE* fp, DiagnosisSituationUnion* tempInfo) {
    PrescribeInfo* nowPos = tempInfo->prescribeRecord.prescribeInfoHead;
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

// ���סԺ���͵����Ƽ�¼��
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

// ������ݵ����Ƽ�¼��
void OutRecord(FILE* fp, DiagnosisRecord* record) {
    //                           ����       �Һ� ���� ���� ���� ���� ���� ����
    fprintf(fp, "# %02d%02d%02d%02d %07d %s %d %04d %02d %s %d ",
        record->recordTime.month,
        record->recordTime.day,
        record->recordTime.hour,
        record->recordTime.minute,
        record->patientInfo.registerId,
        record->patientInfo.name,
        record->patientInfo.age,
        record->doctorInfo.id,
        record->doctorInfo.sectionId,
        record->doctorInfo.name,
        record->doctorInfo.level
    );
    //80
    for (int i = 0; i < 7; i++)             // д�����ʱ��Ķ�������
        fprintf(fp, "%d", record->doctorInfo.consultTime[i] ? 1 : 0);
    fprintf(fp, " %d ", record->diagnosisSituation.setFlag); // д���������ͱ��
    // ����diagnosisSituationInfoȫ�øñ������� 
    DiagnosisSituationUnion* tempInfo =
        &record->diagnosisSituation.diagnosisSituationInfo;
    if (record->diagnosisSituation.setFlag == 0) {  // �����
        OutCheckRecord(fp, tempInfo);
    }
    else if (record->diagnosisSituation.setFlag == 1) {  // ��ҩ��
        OutPrescribeRecord(fp, tempInfo);
    }
    else if (record->diagnosisSituation.setFlag == 2) {  // סԺ��
        OutInHospitalRecord(fp, tempInfo);
    }
    fprintf(fp, " #\n");
}