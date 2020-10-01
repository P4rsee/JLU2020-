#include "Checks.h"

bool IsNumber(const char* str) { //判断该字符串是否为数字
    int len = strlen(str);
    for (int i = 0; i < len; i++)
        if (str[i] > '9' || str[i] < '0')return false;
    return true;
}

bool HasDate(int month, int day) { // 判断月日的正确性
    static const int m_day[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (day > m_day[month] || day < 0)return false;
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
    else if (!IsNumber(str) || atoi(str) % 100 != 0) {
        return INVALID_DATA;
    }
    else {
        return LEGAL_DATA;
    }
}