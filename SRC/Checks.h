#pragma once
#include "DiagnosisMessage.h"
#include <stdlib.h>

bool IsNumber(const char* str);  // 判断该字符串是否为数字

bool HasDate(int month, int day);  // 判断月日的正确性

bool IsEnd(const char* str);  // 是否读到结束符

bool IsDefault(const char* str);  // 是否读到缺省值

int IsRegisterId(const char* str);  // 判断 registerId 是否合法

int IsDate(const char* str);  // 判断日期是否合法

int IsName(const char* str);  // 判断名字是否合法 char[40] 以内

int IsAge(const char* str);  // 判断年龄是否合法

int IsDoctorId(const char* str);  // 检查医生工号

int IsSection(const char* str);  // 检查科室号

int IsDoctorLevel(const char* str);  // 检查医生级别 (一位数字)

int IsConsultTime(const char* str);  // 检查出诊时间 协议：缺省值为默认全天出诊

int IsDiagnosisFlag(const char* str);  // 检查诊疗类型编号

int IsDeposit(const char* str);  // 检查押金是否正确

int IsByNowCost(const char* str);  // 检查当前花费是否正确

int IsSickBedNumber(const char* str);  // 检查病床号 2+2位

int IsDoctorStatus(const char* str);  // 检查是否为医生状态

int IsBusyDegree(const char* str);  // 检查医生繁忙程度

int IsVacationLeft(const char* str);  // 检查剩余假期

int IsWardId(const char* str);  // 检查病房号

int IsOneDigitNumber(const char* str);  // 检查是否为一位数

bool IsInHospital(DiagnosisRecord* record);  // 检查该诊疗记录是否为正在住院

bool IsTimedRecord(const DiagnosisRecord* record,  // 检查是否在规定时间
  int m1, int d1, int h1, int f1, int m2, int d2, int h2, int f2);

int IsCost(const char* str);  // 元角分

SingleCost StrToCost(const char* str);  // 字符串转换

int IsDrugKindNum(const char* str);  // 判断药品种类数目合法性

int IsDrugId(const char* str);  // 判断药品编号，协议：1 - 30

int IsDrugNum(const char* str);  // 判断某种药品数目，协议：最多100盒

void InitDiagosisRecord(DiagnosisRecord* res);  // 界面输入前初始化结点的函数
