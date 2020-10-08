#include "InRecord.h"

// ��ֵ����
void SetDate(char* str, int* month, int* day, int* hour, int* minute) {
    (*month) = atoi(str) / 1000000;
    (*day) = atoi(str) / 10000 % 100;
    (*hour) = atoi(str) % 10000 / 100;
    (*minute) = atoi(str) % 100;
}

// �����ļ����� �жϷ��� ���Ϸ���ֵ����
int GetCost(FILE* fp, int* yuan, int* jiao, int* fen) { // �������
    char cache[100]; int flag = 0;
    fscanf(fp, "%s", cache);
    if (IsEnd(cache)) return FILE_END;
    if (!IsNumber(cache)) flag = 1;  // Ԫ
    else (*yuan) = atoi(cache);
    fscanf(fp, "%s", cache);
    if (IsEnd(cache)) return FILE_END;
    if (!IsNumber(cache)) flag = 1;  // ��
    else {
        (*jiao) = atoi(cache);
        if (atoi(cache) > 9) flag = 1;
    }
    fscanf(fp, "%s", cache);
    if (IsEnd(cache)) return FILE_END;
    if (!IsNumber(cache)) flag = 1;  // ��
    else {
        (*fen) = atoi(cache);
        if (atoi(cache) > 9) flag = 1;
    }
    return !flag ? LEGAL_DATA : INVALID_DATA;
}

