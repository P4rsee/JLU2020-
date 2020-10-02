#include "Checks.h"

bool IsNumber(const char* str) { //�жϸ��ַ����Ƿ�Ϊ����
    int len = strlen(str);
    for (int i = 0; i < len; i++)
        if (str[i] > '9' || str[i] < '0')return false;
    return true;
}

bool HasDate(int month, int day) { // �ж����յ���ȷ��
    static const int m_day[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (day > m_day[month] || day < 0)return false;
    return true;
}

bool IsEnd(const char* str) {  // �Ƿ����������
    return (strcmp(str, "#") == 0) ? true : false;
}

bool IsDefault(const char* str) { // �Ƿ����ȱʡֵ
    return strcmp(str, "$") == 0 || strcmp(str, "-1") == 0 ? true : false;
}

int IsRegisterId(const char* str) {  //�ж� registerId �Ƿ�Ϸ�
    if (IsDefault(str)) {  //ȱʡֵ
        return LACKED_DATA;
    }
    else if (IsEnd(str)) {  //����ĩβֵ
        return FILE_END;
    }
    else if (!IsNumber(str) || strlen(str) != 7) { // ���ַ������ַ��򳤶ȴ���
        return INVALID_DATA;
    } // ����Ƿ����޶���Χ��
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
            return INVALID_DATA; // ���ղ���Ӧ
        }
    }
}

int IsDate(const char* str) {  //�ж������Ƿ�Ϸ�
    if (IsDefault(str)) {  //ȱʡֵ
        return LACKED_DATA;
    }
    else if (IsEnd(str)) {  //����ĩβֵ
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

int IsName(const char* str) {  //�ж������Ƿ�Ϸ� char[40] ����
    if (IsDefault(str)) {  //ȱʡֵ
        return LACKED_DATA;
    }
    else if (IsEnd(str)) {  //����ĩβֵ
        return FILE_END;
    }
    else if (strlen(str) > 40) {
        return INVALID_DATA;
    }
    else {
        return LEGAL_DATA;
    }
}

int IsAge(const char* str) {  //�ж������Ƿ�Ϸ�
    if (IsDefault(str)) {  //ȱʡֵ
        return LACKED_DATA;
    }
    else if (IsEnd(str)) {  //����ĩβֵ
        return FILE_END;
    }
    else if (!IsNumber(str) || strlen(str) > 3) {  //Age�������ֻ���Age̫��
        return INVALID_DATA;
    }
    else {
        return LEGAL_DATA;
    }
}

int IsDoctorId(const char* str) {  //���ҽ������
    if (IsDefault(str)) {  //ȱʡֵ
        return LACKED_DATA;
    }
    else if (IsEnd(str)) {  //����ĩβֵ
        return FILE_END;
    }
    else if (!IsNumber(str) || strlen(str) != 4) { // ���ų���Ŀǰ�̶�Ϊ4λ
        return INVALID_DATA;
    }
    else {
        return LEGAL_DATA;
    }
}

int IsSection(const char* str) {  //�����Һ�
    if (IsDefault(str)) {  //ȱʡֵ
        return LACKED_DATA;
    }
    else if (IsEnd(str)) {  //����ĩβֵ
        return FILE_END;
    }
    else if (!IsNumber(str) || strlen(str) != 2) { // ���Һų���Ŀǰ�̶�Ϊ4λ
        return INVALID_DATA;
    }
    else {
        return LEGAL_DATA;
    }
}

int IsDoctorLevel(const char* str) {  //���ҽ������ (һλ����)
    if (IsDefault(str)) {  //ȱʡֵ
        return LACKED_DATA;
    }
    else if (IsEnd(str)) {  //����ĩβֵ
        return FILE_END;
    }
    else if (!IsNumber(str) || strlen(str) != 1) {
        return INVALID_DATA;
    }
    else {
        return LEGAL_DATA;
    }
}

int IsConsultTime(const char* str) {  //������ʱ�� Э�飺ȱʡֵΪĬ��ȫ�����
    if (IsDefault(str)) {  //ȱʡֵ
        return LACKED_DATA;
    }
    else if (IsEnd(str)) {  //����ĩβֵ
        return FILE_END;
    }
    else if (!IsNumber(str) || strlen(str) != 7) {
        return INVALID_DATA;
    }
    else {
        return LEGAL_DATA;
    }
}

int IsDiagnosisFlag(const char* str) {  //����������ͱ��
    if (IsDefault(str)) {  //ȱʡֵ
        return LACKED_DATA;
    }
    else if (IsEnd(str)) {  //����ĩβֵ
        return FILE_END;
    }
    else if (!IsNumber(str) || strlen(str) != 1) { //�������ͱ�ų���Ϊ1
        return INVALID_DATA;
    }
    else {
        int flag = atoi(str);
        if (0 == flag || 1 == flag || 2 == flag) {  //����������֮һ
            return LEGAL_DATA;
        }
        else {
            return INVALID_DATA;
        }

    }
}

int IsDeposit(const char* str) { // ���Ѻ���Ƿ���ȷ
    if (IsDefault(str)) {  //ȱʡֵ
        return LACKED_DATA;
    }
    else if (IsEnd(str)) {  //����ĩβֵ
        return FILE_END;
    }
    else if (!IsNumber(str) || atoi(str) % 100 != 0) {
        return INVALID_DATA;
    }
    else {
        return LEGAL_DATA;
    }
}