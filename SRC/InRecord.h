#pragma once
#include "DiagnosisMessage.h"
#include "Checks.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// 赋值日期
void SetDate(char* str, int* month, int* day, int* hour, int* minute);
//80
// 用于文件读入 判断费用 若合法则赋值费用
int GetCost(FILE* fp, int* yuan, int* jiao, int* fen);

// 获取对应的与检查有关的信息
int GetCheckInfo(FILE* fp, DiagnosisSituationUnion* tempInfo);

// 获取对应的与开药有关的信息
int GetPrescribeInfo(FILE* fp, DiagnosisSituationUnion* tempInfo);

// 获取对应的与住院有关的信息
int GetInHospitalInfo(FILE* fp, DiagnosisSituationUnion* tempInfo);

// 从文件种获取患者相关信息
int GetPatientRecord(FILE* fp, DiagnosisRecord* res);

// 从文件中获取医生相关信息
int GetDoctorRecord(FILE* fp, DiagnosisRecord* res);

DiagnosisRecord* InRecord(FILE* fp);  // 边输入边检查,若有数据错误返回NULL
