#include "Checks.h"

bool IsNumber(const char* str) { //判断该字符串是否为数字
	int len = strlen(str);
	for (int i = 0; i < len; i++)
		if (str[i] > '9' || str[i] < '0')return false;
	return true;
}

bool HasDate(int month, int day) { // 判断月日的正确性
	static const int m_day[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (day > m_day[month] || day < 1)return false;
	return true;
}

bool IsEnd(const char* str) {  // 是否读到结束符
	return (strcmp(str, "#") == 0) ? true : false;
}

bool IsDefault(const char* str) { // 是否读到缺省值
	return strcmp(str, "$") == 0 || strcmp(str, "-1") == 0 ? true : false;
}

int IsRegisterId(const char* str) {  //判断 registerId 是否合法
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 7) { // 出现非数字字符或长度错误
		return INVALID_DATA;
	} // 检查是否在限定范围内
	else if (strcmp(str, "1231500") > 0 || strcmp(str, "0101001") < 0) {
		return INVALID_DATA;
	}
	else {
		int id = atoi(str);
		int month = id / 100000;
		int day = id / 1000 % 100;
		if (HasDate(month, day)) {
			return LEGAL_DATA;
		}
		else {
			return INVALID_DATA; // 月日不对应
		}
	}
}

int IsDate(const char* str) {  //判断日期是否合法
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 8) {
		return INVALID_DATA;
	}
	else {
		int date = atoi(str);
		int month = date / 1000000;
		int day = date / 10000 % 100;
		int hour = date % 10000 / 100;
		int minute = date % 100;
		if (!HasDate(month, day) || hour > 23 ||
			hour < 0 || minute > 59 || minute < 0) {
			return INVALID_DATA;
		}
		else {
			return LEGAL_DATA;
		}
	}
}

