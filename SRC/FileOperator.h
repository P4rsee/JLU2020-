#pragma once
#include "DiagnosisMessage.h"
#include "Checks.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// ��ֵ����
void SetDate(char* str, int* month, int* day, int* hour, int* minute);
//80
// �����ļ����� �жϷ��� ���Ϸ���ֵ����
int GetCost(FILE* fp, int* yuan, int* jiao, int* fen);

// ��ȡ��Ӧ�������йص���Ϣ
int GetCheckInfo(FILE* fp, DiagnosisSituationUnion* tempInfo);

// ��ȡ��Ӧ���뿪ҩ�йص���Ϣ
int GetPrescribeInfo(FILE* fp, DiagnosisSituationUnion* tempInfo);

// ��ȡ��Ӧ����סԺ�йص���Ϣ
int GetInHospitalInfo(FILE* fp, DiagnosisSituationUnion* tempInfo);

// ���ļ��ֻ�ȡ���������Ϣ
int GetPatientRecord(FILE* fp, DiagnosisRecord* res);

// ���ļ��л�ȡҽ�������Ϣ
int GetDoctorRecord(FILE* fp, DiagnosisRecord* res);

void OutCheckRecord(FILE* fp, DiagnosisSituationUnion* tempInfo);

// �����ҩ���͵����Ƽ�¼��
void OutPrescribeRecord(FILE* fp, DiagnosisSituationUnion* tempInfo);

// ���סԺ���͵����Ƽ�¼��
void OutInHospitalRecord(FILE* fp, DiagnosisSituationUnion* tempInfo);

// ������ݵ����Ƽ�¼��
void OutRecord(FILE* fp, DiagnosisRecord* record);

// ���뵥����¼������߼��,�������ݴ��󷵻�NULL
DiagnosisRecord* InRecord(FILE* fp);

DiagnosisRecord* ReadFromDiagnosisFile(const char* readPath);//���ļ�����

void PrintToDiagnosisFile(DiagnosisRecord* head, const char* writePath);

DoctorNode* GetSingleDoctorNode(FILE* fp); // ���ļ��ж�����ҽ���ڵ�

DoctorNode* ReadFromDoctorFile(const char* readPath);//char*Ϊ�ļ�·��

void OutDoctorNode(FILE* fp, DoctorNode* node);

void PrintToDoctorFile(DoctorNode* head, const char* writePath);

Ward* GetSingleWard(FILE* fp); // ���ļ��ж��뵥�������ڵ�

Ward* ReadFromWardFile(const char* readPath);

void OutWard(FILE* fp, Ward* ward);

void PrintToWardFile(Ward* head, const char* writePath);

// ����һ�����Ƽ�¼�ڵ�
void CopyRecord(DiagnosisRecord* des, DiagnosisRecord* src);

// �ж������¼�Ƿ�Ϊ����סԺ�Ĳ���
bool IsInHospital(DiagnosisRecord* record);

//void PrintToWardFile(Ward* head, const char* writePath);

//void CopyRecord(DiagnosisRecord* des, DiagnosisRecord* src);

void splitByInHospital(DiagnosisRecord* totHead, // ��סԺ�ͷ�סԺ�ֿ�
	DiagnosisRecord* inHosiptalHead, DiagnosisRecord* othersHead);


void initCurrentFromFile(const char* readPath);

void saveCurrentToFile(const char* writePath);