// ��ȡ��Ӧ�������йص���Ϣ
int GetCheckInfo(FILE* fp, DiagnosisSituationUnion* tempInfo) {
    char cache[100];  // ��ʱ�洢 ���ڼ��
    int flag = 0; // ����Ƿ��д���
    int retInt = 0; // ��¼ÿ�μ��ķ���ֵ
    retInt = GetCost(fp, &tempInfo->checkRecord.totalCost.yuan,
        &tempInfo->checkRecord.totalCost.jiao,
        &tempInfo->checkRecord.totalCost.fen); // ����ܷ���
    if (retInt != LEGAL_DATA) {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    if (IsEnd(cache)) return FILE_END;
    int count = 0;  // ��¼�����Ŀ
    if (!IsNumber(cache)) flag = 1;
    else {
        count = atoi(cache);
        tempInfo->checkRecord.typeNumber = count;
    }
    if (tempInfo->checkRecord.checkInformationHead == NULL) {
        tempInfo->checkRecord.checkInformationHead = (CheckInfo*)malloc(sizeof(CheckInfo));
    }
    CheckInfo* nowCheck = tempInfo->checkRecord.checkInformationHead; // ��ǰλ��ָ��ͷ�ڵ�
    nowCheck->next = NULL; nowCheck->checkId = 0; 
    nowCheck->singleCost.yuan = nowCheck->singleCost.jiao = nowCheck->singleCost.fen = 0;
    int totYuan = 0, totJiao = 0, totFen = 0;
    for (int i = 0; i < count; i++) { // ¼��ÿ�ּ��
        CheckInfo* nextCheck = (CheckInfo*)malloc(sizeof(CheckInfo)); // ��һ���ڵ�
        fscanf(fp, "%s", cache);
        if (!IsNumber(cache)) flag = 1;
        else nextCheck->checkId = atoi(cache); // ��¼�����
        if (IsEnd(cache)) { // ��¼��ǰ��ֹ
            flag = FILE_END; break;
        }
        retInt = GetCost(fp, &nextCheck->singleCost.yuan,
            &nextCheck->singleCost.jiao,
            &nextCheck->singleCost.fen); // ���ּ��ķ���
        nowCheck->next = nextCheck;
        nowCheck = nextCheck;
        if (retInt != LEGAL_DATA) {
            flag = 1; if (retInt == FILE_END) {
                flag = FILE_END; break;  // ��¼��ǰ��ֹ
            }
        }
        else {
            totFen += nextCheck->singleCost.fen;
            if (totFen >= 10) {
                totFen -= 10; totJiao++;
            }
            totJiao += nextCheck->singleCost.jiao;
            if (totJiao >= 10) {
                totJiao -= 10; totYuan++;
            }
            totYuan += nextCheck->singleCost.yuan;
        }
    }
    nowCheck->next = NULL; // ע�� ��������Ŀ����count˵����ȥ֮����ֱ�Ӷ���������
    if (totYuan != tempInfo->checkRecord.totalCost.yuan ||
        totJiao != tempInfo->checkRecord.totalCost.jiao ||
        totFen != tempInfo->checkRecord.totalCost.fen)flag = 1;
    if (flag) {  // ����� free���� or free�����������ʵ�� ���� �ظ�ʵ��ȷ��free
        if (flag == FILE_END)return FILE_END;
        else return INVALID_DATA;
    }
    else {
        return LEGAL_DATA;
    }
}

// ��ȡ��Ӧ���뿪ҩ�йص���Ϣ
int GetPrescribeInfo(FILE* fp, DiagnosisSituationUnion* tempInfo) {
    char cache[100];  // ��ʱ�洢 ���ڼ��
    int flag = 0; // ����Ƿ��д���
    int retInt = 0; // ��¼ÿ�μ��ķ���ֵ
    retInt = GetCost(fp, &tempInfo->checkRecord.totalCost.yuan,
        &tempInfo->checkRecord.totalCost.jiao,
        &tempInfo->checkRecord.totalCost.fen); // ����ܷ���
    if (retInt != LEGAL_DATA) {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    if (IsEnd(cache)) return FILE_END;
    int count = 0;  // ��¼��ҩ����
    if (!IsNumber(cache)) flag = 1;
    else {
        count = atoi(cache);
        tempInfo->prescribeRecord.typeNumber = count;
    }
    // ��ǰλ��ָ��ͷ�ڵ�
    if (tempInfo->prescribeRecord.prescribeInformationHead == NULL) {
        tempInfo->prescribeRecord.prescribeInformationHead = 
            (PrescribeInfo*)malloc(sizeof(PrescribeInfo));
    }
    PrescribeInfo* nowDrug = tempInfo->prescribeRecord.prescribeInformationHead;
    nowDrug->next = NULL; nowDrug->drugId = nowDrug->drugNumber = 0;
    for (int i = 0; i < count; i++) { // ÿ��ҩƷ
        PrescribeInfo* nextDrug = (PrescribeInfo*)malloc(sizeof(PrescribeInfo));  // ��һ���ڵ�
        fscanf(fp, "%s", cache);
        if (!IsNumber(cache)) flag = 1;
        else nextDrug->drugId = atoi(cache); // ��¼ҩƷ���
        if (IsEnd(cache)) {
            flag = FILE_END; break;
        }
        fscanf(fp, "%s", cache);
        if (!IsNumber(cache)) flag = 1;
        else nextDrug->drugNumber = atoi(cache); // ��¼ҩƷ����
        if (IsEnd(cache)) {
            flag = FILE_END; break;
        }
        nowDrug->next = nextDrug;
        nowDrug = nextDrug;
    }
    nowDrug->next = NULL;
    if (flag) {  // ����� free����
        if (flag == FILE_END)return FILE_END;
        else return INVALID_DATA;
    }
    else {
        return LEGAL_DATA;
    }
}

// ��ȡ��Ӧ����סԺ�йص���Ϣ
int GetInHospitalInfo(FILE* fp, DiagnosisSituationUnion* tempInfo) {
    char cache[100];  // ��ʱ�洢 ���ڼ��
    int flag = 0; // ����Ƿ��д���
    int retInt = 0; // ��¼ÿ�μ��ķ���ֵ
    fscanf(fp, "%s", cache);
    retInt = IsDate(cache);
    if (retInt == 1) { // ��Ժ����
        SetDate(cache, &tempInfo->inHospitalRecord.hospitalizedDate.month,
            &tempInfo->inHospitalRecord.hospitalizedDate.day,
            &tempInfo->inHospitalRecord.hospitalizedDate.hour,
            &tempInfo->inHospitalRecord.hospitalizedDate.minute);
    }
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    retInt = IsDate(cache);
    if (retInt == 1) { // Ԥ�Ƴ�Ժ����
        SetDate(cache, &tempInfo->inHospitalRecord.predictedLeaveDate.month,
            &tempInfo->inHospitalRecord.predictedLeaveDate.day,
            &tempInfo->inHospitalRecord.predictedLeaveDate.hour,
            &tempInfo->inHospitalRecord.predictedLeaveDate.minute);
    }
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    retInt = IsDeposit(cache);
    if (retInt == 1) {
        tempInfo->inHospitalRecord.deposit.yuan = atoi(cache);
    }
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    if (flag)return INVALID_DATA;
    else return LEGAL_DATA;
}

// ���ļ������Ӧ����������
int GetDiagnosisSituationInfo(FILE* fp, DiagnosisRecord* res) {
    int retInt = 0; // ��¼ÿ�μ��ķ���ֵ
    DiagnosisSituationUnion* tempInfo =
        &res->diagnosisSituation.diagnosisSituationInfo;
    if (res->diagnosisSituation.setFlag == 0) {  // �����
        retInt = GetCheckInfo(fp, tempInfo);
    }
    else if (res->diagnosisSituation.setFlag == 1) {  // ��ҩ��
        retInt = GetPrescribeInfo(fp, tempInfo);
    }
    else if (res->diagnosisSituation.setFlag == 2) {  // סԺ��
        retInt = GetInHospitalInfo(fp, tempInfo);
    }
    else retInt = INVALID_DATA;  // �������͵ı�ų���
    return retInt; // ��� �ô��д�����
}

// ���ļ��ֻ�ȡ���������Ϣ
int GetPatientRecord(FILE* fp, DiagnosisRecord* res) {
    char cache[100];  // ��ʱ�洢 ���ڼ��
    int flag = 0; // ����Ƿ��д���
    int retInt = 0; // ��¼ÿ�μ��ķ���ֵ
    fscanf(fp, "%s", cache);
    retInt = IsRegisterId(cache); // ��黼�߹Һ�
    if (retInt == LEGAL_DATA) res->patientInfo.registerId = atoi(cache);  // �ҺźϷ�
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    retInt = IsName(cache); // ��黼�����������Ƿ����� ��20��(char[40])������Ϊ����
    if (retInt == LEGAL_DATA) {  // �����Ϸ�
        strcpy(res->patientInfo.name, cache);
    }
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    retInt = IsAge(cache); // ��黼������
    if (retInt == LEGAL_DATA) res->patientInfo.age = atoi(cache);  // ����Ϸ�
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    if (flag)return INVALID_DATA;
    else return LEGAL_DATA;
}

// ���ļ��л�ȡҽ�������Ϣ
int GetDoctorRecord(FILE* fp, DiagnosisRecord* res) {
    char cache[100];  // ��ʱ�洢 ���ڼ��
    int flag = 0; // ����Ƿ��д���
    int retInt = 0; // ��¼ÿ�μ��ķ���ֵ
    fscanf(fp, "%s", cache);
    retInt = IsDoctorId(cache); // ���ҽ������
    if (retInt == LEGAL_DATA) res->doctorInfo.id = atoi(cache);  // ���źϷ�
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    // ������
    fscanf(fp, "%s", cache);
    retInt = IsSection(cache);
    if (retInt == LEGAL_DATA) {
        res->doctorInfo.section = atoi(cache); // ���ҺϷ�
    }
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    retInt = IsName(cache);  // ���ҽ������ ���ƻ�������
    if (retInt == LEGAL_DATA) {  // �����Ϸ�
        strcpy(res->doctorInfo.name, cache);
    }
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    retInt = IsDoctorLevel(cache); // ���ҽ������
    if (retInt == LEGAL_DATA) { // ҽ������Ϸ�
        res->doctorInfo.level = atoi(cache);
    }
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    retInt = IsConsultTime(cache); // ���ҽ������ʱ��
    if (retInt == LEGAL_DATA) { // ����ʱ��Ϸ�
        for (int i = 0; i < 7; i++)
            res->doctorInfo.consultTime[i] = cache[i] != '0' ? true : false;
    }
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    if (flag)return INVALID_DATA;
    else return LEGAL_DATA;
}

DiagnosisRecord* InRecord(FILE* fp) {  // ������߼��
    char cache[100];  // ��ʱ�洢 ���ڼ��
    int flag = 0;  // ����Ƿ��д���
    int retInt = 0; // ��¼ÿ�μ��ķ���ֵ�߼��,�������ݴ��󷵻�NULL
    DiagnosisRecord* res = (DiagnosisRecord*)malloc(sizeof(DiagnosisRecord));
    res->diagnosisSituation.diagnosisSituationInfo.
        checkRecord.checkInformationHead = NULL;
    res->diagnosisSituation.diagnosisSituationInfo.
        prescribeRecord.prescribeInformationHead = NULL;
    fscanf(fp, "%s", cache);
    while (1) {
        // ��������Ƿ���ȷ
        fscanf(fp, "%s", cache);
        retInt = IsDate(cache);
        if (retInt == LEGAL_DATA) {  // ���ںϷ�
            SetDate(cache, &res->TimeRecord.month,
                &res->TimeRecord.day,
                &res->TimeRecord.hour,
                &res->TimeRecord.minute);
        }
        else {
            flag = 1; if (retInt == FILE_END)break;
        }
        retInt = GetPatientRecord(fp, res);
        if (retInt != LEGAL_DATA) {  // ������Ϣ�Ϸ�
            flag = 1; if (retInt == FILE_END)break;
        }
        retInt = GetDoctorRecord(fp, res);
        if (retInt != LEGAL_DATA) {  // ҽ����Ϣ�Ϸ�
            flag = 1; if (retInt == FILE_END)break;
        }
        // ����������ͱ��
        fscanf(fp, "%s", cache);
        retInt = IsDiagnosisFlag(cache);
        if (retInt == LEGAL_DATA) { // �������ͱ�źϷ�
            res->diagnosisSituation.setFlag = atoi(cache);
        }
        else {
            flag = 1; if (retInt == FILE_END)break;
        }
        retInt = GetDiagnosisSituationInfo(fp, res); // ��ȡ��Ӧ���������͵���Ϣ
        if (retInt != LEGAL_DATA) {
            flag = 1; if (retInt == FILE_END)break;
        }
        fscanf(fp, "%s", cache);  // ��ȡ������
        if (!IsEnd(cache)) {  // �ü�¼��δ��ֹ,ȷ�����������,����Ӱ���¸���¼
            while (!feof(fp) && !IsEnd(cache))fscanf(fp, "%s", cache);
            flag = 1;
        }
        break;
    }
    if (flag) { // �ڴ˴�����ɾ������
        free(res);
        res = NULL;
    }
    return res;
}