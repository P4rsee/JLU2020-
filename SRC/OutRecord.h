#pragma once
#include "DiagnosisMessage.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

void OutCheckRecord(FILE* fp, DiagnosisSituationUnion* tempInfo);

// 输出开药类型到诊疗记录中
void OutPrescribeRecord(FILE* fp, DiagnosisSituationUnion* tempInfo);

// 输出住院类型到诊疗记录中
void OutInHospitalRecord(FILE* fp, DiagnosisSituationUnion* tempInfo);

// 输出数据到诊疗记录中
void OutRecord(FILE* fp, DiagnosisRecord* record);
