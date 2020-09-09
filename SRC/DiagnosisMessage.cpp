#include "DiagnosisMessage.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

bool IsNumber(char* str) { // 判断该字符串是否为数字
	int len = strlen(str);
	for (int i = 0; i < len; i++)
		if (str[i] > '9' || str[i] < '0')return false;
	return true;
}

bool HasDate(int month, int day) { // 判断月日的正确性
	static const int m_day[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	if (day > m_day[month] || day < 0)return false;
	return true;
}

bool IsEnd(char *str) { // 是否读到结束符
	return strcmp(str,";") == 0 ? true : false;
}

DiagnosisRecord* InRecord(FILE* fp) { //边输入边检查,若有数据错误返回NULL
	char cache[100]; // 暂时存储 用于检查
	int flag = 0; // 标记是否有错误
	DiagnosisRecord* res = (DiagnosisRecord*)malloc(sizeof(DiagnosisRecord));
	// 检查患者挂号
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) { flag = 1; goto END; }
	if (!IsNumber(cache) || strlen(cache) != 7) flag = 1; // 出现非数字字符或长度错误
	else res->patientInformation.registerId = atoi(cache); // 判断是否在限定范围之内
	if (res->patientInformation.registerId > 1231500 || res->patientInformation.registerId < 0101001) flag = 1;
	if (!HasDate(res->patientInformation.registerId / 100000, res->patientInformation.registerId / 1000 % 100)) flag = 1;
	// 检查日期是否正确
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) { flag = 1; goto END; }
	if (!IsNumber(cache) || strlen(cache) != 8) flag = 1; // 出现非数字字符或长度错误
	else {
		res->recordTime.month = atoi(cache) / 1000000;
		res->recordTime.day = atoi(cache) / 10000 % 100;
		if (!HasDate(res->recordTime.month, res->recordTime.day)) flag = 1; // 月日不对应
		res->recordTime.hour = atoi(cache) / 100 % 100;
		res->recordTime.minute = atoi(cache) % 100;
		if (res->recordTime.hour > 23 || res->recordTime.minute > 59) flag = 1; // 不合时间规范
	}
	// 检查患者姓名长度是否正常 以20字(char[40])及以内为正常
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) { flag = 1; goto END; }
	if (strlen(cache) > 40) flag = 1;
	else strcpy(res->patientInformation.name, cache);
	// 检查患者年龄
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) { flag = 1; goto END; }
	if (!IsNumber(cache) || strlen(cache) > 3) flag = 1; // 非数字或年龄位数不正常
	else res->patientInformation.age = atoi(cache);
	// 检查医生工号
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) { flag = 1; goto END; }
	if (!IsNumber || strlen(cache) != 4) flag = 1; // 非数字或工号位数不正确
	else res->doctorinformation.id = atoi(cache);
	// 检查科室
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) { flag = 1; goto END; }
	if (!IsNumber(cache) || strlen(cache) != 4) flag = 1; // 非数字或科室号不正确
	else res->doctorinformation.section = atoi(cache);
	// 检查医生姓名 类似患者姓名
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) { flag = 1; goto END; }
	if (strlen(cache) > 40) flag = 1;
	else strcpy(res->doctorinformation.name, cache);
	// 检查医生级别
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) { flag = 1; goto END; }
	if (!IsNumber(cache) || strlen(cache) != 1) flag = 1;
	else res->doctorinformation.level = atoi(cache);
	// 检查医生出诊时间
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) { flag = 1; goto END; }
	if (!IsNumber(cache) || strlen(cache) != 7) flag = 1;
	for (int i = 0; i < 7; i++)
		res->doctorinformation.consultTime[i] = cache[i] != '0' ? true : false;
	// 检查诊疗类型编号
	fscanf(fp, "%s", cache);
	if (IsEnd(cache)) { flag = 1; goto END; }
	if (!IsNumber(cache) || strlen(cache) != 1) flag = 1;
	else res->diagnosisSituation.setFlag = atoi(cache);
	// 三种诊疗类型
	if (res->diagnosisSituation.setFlag == 0) { // 检查类
		fscanf(fp, "%s", cache); // 检查总费用
		if (IsEnd(cache)) { flag = 1; goto END; }
		if (!IsNumber(cache)) flag = 1; // 元
		else res->diagnosisSituation.diagnosisSituationInformation.checkRecord.totalCost.yuan = atoi(cache);
		fscanf(fp, "%s", cache);
		if (IsEnd(cache)) { flag = 1; goto END; }
		if (!IsNumber(cache)) flag = 1; // 角
		else {
			res->diagnosisSituation.diagnosisSituationInformation.checkRecord.totalCost.jiao = atoi(cache);
			if (atoi(cache) > 9) flag = 1;
		}
		fscanf(fp, "%s", cache);
		if (IsEnd(cache)) { flag = 1; goto END; }
		if (!IsNumber(cache)) flag = 1; // 分
		else {
			res->diagnosisSituation.diagnosisSituationInformation.checkRecord.totalCost.fen = atoi(cache);
			if (atoi(cache) > 9) flag = 1;
		}
		fscanf(fp, "%s", cache);
		if (IsEnd(cache)) { flag = 1; goto END; }
		int count = 0; // 记录检查数目
		if (!IsNumber(cache)) flag = 1;
		else {
			count = atoi(cache);
			res->diagnosisSituation.diagnosisSituationInformation.checkRecord.typeNumber = count;
		}
		// 录入每种检查
		fscanf(fp, "%s", cache);
		// 当前位置指向头节点
		CheckInformation* nowCheck = res->diagnosisSituation.diagnosisSituationInformation.checkRecord.checkInformationHead;
		while (!IsEnd(cache)) {
			CheckInformation* nextCheck = (CheckInformation*)malloc(sizeof(CheckInformation)); // 下一个节点
			if (!IsNumber(cache)) flag = 1;
			nowCheck->next = nextCheck;
			nowCheck = nextCheck;
			if (!IsNumber(cache)) flag = 1; // 元
			else nextCheck->singleCost.yuan = atoi(cache);
			fscanf(fp, "%s", cache);
			if (IsEnd(cache)) break;
			if (!IsNumber(cache)) flag = 1; // 角
			else {
				nextCheck->singleCost.jiao = atoi(cache);
				if (atoi(cache) > 9) flag = 1;
			}
			fscanf(fp, "%s", cache);
			if (IsEnd(cache)) break;
			if (!IsNumber(cache)) flag = 1; // 分
			else {
				nextCheck->singleCost.fen = atoi(cache);
				if (atoi(cache) > 9) flag = 1;
			}
			count--;
		}
		nowCheck->next = NULL;
		if (count != 0) flag = 1;// 待填充 free链表
	}
	else if (res->diagnosisSituation.setFlag == 1) { // 开药类
		int dCount = 0; // 记录开药种数
		if (!IsNumber(cache)) flag = 1;
		else {
			dCount = atoi(cache);
			res->diagnosisSituation.diagnosisSituationInformation.prescribeRecord.typeNumber = dCount;
		}
		//每种药品
		fscanf(fp, "%s", cache);
		// 当前位置指向头节点
		PrescribeInformation* nowDrug = res->diagnosisSituation.diagnosisSituationInformation.prescribeRecord.prescribeInformationHead;
		while (!IsEnd(cache)) {
			PrescribeInformation* nextDrug = (PrescribeInformation*)malloc(sizeof(PrescribeInformation)); // 下一个节点
			nowDrug->next = nextDrug;
			nowDrug = nextDrug;
			if (!IsNumber(cache)) flag = 1;
			else nextDrug->drugId = atoi(cache);
			fscanf(fp, "%s", cache);
			if (IsEnd(cache)) break;
			if (!IsNumber(cache)) flag = 1;
			else nextDrug->drugNumber = atoi(cache);
			dCount--;
		}
		nowDrug->next = NULL;
		if (dCount != 0) flag = 1;// 待填充 free链表
	}
	else if (res->diagnosisSituation.setFlag == 2) { // 住院类
		//入院日期
		fscanf(fp, "%s", cache);
		if (IsEnd(cache)) { flag = 1; goto END; }
		if (!IsNumber(cache) || strlen(cache) != 8) flag = 1; // 出现非数字字符或长度错误
		else {
			res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.month = atoi(cache) / 1000000;
			res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.day = atoi(cache) / 10000 % 100;
			if (!HasDate(res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.month,
				res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.day)) flag = 1; // 月日不对应
			res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.hour = atoi(cache) / 100 % 100;
			res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.minute = atoi(cache) % 100;
			if (res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.hour > 23 ||
				res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.minute > 59) flag = 1; // 不合时间规范
		}
		//预计出院日期
		fscanf(fp, "%s", cache);
		if (IsEnd(cache)) { flag = 1; goto END; }
		if (!IsNumber(cache) || strlen(cache) != 8) flag = 1; // 出现非数字字符或长度错误
		else {
			res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.predictedLeaveDate.month = atoi(cache) / 1000000;
			res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.day = atoi(cache) / 10000 % 100;
			if (!HasDate(res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.predictedLeaveDate.month,
				res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.day)) flag = 1; // 月日不对应
			res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.predictedLeaveDate.hour = atoi(cache) / 100 % 100;
			res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.predictedLeaveDate.minute = atoi(cache) % 100;
			if (res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.predictedLeaveDate.hour > 23 ||
				res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.predictedLeaveDate.minute > 59) flag = 1; // 不合时间规范
		}
		fscanf(fp, "%s", cache);
		if (IsEnd(cache)) { flag = 1; goto END; }
		if (!IsNumber(cache)) flag = 1;
		else {
			res->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.deposit.yuan = atoi(cache);
			if (atoi(cache) % 100 != 0) flag = 1; // 不是一百的整数
		}
	}
	else flag = 1; // 诊疗类型的编号出错
	fscanf(fp, "%s", cache); // 读取结束符
	if (!IsEnd(cache)) { // 该记录仍未终止
		while (!feof(fp) && !IsEnd(cache))fscanf(fp, "%s", cache);
		flag = 1;
	}
