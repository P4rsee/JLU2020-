#include "FileOperator.h"
#include "ListOperator.h"
#include "global.h"

//char writePath[] = "out.txt";
//char readPath[] = "in.txt";
//HospitalFund hospital;
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
	if (retInt == LEGAL_DATA) { // 入院日期
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
	if (retInt == LEGAL_DATA) { // 预计出院日期
		SetDate(cache, &tempInfo->inHospitalRecord.predictedLeaveDate.month,
			&tempInfo->inHospitalRecord.predictedLeaveDate.day,
			&tempInfo->inHospitalRecord.predictedLeaveDate.hour,
			&tempInfo->inHospitalRecord.predictedLeaveDate.minute);
	}
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	fscanf(fp, "%s", cache);
	retInt = IsDeposit(cache);//住院押金
	if (retInt == LEGAL_DATA) {
		tempInfo->inHospitalRecord.deposit.yuan = atoi(cache);
		tempInfo->inHospitalRecord.deposit.jiao = 0;
		tempInfo->inHospitalRecord.deposit.fen = 0;
	}
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	//fscanf(fp, "%s", cache);
	//retInt = IsDate(cache);//读取levelDate
	//if (retInt == LEGAL_DATA) {
	//	SetDate(cache, &tempInfo->inHospitalRecord.leaveDate.month,
	//		&tempInfo->inHospitalRecord.leaveDate.day,
	//		&tempInfo->inHospitalRecord.leaveDate.hour,
	//		&tempInfo->inHospitalRecord.leaveDate.minute);
	//}
	//else {
	//	flag = 1; if (retInt == FILE_END)return FILE_END;
	//}
	fscanf(fp, "%s", cache);
	retInt = IsDate(cache);//读取levelDate
	if (IsNumber(cache))retInt = LEGAL_DATA;
	if (retInt == LEGAL_DATA) {
		SetDate(cache, &tempInfo->inHospitalRecord.leaveDate.month,
			&tempInfo->inHospitalRecord.leaveDate.day,
			&tempInfo->inHospitalRecord.leaveDate.hour,
			&tempInfo->inHospitalRecord.leaveDate.minute);
	}
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	fscanf(fp, "%s", cache);//读入病床号 2+2位
	retInt = IsSickBedNumber(cache);
	if (retInt == LEGAL_DATA) {
		tempInfo->inHospitalRecord.sickBedNumber = atoi(cache);
	}
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	fscanf(fp, "%s", cache);//读入当前花费
	retInt = IsByNowCost(cache);//当前花费和押金的格式是一样的
	if (retInt == LEGAL_DATA) {
		tempInfo->inHospitalRecord.costByNow.yuan = atoi(cache);
		tempInfo->inHospitalRecord.costByNow.jiao = 0;
		tempInfo->inHospitalRecord.costByNow.fen = 0;
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
	fscanf(fp, "%s", cache);//读入起始符
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
		freeDiagnosisRecord(res);
		res = NULL;
	}
	return res;
}

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

// 输出开药类型到诊疗记录中
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

// 输出住院类型到诊疗记录中
void OutInHospitalRecord(FILE* fp, DiagnosisSituationUnion* tempInfo) {
	fprintf(fp, "%02d%02d%02d%02d %02d%02d%02d%02d %d %02d%02d%02d%02d %04d %d",
		tempInfo->inHospitalRecord.hospitalizedDate.month,
		tempInfo->inHospitalRecord.hospitalizedDate.day,
		tempInfo->inHospitalRecord.hospitalizedDate.hour,
		tempInfo->inHospitalRecord.hospitalizedDate.minute,
		tempInfo->inHospitalRecord.predictedLeaveDate.month,
		tempInfo->inHospitalRecord.predictedLeaveDate.day,
		tempInfo->inHospitalRecord.predictedLeaveDate.hour,
		tempInfo->inHospitalRecord.predictedLeaveDate.minute,
		tempInfo->inHospitalRecord.deposit.yuan,
		tempInfo->inHospitalRecord.leaveDate.month,
		tempInfo->inHospitalRecord.leaveDate.day,
		tempInfo->inHospitalRecord.leaveDate.hour,
		tempInfo->inHospitalRecord.leaveDate.minute,
		tempInfo->inHospitalRecord.sickBedNumber,
		tempInfo->inHospitalRecord.costByNow
	);
}

