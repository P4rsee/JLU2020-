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

DiagnosisRecord* InRecord(FILE* fp);  // ������߼��,�������ݴ��󷵻�NULL