int IsName(const char* str) {  //判断名字是否合法 char[40] 以内
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (strlen(str) > 40) {
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsAge(const char* str) {  //判断年龄是否合法
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) > 3) {  //Age不是数字或者Age太大
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsDoctorId(const char* str) {  //检查医生工号
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 4) { // 工号长度目前固定为4位
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsSection(const char* str) {  //检查科室号
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 2) { // 科室号长度目前固定为4位
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsDoctorLevel(const char* str) {  //检查医生级别 (一位数字)
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 1) {
		return INVALID_DATA;
	}
	else {
		if (atoi(str) > 3)return INVALID_DATA;
		return LEGAL_DATA;
	}
}

int IsConsultTime(const char* str) {  //检查出诊时间 协议：缺省值为默认全天出诊
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 7) {
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsDiagnosisFlag(const char* str) {  //检查诊疗类型编号
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 1) { //诊疗类型编号长度为1
		return INVALID_DATA;
	}
	else {
		int flag = atoi(str);
		if (0 == flag || 1 == flag || 2 == flag) {  //是三种类型之一
			return LEGAL_DATA;
		}
		else {
			return INVALID_DATA;
		}

	}
}

int IsDeposit(const char* str) { // 检查押金是否正确
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else {
		char buf[100];
		int pos1 = 0, pos2 = 0;
		strcpy(buf, str);
		if (buf[0] == '-')pos1++;
		while (buf[pos2] != '.' && buf[pos2] != NULL)pos2++;
		if (buf[pos2] == '.') {
			if (strlen(buf) != pos2 + 3 || buf[pos2 + 1] != '0'
				|| buf[pos2 + 2] != '0')return INVALID_DATA;
			buf[pos2] = NULL;
		}
		if (atoi(buf + pos1) % 100 != 0) {
			return INVALID_DATA;
		}
		else {
			return LEGAL_DATA;
		}
	}
}

int IsByNowCost(const char* str) {
	if (IsDefault(str)) {  //缺省值
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {  //数据末尾值
		return FILE_END;
	}
	else {
		if (!IsNumber(str) || atoi(str) % 100 != 0) {
			return INVALID_DATA;
		}
		else {
			return LEGAL_DATA;
		}
	}
}

int IsSickBedNumber(const char* str) { // 检查病床号
	if (IsDefault(str)) {
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 4) {
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsDoctorStatus(const char* str) {
	if (IsDefault(str)) {
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 1) {
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsBusyDegree(const char* str) {
	if (IsDefault(str)) {
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 3) {
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsVacationLeft(const char* str) {
	if (IsDefault(str)) {
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 2) {
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsWardId(const char* str) {
	if (IsDefault(str)) {
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 2) {
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

int IsOneDigitNumber(const char* str) {
	if (IsDefault(str)) {
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {
		return FILE_END;
	}
	else if (!IsNumber(str) || strlen(str) != 1) {
		return INVALID_DATA;
	}
	else {
		return LEGAL_DATA;
	}
}

//bool IsInHospital(DiagnosisRecord* record) {
//	if (record->diagnosisSituation.setFlag != 2)return false;
//	TimeRecord des = record->diagnosisSituation.
//		diagnosisSituationInfo.inHospitalRecord.predictedLeaveDate;
//	if (!IsDate(buf))retuurn true;
//	/*if (des.month == -1 || des.day == -1 ||
//		des.hour == -1 || des.minute == -1)return false;*/
//	return false;
//}
bool IsInHospital(DiagnosisRecord* record) {
	if (record->diagnosisSituation.setFlag != 2)return false;
	TimeRecord des = record->diagnosisSituation.
		diagnosisSituationInfo.inHospitalRecord.leaveDate;
	char buf[100];
	sprintf(buf, "%02d%02d%02d%02d", des.month, des.day, des.hour, des.minute);
	if (!IsDate(buf))return true;
	/*if (des.month == -1 || des.day == -1 ||
		des.hour == -1 || des.minute == -1)return false;*/
	return false;
}
bool IsTimedRecord(const DiagnosisRecord* record,
	int m1, int d1, int h1, int f1, int m2, int d2, int h2, int f2) {
	const TimeRecord* tmp = &record->recordTime;
	int isFalse = 0;
	if (tmp->month<m1 || tmp->month>m2)isFalse = 1;
	if (tmp->month == m1 && tmp->day < d1)isFalse = 1;
	if (tmp->month == m2 && tmp->day > d2)isFalse = 1;
	if (tmp->month == m1 && tmp->day == d1 &&
		tmp->hour < h1)isFalse = 1;
	if (tmp->month == m2 && tmp->day == d2 &&
		tmp->hour > h2)isFalse = 1;
	if (tmp->month == m1 && tmp->day == d1 &&
		tmp->hour == h1 && tmp->minute < f1)isFalse = 1;
	if (tmp->month == m2 && tmp->day == d2 &&
		tmp->hour == h2 && tmp->minute > f2)isFalse = 1;
	if (isFalse)return false;
	else return true;
}

//2020/9/15 李增加
int IsCost(const char* str) {
	if (IsDefault(str)) {
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {
		return FILE_END;
	}
	else {
		float cost = atof(str);
		if (cost * 100 - (int)(cost * 100) > 0 || cost <= 0 ||
			(cost - 1) > 2147483647) {  //比“分”精度更大 / 花费小于0 / 超出int范围
			return INVALID_DATA;
		}
		else {
			return LEGAL_DATA;
		}
	}
}
SingleCost StrToCost(const char* str) {  //字符串转 SingleCost
	SingleCost cost;
	float temp = atof(str);
	cost.yuan = (int)temp;
	cost.jiao = ((int)(temp * 10)) % 10;
	cost.fen = ((int)(temp * 100)) % 10;
	return cost;
}

int IsDrugKindNum(const char* str) {  //判断药品种类数量，协议：一条 记录最多开 5 种药
	if (IsDefault(str)) {
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {
		return FILE_END;
	}
	else if (!IsNumber(str)) {
		return INVALID_DATA;
	}
	else {
		int num = atoi(str);
		if (num > 5 || 0 == num) {
			return INVALID_DATA;
		}
		else {
			return LEGAL_DATA;
		}
	}
}
int IsDrugId(const char* str) {  //判断药品id ，协议：药品ID为 1 - 30
	if (IsDefault(str)) {
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {
		return FILE_END;
	}
	else if (!IsNumber(str)) {
		return INVALID_DATA;
	}
	else {
		int id = atoi(str);
		if (id > 30 || 0 == id) {
			return INVALID_DATA;
		}
		else {
			return LEGAL_DATA;
		}
	}
}
int IsDrugNum(const char* str) {  //判断某种药品数量
	if (IsDefault(str)) {
		return LACKED_DATA;
	}
	else if (IsEnd(str)) {
		return FILE_END;
	}
	else if (!IsNumber(str)) {
		return INVALID_DATA;
	}
	else {
		int num = atoi(str);
		if (num > 100 || num == 0) {
			return INVALID_DATA;
		}
		else {
			return LEGAL_DATA;
		}
	}
}


void InitDiagosisRecord(DiagnosisRecord* res) {
	res->next = NULL;
	res->recordTime.day = -1;
	res->recordTime.hour = -1;
	res->recordTime.month = -1;
	res->recordTime.minute = -1;
	res->patientInfo.age = -1;
	strcpy(res->patientInfo.name, "$");
	res->patientInfo.registerId = -1;
	res->doctorInfo.id = -1;
	res->doctorInfo.level = -1;
	res->doctorInfo.sectionId = -1;
	strcpy(res->doctorInfo.name, "$");
	for (int i = 0; i < 7; i++) {
		res->doctorInfo.consultTime[i] = 1;
	}
	res->diagnosisSituation.setFlag = -1;
}