// 输出数据到诊疗记录中
void OutRecord(FILE* fp, DiagnosisRecord* record) {
	//                           日期       挂号 姓名 年龄 工号 科室 姓名 级别
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

DiagnosisRecord* ReadFromDiagnosisFile(const char * readPath) {
	DiagnosisRecord* res = (DiagnosisRecord*)malloc(sizeof(DiagnosisRecord));
	res->next = NULL;
	FILE* fileReadPointer;
	if ((fileReadPointer = fopen(readPath, "r")) == NULL) {
		printf("文件路径不正确,请重新输入!\n");
		return NULL;
	}
	while (!feof(fileReadPointer)) {
		//printf("开始读入\n");
		DiagnosisRecord* nowRecord = InRecord(fileReadPointer);
		//printf("读入结束\n");
		if (!nowRecord) continue;
		pushBackDiagnosisList(res, nowRecord);
		if (nowRecord->diagnosisSituation.setFlag == 0) {
			hospitalFund.checkCost.yuan += nowRecord->diagnosisSituation.
				diagnosisSituationInfo.checkRecord.totalCost.yuan;
			hospitalFund.checkCost.jiao += nowRecord->diagnosisSituation.
				diagnosisSituationInfo.checkRecord.totalCost.jiao;
			hospitalFund.checkCost.fen += nowRecord->diagnosisSituation.
				diagnosisSituationInfo.checkRecord.totalCost.fen;
		}
		else if (nowRecord->diagnosisSituation.setFlag == 1) {
			hospitalFund.drugCost.yuan += nowRecord->diagnosisSituation.
				diagnosisSituationInfo.prescribeRecord.totalCost.yuan;
			hospitalFund.drugCost.jiao += nowRecord->diagnosisSituation.
				diagnosisSituationInfo.prescribeRecord.totalCost.jiao;
			hospitalFund.drugCost.fen += nowRecord->diagnosisSituation.
				diagnosisSituationInfo.prescribeRecord.totalCost.fen;
		}
		else if (nowRecord->diagnosisSituation.setFlag == 2) {
			hospitalFund.inHosipitalCost.yuan += nowRecord->diagnosisSituation.
				diagnosisSituationInfo.inHospitalRecord.costByNow.yuan;
			hospitalFund.inHosipitalCost.jiao += nowRecord->diagnosisSituation.
				diagnosisSituationInfo.inHospitalRecord.costByNow.jiao;
			hospitalFund.inHosipitalCost.fen += nowRecord->diagnosisSituation.
				diagnosisSituationInfo.inHospitalRecord.costByNow.fen;
		}
	}
	int CF = 0;//进位寄存器
	hospitalFund.allCost.fen += hospitalFund.checkCost.fen +
		hospitalFund.drugCost.fen + hospitalFund.inHosipitalCost.fen;
	CF = hospitalFund.allCost.fen / 10; hospitalFund.allCost.fen %= 10;
	hospitalFund.allCost.jiao += hospitalFund.checkCost.jiao +
		hospitalFund.drugCost.jiao + hospitalFund.inHosipitalCost.jiao + CF;
	CF = hospitalFund.allCost.jiao / 10; hospitalFund.allCost.jiao %= 10;
	hospitalFund.allCost.yuan += hospitalFund.checkCost.yuan +
		hospitalFund.drugCost.yuan + hospitalFund.inHosipitalCost.yuan + CF;
	fclose(fileReadPointer);
	return res;
}

void PrintToDiagnosisFile(DiagnosisRecord* head, const char* writePath) {
	FILE* fileWritePointer;
	if ((fileWritePointer = fopen(writePath, "w")) == NULL) {
		printf("写入文件打开失败!\n"); return;
	}
	DiagnosisRecord* p = head->next;
	while (p != NULL) {
		//printf("%s\n", p->patientInfo.name);
		OutRecord(fileWritePointer, p);
		p = p->next;
	}
	fclose(fileWritePointer);
}

DoctorNode* GetSingleDoctorNode(FILE* fp) {
	DoctorNode* res = (DoctorNode*)malloc(sizeof(DoctorInfo));
	char cache[100];
	int retInt = 0, flag = 0;
	fscanf(fp, "%s", cache);//读入起始符
	while (1) {
		fscanf(fp, "%s", cache);//读入姓名
		retInt = IsName(cache);  // 检查医生姓名 类似患者姓名
		if (retInt == LEGAL_DATA) {  // 姓名合法
			strcpy(res->doctorInfo.name, cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		retInt = IsDoctorLevel(cache); // 检查医生级别
		if (retInt == LEGAL_DATA) { // 医生级别合法
			res->doctorInfo.level = atoi(cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		// 检查科室
		fscanf(fp, "%s", cache);
		retInt = IsSection(cache);
		if (retInt == LEGAL_DATA) {
			res->doctorInfo.sectionId = atoi(cache); // 科室合法
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		retInt = IsConsultTime(cache); // 检查医生出诊时间
		if (retInt == LEGAL_DATA) { // 出诊时间合法
			for (int i = 0; i < 7; i++)
				res->doctorInfo.consultTime[i] = cache[i] != '0' ? true : false;
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		retInt = IsDoctorId(cache); // 检查医生工号
		if (retInt == LEGAL_DATA) res->doctorInfo.id = atoi(cache);  // 工号合法
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache); // 检查医生状态
		retInt = IsDoctorStatus(cache);
		if (retInt == LEGAL_DATA) res->doctorInfo.doctorStatus = atoi(cache);  // 状态合法
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache); // 繁忙程度 3位数
		retInt = IsBusyDegree(cache);
		if (retInt == LEGAL_DATA) res->doctorInfo.busyDegree = atoi(cache);
		else {
			flag = 1; if (retInt == FILE_END) break;
		}
		fscanf(fp, "%s", cache);
		retInt = IsVacationLeft(cache);
		if (retInt == LEGAL_DATA) res->doctorInfo.vacationLeft = atoi(cache);
		else {
			flag = 1; if (retInt == FILE_END) break;
		}
		fscanf(fp, "%s", cache);
		if (!IsEnd(cache)) { // 读结束符
			flag = 1; while (!IsEnd(cache))fscanf(fp, "%s", cache);
		}
		break;
	}
	if (flag) {
		free(res);
		res = NULL;
	}
	return res;
}

DoctorNode* ReadFromDoctorFile(const char* readPath) {
	DoctorNode* res = (DoctorNode*)malloc(sizeof(DoctorNode));
	res->next = NULL;
	FILE* fileReadPointer;
	if ((fileReadPointer = fopen(readPath, "r")) == NULL) {
		printf("文件路径不正确,请重新输入!\n");
		return NULL;
	}
	while (!feof(fileReadPointer)) {
		DoctorNode* nowNode = GetSingleDoctorNode(fileReadPointer);
		if (!nowNode) continue;
		pushBackDoctorList(res, nowNode);
	}
	fclose(fileReadPointer);
	return res;
}

void OutDoctorNode(FILE* fp, DoctorNode* node) {
	// 姓名 级别 科室
	fprintf(fp, "# %s %d %02d ",
		node->doctorInfo.name,
		node->doctorInfo.level,
		node->doctorInfo.sectionId);
	for (int i = 0; i < 7; i++)             // 写入出诊时间
		fprintf(fp, "%d", node->doctorInfo.consultTime[i] ? 1 : 0);
	//工号 状态 繁忙程度
	fprintf(fp, " %04d %d %03d %02d",
		node->doctorInfo.id,
		node->doctorInfo.doctorStatus,
		node->doctorInfo.busyDegree,
		node->doctorInfo.vacationLeft);
}

void PrintToDoctorFile(DoctorNode* head, const char* writePath) {
	FILE* fileWritePointer;
	if ((fileWritePointer = fopen(writePath, "w")) == NULL) {
		printf("写入文件打开失败!\n"); return;
	}
	DoctorNode* p = head->next;
	while (p != NULL) {
		if (p->doctorInfo.doctorStatus == 2){
			p = p->next;
			continue;
		}
		OutDoctorNode(fileWritePointer, p);
		fprintf(fileWritePointer, " #");
		if (p->next != NULL)fprintf(fileWritePointer, "\n");
		p = p->next;
	}
	fclose(fileWritePointer);
}

Ward* GetSingleWard(FILE* fp) {
	char cache[100];  // 暂时存储 用于检查
	int flag = 0;  // 标记是否有错误
	int  retInt = 0; // 记录每次检查的返回值边检查,若有数据错误返回NULL
	Ward* res = (Ward*)malloc(sizeof(Ward));
	res->next = NULL;
	fscanf(fp, "%s", cache);//读入起始符
	//printf("--%s\n", cache);
	while (1) {
		fscanf(fp, "%s", cache);
		//printf("--%s\n", cache);
		retInt = IsWardId(cache);
		if (retInt == LEGAL_DATA) { // 病房号码合法
			res->wardId = atoi(cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		//printf("--%s\n", cache);
		retInt = IsOneDigitNumber(cache);
		if (retInt == LEGAL_DATA) { // 护理类型合法
			res->nursingType = atoi(cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		//printf("--%s\n", cache);
		retInt = IsOneDigitNumber(cache);
		if (retInt == LEGAL_DATA) { // 病床类型合法
			res->bedType = atoi(cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		//printf("--%s\n", cache);
		retInt = IsOneDigitNumber(cache);
		if (retInt == LEGAL_DATA) { // 总床数
			res->totalBedNum = atoi(cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		//printf("--%s\n", cache);
		retInt = IsOneDigitNumber(cache);
		if (retInt == LEGAL_DATA) { // 被占用床数
			res->occupiedBedNum = atoi(cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		//printf("flag=%d\n", flag);
		fscanf(fp, "%s", cache);
		//printf("--%s\n", cache);//占用状态
		if (IsNumber(cache)) {
			for (int i = 0; i < strlen(cache); i++) {
				res->bedSituation[i] = cache[i] - '0';
				if (cache[i] - '0' > 1 || cache[i] - '0' < 0)flag = 1;
			}
		}
		else {
			flag = 1; if (IsEnd(cache))break;
		}
		fscanf(fp, "%s", cache);
		//printf("--%s\n", cache);
		if (!IsEnd(cache)) { // 读结束符
			flag = 1; while (!IsEnd(cache))fscanf(fp, "%s", cache);
		}
		break;
	}
	if (flag) {
		free(res); res = NULL;
	}
	return res;
}

Ward* ReadFromWardFile(const char* readPath) {
	Ward* res = (Ward*)malloc(sizeof(Ward));
	res->next = NULL;
	FILE* fileReadPointer;
	if ((fileReadPointer = fopen(readPath, "r")) == NULL) {
		printf("文件路径不正确,请重新输入!\n");
		return NULL;
	}
	while (!feof(fileReadPointer)) {
		Ward* nowWard = GetSingleWard(fileReadPointer);
		if (!nowWard) continue;
		pushbackWard(res, nowWard);
	}
	fclose(fileReadPointer);
	return res;
}

void OutWard(FILE* fp, Ward* ward) {
	//病房号 护理类型 床的类型 总床数 被占用床数
	fprintf(fp, "# %02d %d %d %d %d ",
		ward->wardId, ward->nursingType, ward->bedType,
		ward->totalBedNum, ward->occupiedBedNum);
	for (int i = 0; i < ward->totalBedNum; i++)
		fprintf(fp, "%d", ward->bedSituation[i] ? 1 : 0);
}

void PrintToWardFile(Ward* head, const char* writePath) {
	FILE* fileWritePointer;
	if ((fileWritePointer = fopen(writePath, "w")) == NULL) {
		printf("写入文件打开失败!\n"); return;
	}
	Ward* p = head->next;
	while (p != NULL) {
		OutWard(fileWritePointer, p);
		fprintf(fileWritePointer, " #");
		if (p->next != NULL)fprintf(fileWritePointer, "\n");
		p = p->next;
	}
	fclose(fileWritePointer);
}

void CopyRecord(DiagnosisRecord* des, DiagnosisRecord* src) { // 拷贝诊疗记录节点
	int setFlag = src->diagnosisSituation.setFlag;
	*des = *src;
	des->next = NULL;
	if (setFlag == 2)return; // 如果是住院类直接返回
	if (setFlag == 1) { // 开药类
		PrescribeInfo* desInfo = des->diagnosisSituation.diagnosisSituationInfo.
			prescribeRecord.prescribeInfoHead = (PrescribeInfo*)malloc(sizeof(PrescribeInfo));
		PrescribeInfo* srcInfo = src->diagnosisSituation.diagnosisSituationInfo.
			prescribeRecord.prescribeInfoHead->next;
		while (srcInfo != NULL) {
			desInfo->next = NULL;
			desInfo->next = (PrescribeInfo*)malloc(sizeof(PrescribeInfo));
			*desInfo->next = *srcInfo;
			desInfo = desInfo->next;
			srcInfo = srcInfo->next;
		}
		desInfo->next = NULL;
	}
	else { // 检查类
		CheckInfo* desInfo = des->diagnosisSituation.diagnosisSituationInfo.
			checkRecord.checkInfoHead = (CheckInfo*)malloc(sizeof(CheckInfo));
		CheckInfo* srcInfo = src->diagnosisSituation.diagnosisSituationInfo.
			checkRecord.checkInfoHead->next;
		while (srcInfo != NULL) {
			desInfo->next = NULL;
			desInfo->next = (CheckInfo*)malloc(sizeof(CheckInfo));
			*desInfo->next = *srcInfo;
			desInfo = desInfo->next;
			srcInfo = srcInfo->next;
		}
		desInfo->next = NULL;
	}
}

void splitByInHospital(DiagnosisRecord* totHead,
	DiagnosisRecord* inHosiptalHead, DiagnosisRecord* othersHead) {
	DiagnosisRecord* nowRecord = totHead->next;
	inHosiptalHead->next = NULL, othersHead->next = NULL;
	while (nowRecord != NULL) {
		DiagnosisRecord* tempRecord = (DiagnosisRecord*)malloc(sizeof(DiagnosisRecord));
		CopyRecord(tempRecord, nowRecord); tempRecord->next = NULL;
		if (IsInHospital(tempRecord)) {
			pushBackDiagnosisList(inHosiptalHead, tempRecord);
		}
		else {
			pushBackDiagnosisList(othersHead, tempRecord);
		}
		nowRecord = nowRecord->next;
	}
}

void initCurrentFromFile(const char* readPath) {
	FILE* fileReadPointer;
	if ((fileReadPointer = fopen(readPath, "r")) == NULL) {
		printf("文件路径不正确,请重新输入!\n"); return;
	}
	char buf_time[100], buf_id[100];
	fscanf(fileReadPointer, "%s %s", buf_time, buf_id);
	currentID = atoi(buf_id);
	int time = atoi(buf_time);
	currentTime.month = time / 1000000;
	currentTime.day = time / 10000 % 100;
	currentTime.hour = time % 10000 / 100;
	currentTime.minute = time % 100;
	fclose(fileReadPointer);
}

void saveCurrentToFile(const char* writePath) {
	FILE* fileWritePointer;
	if ((fileWritePointer = fopen(writePath, "w")) == NULL) {
		printf("写入文件打开失败!\n"); return;
	}
	fprintf(fileWritePointer, "%08d %07d", currentTime.month * 1000000 +
		currentTime.day * 10000 + currentTime.hour * 100 + currentTime.minute,
		currentID);
	fclose(fileWritePointer);
}