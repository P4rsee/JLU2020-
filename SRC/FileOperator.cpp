#include "FileOperator.h"
#include "ListOperator.h"
#include "global.h"

//char writePath[] = "out.txt";
//char readPath[] = "in.txt";
//HospitalFund hospital;
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
	if (tempInfo->checkRecord.checkInfoHead == NULL) {
		tempInfo->checkRecord.checkInfoHead = (CheckInfo*)malloc(sizeof(CheckInfo));
	}
	CheckInfo* nowCheck = tempInfo->checkRecord.checkInfoHead; // ��ǰλ��ָ��ͷ�ڵ�
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
	if (tempInfo->prescribeRecord.prescribeInfoHead == NULL) {
		tempInfo->prescribeRecord.prescribeInfoHead =
			(PrescribeInfo*)malloc(sizeof(PrescribeInfo));
	}
	PrescribeInfo* nowDrug = tempInfo->prescribeRecord.prescribeInfoHead;
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
	if (retInt == LEGAL_DATA) { // ��Ժ����
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
	if (retInt == LEGAL_DATA) { // Ԥ�Ƴ�Ժ����
		SetDate(cache, &tempInfo->inHospitalRecord.predictedLeaveDate.month,
			&tempInfo->inHospitalRecord.predictedLeaveDate.day,
			&tempInfo->inHospitalRecord.predictedLeaveDate.hour,
			&tempInfo->inHospitalRecord.predictedLeaveDate.minute);
	}
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	fscanf(fp, "%s", cache);
	retInt = IsDeposit(cache);//סԺѺ��
	if (retInt == LEGAL_DATA) {
		tempInfo->inHospitalRecord.deposit.yuan = atoi(cache);
		tempInfo->inHospitalRecord.deposit.jiao = 0;
		tempInfo->inHospitalRecord.deposit.fen = 0;
	}
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	//fscanf(fp, "%s", cache);
	//retInt = IsDate(cache);//��ȡlevelDate
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
	retInt = IsDate(cache);//��ȡlevelDate
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
	fscanf(fp, "%s", cache);//���벡���� 2+2λ
	retInt = IsSickBedNumber(cache);
	if (retInt == LEGAL_DATA) {
		tempInfo->inHospitalRecord.sickBedNumber = atoi(cache);
	}
	else {
		flag = 1; if (retInt == FILE_END)return FILE_END;
	}
	fscanf(fp, "%s", cache);//���뵱ǰ����
	retInt = IsByNowCost(cache);//��ǰ���Ѻ�Ѻ��ĸ�ʽ��һ����
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
		res->doctorInfo.sectionId = atoi(cache); // ���ҺϷ�
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
		checkRecord.checkInfoHead = NULL;
	res->diagnosisSituation.diagnosisSituationInfo.
		prescribeRecord.prescribeInfoHead = NULL;
	fscanf(fp, "%s", cache);//������ʼ��
	while (1) {
		// ��������Ƿ���ȷ
		fscanf(fp, "%s", cache);
		retInt = IsDate(cache);
		if (retInt == LEGAL_DATA) {  // ���ںϷ�
			SetDate(cache, &res->recordTime.month,
				&res->recordTime.day,
				&res->recordTime.hour,
				&res->recordTime.minute);
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

DiagnosisRecord* ReadFromDiagnosisFile(const char * readPath) {
	DiagnosisRecord* res = (DiagnosisRecord*)malloc(sizeof(DiagnosisRecord));
	res->next = NULL;
	FILE* fileReadPointer;
	if ((fileReadPointer = fopen(readPath, "r")) == NULL) {
		printf("�ļ�·������ȷ,����������!\n");
		return NULL;
	}
	while (!feof(fileReadPointer)) {
		//printf("��ʼ����\n");
		DiagnosisRecord* nowRecord = InRecord(fileReadPointer);
		//printf("�������\n");
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
	int CF = 0;//��λ�Ĵ���
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
		printf("д���ļ���ʧ��!\n"); return;
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
	fscanf(fp, "%s", cache);//������ʼ��
	while (1) {
		fscanf(fp, "%s", cache);//��������
		retInt = IsName(cache);  // ���ҽ������ ���ƻ�������
		if (retInt == LEGAL_DATA) {  // �����Ϸ�
			strcpy(res->doctorInfo.name, cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		retInt = IsDoctorLevel(cache); // ���ҽ������
		if (retInt == LEGAL_DATA) { // ҽ������Ϸ�
			res->doctorInfo.level = atoi(cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		// ������
		fscanf(fp, "%s", cache);
		retInt = IsSection(cache);
		if (retInt == LEGAL_DATA) {
			res->doctorInfo.sectionId = atoi(cache); // ���ҺϷ�
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		retInt = IsConsultTime(cache); // ���ҽ������ʱ��
		if (retInt == LEGAL_DATA) { // ����ʱ��Ϸ�
			for (int i = 0; i < 7; i++)
				res->doctorInfo.consultTime[i] = cache[i] != '0' ? true : false;
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		retInt = IsDoctorId(cache); // ���ҽ������
		if (retInt == LEGAL_DATA) res->doctorInfo.id = atoi(cache);  // ���źϷ�
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache); // ���ҽ��״̬
		retInt = IsDoctorStatus(cache);
		if (retInt == LEGAL_DATA) res->doctorInfo.doctorStatus = atoi(cache);  // ״̬�Ϸ�
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache); // ��æ�̶� 3λ��
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
		if (!IsEnd(cache)) { // ��������
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
		printf("�ļ�·������ȷ,����������!\n");
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
	// ���� ���� ����
	fprintf(fp, "# %s %d %02d ",
		node->doctorInfo.name,
		node->doctorInfo.level,
		node->doctorInfo.sectionId);
	for (int i = 0; i < 7; i++)             // д�����ʱ��
		fprintf(fp, "%d", node->doctorInfo.consultTime[i] ? 1 : 0);
	//���� ״̬ ��æ�̶�
	fprintf(fp, " %04d %d %03d %02d",
		node->doctorInfo.id,
		node->doctorInfo.doctorStatus,
		node->doctorInfo.busyDegree,
		node->doctorInfo.vacationLeft);
}

void PrintToDoctorFile(DoctorNode* head, const char* writePath) {
	FILE* fileWritePointer;
	if ((fileWritePointer = fopen(writePath, "w")) == NULL) {
		printf("д���ļ���ʧ��!\n"); return;
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
	char cache[100];  // ��ʱ�洢 ���ڼ��
	int flag = 0;  // ����Ƿ��д���
	int  retInt = 0; // ��¼ÿ�μ��ķ���ֵ�߼��,�������ݴ��󷵻�NULL
	Ward* res = (Ward*)malloc(sizeof(Ward));
	res->next = NULL;
	fscanf(fp, "%s", cache);//������ʼ��
	//printf("--%s\n", cache);
	while (1) {
		fscanf(fp, "%s", cache);
		//printf("--%s\n", cache);
		retInt = IsWardId(cache);
		if (retInt == LEGAL_DATA) { // ��������Ϸ�
			res->wardId = atoi(cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		//printf("--%s\n", cache);
		retInt = IsOneDigitNumber(cache);
		if (retInt == LEGAL_DATA) { // �������ͺϷ�
			res->nursingType = atoi(cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		//printf("--%s\n", cache);
		retInt = IsOneDigitNumber(cache);
		if (retInt == LEGAL_DATA) { // �������ͺϷ�
			res->bedType = atoi(cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		//printf("--%s\n", cache);
		retInt = IsOneDigitNumber(cache);
		if (retInt == LEGAL_DATA) { // �ܴ���
			res->totalBedNum = atoi(cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		fscanf(fp, "%s", cache);
		//printf("--%s\n", cache);
		retInt = IsOneDigitNumber(cache);
		if (retInt == LEGAL_DATA) { // ��ռ�ô���
			res->occupiedBedNum = atoi(cache);
		}
		else {
			flag = 1; if (retInt == FILE_END)break;
		}
		//printf("flag=%d\n", flag);
		fscanf(fp, "%s", cache);
		//printf("--%s\n", cache);//ռ��״̬
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
		if (!IsEnd(cache)) { // ��������
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
		printf("�ļ�·������ȷ,����������!\n");
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
	//������ �������� �������� �ܴ��� ��ռ�ô���
	fprintf(fp, "# %02d %d %d %d %d ",
		ward->wardId, ward->nursingType, ward->bedType,
		ward->totalBedNum, ward->occupiedBedNum);
	for (int i = 0; i < ward->totalBedNum; i++)
		fprintf(fp, "%d", ward->bedSituation[i] ? 1 : 0);
}

void PrintToWardFile(Ward* head, const char* writePath) {
	FILE* fileWritePointer;
	if ((fileWritePointer = fopen(writePath, "w")) == NULL) {
		printf("д���ļ���ʧ��!\n"); return;
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

void CopyRecord(DiagnosisRecord* des, DiagnosisRecord* src) { // �������Ƽ�¼�ڵ�
	int setFlag = src->diagnosisSituation.setFlag;
	*des = *src;
	des->next = NULL;
	if (setFlag == 2)return; // �����סԺ��ֱ�ӷ���
	if (setFlag == 1) { // ��ҩ��
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
	else { // �����
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
		printf("�ļ�·������ȷ,����������!\n"); return;
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
		printf("д���ļ���ʧ��!\n"); return;
	}
	fprintf(fileWritePointer, "%08d %07d", currentTime.month * 1000000 +
		currentTime.day * 10000 + currentTime.hour * 100 + currentTime.minute,
		currentID);
	fclose(fileWritePointer);
}