END:
	if (flag) {
		free(res); 
		res = NULL;
	}
	return res;
}

void FileInput() { // 从文件导入诊疗记录
	char writePath[] = "out.txt";
	char readPath[100];
	scanf("%s", readPath);
	FILE* fileReadPointer, * fileWritePointer;
	while ((fileReadPointer = fopen(readPath, "r")) == NULL) {
		printf("文件路径不正确,请重新输入!\n");
		scanf("%s", readPath);
	}
	fileWritePointer = fopen(writePath, "w+");
	while (!feof(fileReadPointer)) {
		DiagnosisRecord* nowRecord = InRecord(fileReadPointer);
		if (!nowRecord)continue;
								 // 挂号      日期    姓名 年龄 工号 科室 姓名 级别
 		fprintf(fileWritePointer, "%08d %02d%02d%02d%02d %s %d %04d %02d %s %d ", 
			nowRecord->patientInformation.registerId,
			nowRecord->recordTime.month, 
			nowRecord->recordTime.day,
			nowRecord->recordTime.hour,
			nowRecord->recordTime.minute,
			nowRecord->patientInformation.name,
			nowRecord->patientInformation.age,
			nowRecord->doctorinformation.id,
			nowRecord->doctorinformation.section,
			nowRecord->doctorinformation.name,
			nowRecord->doctorinformation.level
		);
		for (int i = 0; i < 7; i++)
			fprintf(fileWritePointer, "%d", nowRecord->doctorinformation.consultTime[i] ? 1 : 0); // 写入出诊时间的二进制码
		fprintf(fileWritePointer, " %d ", nowRecord->diagnosisSituation.setFlag); // 写入诊疗类型编号
		if (nowRecord->diagnosisSituation.setFlag == 0) { // 检查类
			CheckInformation* nowPos = nowRecord->diagnosisSituation.diagnosisSituationInformation.checkRecord.checkInformationHead;
			fprintf(fileWritePointer, "%d %d", nowRecord->diagnosisSituation.diagnosisSituationInformation.checkRecord.totalCost);
			for (int i = 0; i < nowRecord->diagnosisSituation.diagnosisSituationInformation.checkRecord.typeNumber; i++) {
				nowPos = nowPos->next;
				fprintf(fileWritePointer, " %d %d %d %d",
					nowPos->checkId, nowPos->singleCost.yuan, nowPos->singleCost.jiao, nowPos->singleCost.fen);
			}
		}
		else if (nowRecord->diagnosisSituation.setFlag == 1) { // 开药类
			PrescribeInformation* nowPos = nowRecord->diagnosisSituation.diagnosisSituationInformation.prescribeRecord.prescribeInformationHead;
			fprintf(fileWritePointer, "%d %d %d %d",
				nowRecord->diagnosisSituation.diagnosisSituationInformation.prescribeRecord.totalCost.yuan,
				nowRecord->diagnosisSituation.diagnosisSituationInformation.prescribeRecord.totalCost.jiao,
				nowRecord->diagnosisSituation.diagnosisSituationInformation.prescribeRecord.totalCost.fen,
				nowRecord->diagnosisSituation.diagnosisSituationInformation.prescribeRecord.typeNumber
			);
			for (int i = 0; i < nowRecord->diagnosisSituation.diagnosisSituationInformation.prescribeRecord.typeNumber; i++) {
				nowPos = nowPos->next;
				fprintf(fileWritePointer, " %d %d", nowPos->drugId, nowPos->drugNumber);
			}
		}
		else if (nowRecord->diagnosisSituation.setFlag == 2) { // 住院类
			fprintf(fileWritePointer, "%02d%02d%02d%02d %02d%02d%02d%02d %d",
				nowRecord->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.month,
				nowRecord->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.day,
				nowRecord->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.hour,
				nowRecord->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.hospitalizedDate.minute,
				nowRecord->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.predictedLeaveDate.month,
				nowRecord->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.predictedLeaveDate.day,
				nowRecord->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.predictedLeaveDate.hour,
				nowRecord->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.predictedLeaveDate.minute,
				nowRecord->diagnosisSituation.diagnosisSituationInformation.inHospitalRecord.deposit.yuan
			);
		}
		fprintf(fileWritePointer, ";\n");
	}
	return;
}
