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

void OutCheckRecord(FILE* fp, DiagnosisSituationUnion* tempInfo);

// 输出开药类型到诊疗记录中
void OutPrescribeRecord(FILE* fp, DiagnosisSituationUnion* tempInfo);

// 输出住院类型到诊疗记录中
void OutInHospitalRecord(FILE* fp, DiagnosisSituationUnion* tempInfo);

// 输出数据到诊疗记录中
void OutRecord(FILE* fp, DiagnosisRecord* record);

// 读入单个记录边输入边检查,若有数据错误返回NULL
DiagnosisRecord* InRecord(FILE* fp);

DiagnosisRecord* ReadFromDiagnosisFile(const char* readPath);//从文件读入

void PrintToDiagnosisFile(DiagnosisRecord* head, const char* writePath);

DoctorNode* GetSingleDoctorNode(FILE* fp); // 从文件中读单个医生节点

DoctorNode* ReadFromDoctorFile(const char* readPath);//char*为文件路径

void OutDoctorNode(FILE* fp, DoctorNode* node);

void PrintToDoctorFile(DoctorNode* head, const char* writePath);

Ward* GetSingleWard(FILE* fp); // 从文件中读入单个病房节点

Ward* ReadFromWardFile(const char* readPath);

void OutWard(FILE* fp, Ward* ward);

void PrintToWardFile(Ward* head, const char* writePath);

// 拷贝一个诊疗记录节点
void CopyRecord(DiagnosisRecord* des, DiagnosisRecord* src);

// 判断这个记录是否为正在住院的病人
bool IsInHospital(DiagnosisRecord* record);

//void PrintToWardFile(Ward* head, const char* writePath);

//void CopyRecord(DiagnosisRecord* des, DiagnosisRecord* src);

void splitByInHospital(DiagnosisRecord* totHead, // 将住院和非住院分开
	DiagnosisRecord* inHosiptalHead, DiagnosisRecord* othersHead);


void initCurrentFromFile(const char* readPath);

void saveCurrentToFile(const char* writePath);