#include "InRecord.h"

// 赋值日期
void SetDate(char* str, int* month, int* day, int* hour, int* minute) {
    (*month) = atoi(str) / 1000000;
    (*day) = atoi(str) / 10000 % 100;
    (*hour) = atoi(str) % 10000 / 100;
    (*minute) = atoi(str) % 100;
}

// 用于文件读入 判断费用 若合法则赋值费用
int GetCost(FILE* fp, int* yuan, int* jiao, int* fen) { // 读入费用
    char cache[100]; int flag = 0;
    fscanf(fp, "%s", cache);
    if (IsEnd(cache)) return FILE_END;
    if (!IsNumber(cache)) flag = 1;  // 元
    else (*yuan) = atoi(cache);
    fscanf(fp, "%s", cache);
    if (IsEnd(cache)) return FILE_END;
    if (!IsNumber(cache)) flag = 1;  // 角
    else {
        (*jiao) = atoi(cache);
        if (atoi(cache) > 9) flag = 1;
    }
    fscanf(fp, "%s", cache);
    if (IsEnd(cache)) return FILE_END;
    if (!IsNumber(cache)) flag = 1;  // 分
    else {
        (*fen) = atoi(cache);
        if (atoi(cache) > 9) flag = 1;
    }
    return !flag ? LEGAL_DATA : INVALID_DATA;
}

