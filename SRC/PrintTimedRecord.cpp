#include "InRecord.h"
#include "Checks.h"
#include <stdio.h>
                                                                                
void PrintTimedRecord(int m1, int d1, int h1, int f1, int m2, int d2, int h2, int f2) {
    FILE* fp = fopen("in.txt", "r");
    if (fp == NULL) {
        printf("打开失败!\n");
    }
    while (!feof(fp)) {
        DiagnosisRecord* nowRecord = InRecord(fp);
        TimeRecord* tmp = &nowRecord->TimeRecord;
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
        //加入链表操作
    }
    //输出到界面操作
}

typedef struct Ward {
    int wardId;
    int nursingType;
    int bedType;
    int totalBedNum;
    int ocuupiedBedNum;
    bool bedSituation[10];
    Ward* next;
};

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
    char cache[100];  // 暂时存储 用于检查
    int flag = 0;  // 标记是否有错误
    int  retInt = 0; // 记录每次检查的返回值边检查,若有数据错误返回NULL
    Ward* res = (Ward*)malloc(sizeof(Ward));
    res->next = NULL;
    while (1) {
        fscanf(fp, "%s", cache);
        retInt = IsWardId(cache);
        if (retInt == LEGAL_DATA) { // 病房号码合法
            res->wardId = atoi(cache);
        }
        else {
            flag = 1; if (retInt == FILE_END)break;
        }
        fscanf(fp, "%s", cache);
        retInt = IsNursingType(cache);
        if (retInt == LEGAL_DATA) { // 护理类型合法
            res->nursingType = atoi(cache);
        }
        else {
            flag = 1; if (retInt == FILE_END)break;
        }
        fscanf(fp, "%s", cache);
        retInt = IsBedType(cache);
        if (retInt == LEGAL_DATA) { // 病床类型合法
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
            res->ocuupiedBedNum = atoi(cache);
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
