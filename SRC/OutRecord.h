#pragma once
#include "DiagnosisMessage.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

void OutCheckRecord(FILE* fp, DiagnosisSituationUnion* tempInfo);

// �����ҩ���͵����Ƽ�¼��
void OutPrescribeRecord(FILE* fp, DiagnosisSituationUnion* tempInfo);

// ���סԺ���͵����Ƽ�¼��
void OutInHospitalRecord(FILE* fp, DiagnosisSituationUnion* tempInfo);

// ������ݵ����Ƽ�¼��
void OutRecord(FILE* fp, DiagnosisRecord* record);