// 获取对应的与检查有关的信息
int GetCheckInfo(FILE* fp, DiagnosisSituationUnion* tempInfo) {
    char cache[100];  // 暂时存储 用于检查
    int flag = 0; // 标记是否有错误
    int retInt = 0; // 记录每次检查的返回值
    retInt = GetCost(fp, &tempInfo->checkRecord.totalCost.yuan,
        &tempInfo->checkRecord.totalCost.jiao,
        &tempInfo->checkRecord.totalCost.fen); // 检查总费用
    if (retInt != LEGAL_DATA) {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    if (IsEnd(cache)) return FILE_END;
    int count = 0;  // 记录检查数目
    if (!IsNumber(cache)) flag = 1;
    else {
        count = atoi(cache);
        tempInfo->checkRecord.typeNumber = count;
    }
    if (tempInfo->checkRecord.checkInfoHead == NULL) {
        tempInfo->checkRecord.checkInfoHead = (CheckInfo*)malloc(sizeof(CheckInfo));
    }
    CheckInfo* nowCheck = tempInfo->checkRecord.checkInfoHead; // 当前位置指向头节点
    nowCheck->next = NULL; nowCheck->checkId = 0; 
    nowCheck->singleCost.yuan = nowCheck->singleCost.jiao = nowCheck->singleCost.fen = 0;
    int totYuan = 0, totJiao = 0, totFen = 0;
    for (int i = 0; i < count; i++) { // 录入每种检查
        CheckInfo* nextCheck = (CheckInfo*)malloc(sizeof(CheckInfo)); // 下一个节点
        fscanf(fp, "%s", cache);
        if (!IsNumber(cache)) flag = 1;
        else nextCheck->checkId = atoi(cache); // 记录检查编号
        if (IsEnd(cache)) { // 记录提前终止
            flag = FILE_END; break;
        }
        retInt = GetCost(fp, &nextCheck->singleCost.yuan,
            &nextCheck->singleCost.jiao,
            &nextCheck->singleCost.fen); // 单种检查的费用
        nowCheck->next = nextCheck;
        nowCheck = nextCheck;
        if (retInt != LEGAL_DATA) {
            flag = 1; if (retInt == FILE_END) {
                flag = FILE_END; break;  // 记录提前终止
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
    nowCheck->next = NULL; // 注意 如果检查数目超过count说明出去之后不能直接读到结束符
    if (totYuan != tempInfo->checkRecord.totalCost.yuan ||
        totJiao != tempInfo->checkRecord.totalCost.jiao ||
        totFen != tempInfo->checkRecord.totalCost.fen)flag = 1;
    if (flag) {  // 待填充 free链表 or free链表在最外层实现 或者 重复实现确保free
        if (flag == FILE_END)return FILE_END;
        else return INVALID_DATA;
    }
    else {
        return LEGAL_DATA;
    }
}

// 获取对应的与开药有关的信息
int GetPrescribeInfo(FILE* fp, DiagnosisSituationUnion* tempInfo) {
    char cache[100];  // 暂时存储 用于检查
    int flag = 0; // 标记是否有错误
    int retInt = 0; // 记录每次检查的返回值
    retInt = GetCost(fp, &tempInfo->checkRecord.totalCost.yuan,
        &tempInfo->checkRecord.totalCost.jiao,
        &tempInfo->checkRecord.totalCost.fen); // 检查总费用
    if (retInt != LEGAL_DATA) {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    if (IsEnd(cache)) return FILE_END;
    int count = 0;  // 记录开药种数
    if (!IsNumber(cache)) flag = 1;
    else {
        count = atoi(cache);
        tempInfo->prescribeRecord.typeNumber = count;
    }
    // 当前位置指向头节点
    if (tempInfo->prescribeRecord.prescribeInfoHead == NULL) {
        tempInfo->prescribeRecord.prescribeInfoHead = 
            (PrescribeInfo*)malloc(sizeof(PrescribeInfo));
    }
    PrescribeInfo* nowDrug = tempInfo->prescribeRecord.prescribeInfoHead;
    nowDrug->next = NULL; nowDrug->drugId = nowDrug->drugNumber = 0;
    for (int i = 0; i < count; i++) { // 每种药品
        PrescribeInfo* nextDrug = (PrescribeInfo*)malloc(sizeof(PrescribeInfo));  // 下一个节点
        fscanf(fp, "%s", cache);
        if (!IsNumber(cache)) flag = 1;
        else nextDrug->drugId = atoi(cache); // 记录药品编号
        if (IsEnd(cache)) {
            flag = FILE_END; break;
        }
        fscanf(fp, "%s", cache);
        if (!IsNumber(cache)) flag = 1;
        else nextDrug->drugNumber = atoi(cache); // 记录药品数量
        if (IsEnd(cache)) {
            flag = FILE_END; break;
        }
        nowDrug->next = nextDrug;
        nowDrug = nextDrug;
    }
    nowDrug->next = NULL;
    if (flag) {  // 待填充 free链表
        if (flag == FILE_END)return FILE_END;
        else return INVALID_DATA;
    }
    else {
        return LEGAL_DATA;
    }
}

// 获取对应的与住院有关的信息
int GetInHospitalInfo(FILE* fp, DiagnosisSituationUnion* tempInfo) {
    char cache[100];  // 暂时存储 用于检查
    int flag = 0; // 标记是否有错误
    int retInt = 0; // 记录每次检查的返回值
    fscanf(fp, "%s", cache);
    retInt = IsDate(cache);
    if (retInt == 1) { // 入院日期
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
    if (retInt == 1) { // 预计出院日期
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

// 从文件读入对应的诊疗类型
int GetDiagnosisSituationInfo(FILE* fp, DiagnosisRecord* res) {
    int retInt = 0; // 记录每次检查的返回值
    DiagnosisSituationUnion* tempInfo =
        &res->diagnosisSituation.diagnosisSituationInfo;
    if (res->diagnosisSituation.setFlag == 0) {  // 检查类
        retInt = GetCheckInfo(fp, tempInfo);
    }
    else if (res->diagnosisSituation.setFlag == 1) {  // 开药类
        retInt = GetPrescribeInfo(fp, tempInfo);
    }
    else if (res->diagnosisSituation.setFlag == 2) {  // 住院类
        retInt = GetInHospitalInfo(fp, tempInfo);
    }
    else retInt = INVALID_DATA;  // 诊疗类型的编号出错
    return retInt; // 标记 该处有待考虑
}

// 从文件种获取患者相关信息
int GetPatientRecord(FILE* fp, DiagnosisRecord* res) {
    char cache[100];  // 暂时存储 用于检查
    int flag = 0; // 标记是否有错误
    int retInt = 0; // 记录每次检查的返回值
    fscanf(fp, "%s", cache);
    retInt = IsRegisterId(cache); // 检查患者挂号
    if (retInt == LEGAL_DATA) res->patientInfo.registerId = atoi(cache);  // 挂号合法
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    retInt = IsName(cache); // 检查患者姓名长度是否正常 以20字(char[40])及以内为正常
    if (retInt == LEGAL_DATA) {  // 姓名合法
        strcpy(res->patientInfo.name, cache);
    }
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    retInt = IsAge(cache); // 检查患者年龄
    if (retInt == LEGAL_DATA) res->patientInfo.age = atoi(cache);  // 年龄合法
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    if (flag)return INVALID_DATA;
    else return LEGAL_DATA;
}

// 从文件中获取医生相关信息
int GetDoctorRecord(FILE* fp, DiagnosisRecord* res) {
    char cache[100];  // 暂时存储 用于检查
    int flag = 0; // 标记是否有错误
    int retInt = 0; // 记录每次检查的返回值
    fscanf(fp, "%s", cache);
    retInt = IsDoctorId(cache); // 检查医生工号
    if (retInt == LEGAL_DATA) res->doctorInfo.id = atoi(cache);  // 工号合法
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    // 检查科室
    fscanf(fp, "%s", cache);
    retInt = IsSection(cache);
    if (retInt == LEGAL_DATA) {
        res->doctorInfo.sectionId = atoi(cache); // 科室合法
    }
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    retInt = IsName(cache);  // 检查医生姓名 类似患者姓名
    if (retInt == LEGAL_DATA) {  // 姓名合法
        strcpy(res->doctorInfo.name, cache);
    }
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    retInt = IsDoctorLevel(cache); // 检查医生级别
    if (retInt == LEGAL_DATA) { // 医生级别合法
        res->doctorInfo.level = atoi(cache);
    }
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    fscanf(fp, "%s", cache);
    retInt = IsConsultTime(cache); // 检查医生出诊时间
    if (retInt == LEGAL_DATA) { // 出诊时间合法
        for (int i = 0; i < 7; i++)
            res->doctorInfo.consultTime[i] = cache[i] != '0' ? true : false;
    }
    else {
        flag = 1; if (retInt == FILE_END)return FILE_END;
    }
    if (flag)return INVALID_DATA;
    else return LEGAL_DATA;
}

DiagnosisRecord* InRecord(FILE* fp) {  // 边输入边检查
    char cache[100];  // 暂时存储 用于检查
    int flag = 0;  // 标记是否有错误
    int retInt = 0; // 记录每次检查的返回值边检查,若有数据错误返回NULL
    DiagnosisRecord* res = (DiagnosisRecord*)malloc(sizeof(DiagnosisRecord));
    res->diagnosisSituation.diagnosisSituationInfo.
        checkRecord.checkInfoHead = NULL;
    res->diagnosisSituation.diagnosisSituationInfo.
        prescribeRecord.prescribeInfoHead = NULL;
    fscanf(fp, "%s", cache);
    while (1) {
        // 检查日期是否正确
        fscanf(fp, "%s", cache);
        retInt = IsDate(cache);
        if (retInt == LEGAL_DATA) {  // 日期合法
            SetDate(cache, &res->recordTime.month,
                &res->recordTime.day,
                &res->recordTime.hour,
                &res->recordTime.minute);
        }
        else {
            flag = 1; if (retInt == FILE_END)break;
        }
        retInt = GetPatientRecord(fp, res);
        if (retInt != LEGAL_DATA) {  // 患者信息合法
            flag = 1; if (retInt == FILE_END)break;
        }
        retInt = GetDoctorRecord(fp, res);
        if (retInt != LEGAL_DATA) {  // 医生信息合法
            flag = 1; if (retInt == FILE_END)break;
        }
        // 检查诊疗类型编号
        fscanf(fp, "%s", cache);
        retInt = IsDiagnosisFlag(cache);
        if (retInt == LEGAL_DATA) { // 诊疗类型编号合法
            res->diagnosisSituation.setFlag = atoi(cache);
        }
        else {
            flag = 1; if (retInt == FILE_END)break;
        }
        retInt = GetDiagnosisSituationInfo(fp, res); // 获取相应的诊疗类型的信息
        if (retInt != LEGAL_DATA) {
            flag = 1; if (retInt == FILE_END)break;
        }
        fscanf(fp, "%s", cache);  // 读取结束符
        if (!IsEnd(cache)) {  // 该记录仍未终止,确保读完结束符,以免影响下个记录
            while (!feof(fp) && !IsEnd(cache))fscanf(fp, "%s", cache);
            flag = 1;
        }
        break;
    }
    if (flag) { // 在此处补充删除链表
        free(res);
        res = NULL;
    }
    return res;
}