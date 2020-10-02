#include "InRecord.h"
#include "Checks.h"
#include <stdio.h>
                                                                                
void PrintTimedRecord(int m1, int d1, int h1, int f1, int m2, int d2, int h2, int f2) {
    FILE* fp = fopen("in.txt", "r");
    if (fp == NULL) {
        printf("��ʧ��!\n");
    }
    while (!feof(fp)) {
        DiagnosisRecord* nowRecord = InRecord(fp);
        TimeRecord* tmp = &nowRecord->recordTime;
        if (tmp->month<m1 || tmp->month>m2)continue;
        if (tmp->month == m1 && tmp->day < d1)continue;
        if (tmp->month == m2 && tmp->day > d2)continue;
        if (tmp->month == m1 && tmp->day == d1 &&
            tmp->hour < h1)continue;
        if (tmp->month == m2 && tmp->day == d2 &&
            tmp->hour > h2)continue;
        if (tmp->month == m1 && tmp->day == d1 &&
            tmp->hour == h1 && tmp->minute < f1)continue;
        if (tmp->month == m2 && tmp->day == d2 &&
            tmp->hour == h2 && tmp->minute > f2)continue;
        //�����������
    }
    //������������
}


int IsWardId(const char* str) {
    return 1;
}

int IsNursingType(const char* str) {
    return 1;
}

int IsBedType(const char* str) {
    return 1;
}

Ward* InWard(FILE* fp) {
    char cache[100];  // ��ʱ�洢 ���ڼ��
    int flag = 0;  // ����Ƿ��д���
    int  retInt = 0; // ��¼ÿ�μ��ķ���ֵ�߼��,�������ݴ��󷵻�NULL
    Ward* res = (Ward*)malloc(sizeof(Ward));
    res->next = NULL;
    while (1) {
        fscanf(fp, "%s", cache);
        retInt = IsWardId(cache);
        if (retInt == LEGAL_DATA) { // ��������Ϸ�
            res->wardId = atoi(cache);
        }
        else {
            flag = 1; if (retInt == FILE_END)break;
        }
        fscanf(fp, "%s", cache);
        retInt = IsNursingType(cache);
        if (retInt == LEGAL_DATA) { // �������ͺϷ�
            res->nursingType = atoi(cache);
        }
        else {
            flag = 1; if (retInt == FILE_END)break;
        }
        fscanf(fp, "%s", cache);
        retInt = IsBedType(cache);
        if (retInt == LEGAL_DATA) { // �������ͺϷ�
            res->bedType = atoi(cache);
        }
        else {
            flag = 1; if (retInt == FILE_END)break;
        }
        fscanf(fp, "%s", cache);
        if (IsNumber(cache)) {
            res->totalBedNum = atoi(cache);
        }
        else {
            flag = 1; if (IsEnd(cache))break;
        }
        fscanf(fp, "%s", cache);
        if (IsNumber(cache)) {
            res->occupiedBedNum = atoi(cache);
        }
        else {
            flag = 1; if (IsEnd(cache))break;
        }
        fscanf(fp, "%s", cache);
        if (IsNumber(cache)) {
            for (int i = 1; i <= strlen(cache); i++) {
                res->bedSituation[i] = cache[i] - '0';
                if (cache[i] - '0' > 1 || cache[i] - '0' < 0)flag = 1;
            }
        }
        else {
            flag = 1; if (IsEnd(cache))break;
        }
        fscanf(fp, "%s", cache);
        if (!IsEnd(cache)) {
            flag = 1; while (!IsEnd(cache))fscanf(fp, "%s", cache);
        }
        break;
    }
    if (flag) {
        free(res); res = NULL;
    }
    return res;
}
