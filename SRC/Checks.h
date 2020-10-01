#pragma once
#include "DiagnosisMessage.h"
#include <stdlib.h>

bool IsNumber(const char* str); //判断该字符串是否为数字

bool HasDate(int month, int day); // 判断月日的正确性

bool IsEnd(const char* str);  // 是否读到结束符

bool IsDefault(const char* str); // 是否读到缺省值

int IsRegisterId(const char* str);  //判断 registerId 是否合法

int IsDate(const char* str); //判断日期是否合法

int IsName(const char* str);  //判断名字是否合法 char[40] 以内

int IsAge(const char* str);  //判断年龄是否合法

int IsDoctorId(const char* str); //检查医生工号

int IsSection(const char* str);  //检查科室号

int IsDoctorLevel(const char* str); //检查医生级别 (一位数字)

int IsConsultTime(const char* str);  //检查出诊时间 协议：缺省值为默认全天出诊

int IsDiagnosisFlag(const char* str);  //检查诊疗类型编号

int IsDeposit(const char* str); // 检查押金是否正确
