#pragma once
#include "DiagnosisMessage.h"
#include <stdlib.h>

bool IsNumber(const char* str); //�жϸ��ַ����Ƿ�Ϊ����

bool HasDate(int month, int day); // �ж����յ���ȷ��

bool IsEnd(const char* str);  // �Ƿ����������

bool IsDefault(const char* str); // �Ƿ����ȱʡֵ

int IsRegisterId(const char* str);  //�ж� registerId �Ƿ�Ϸ�

int IsDate(const char* str); //�ж������Ƿ�Ϸ�

int IsName(const char* str);  //�ж������Ƿ�Ϸ� char[40] ����

int IsAge(const char* str);  //�ж������Ƿ�Ϸ�

int IsDoctorId(const char* str); //���ҽ������

int IsSection(const char* str);  //�����Һ�

int IsDoctorLevel(const char* str); //���ҽ������ (һλ����)

int IsConsultTime(const char* str);  //������ʱ�� Э�飺ȱʡֵΪĬ��ȫ�����

int IsDiagnosisFlag(const char* str);  //����������ͱ��

int IsDeposit(const char* str); // ���Ѻ���Ƿ���ȷ

int IsByNowCost(const char* str); // ��鵱ǰ�����Ƿ���ȷ

int IsSickBedNumber(const char* str); // ��鲡���� 2+2λ

int IsDoctorStatus(const char* str); // ����Ƿ�Ϊҽ��״̬

int IsBusyDegree(const char* str); // ���ҽ����æ�̶�

int IsVacationLeft(const char* str); // ���ʣ�����

int IsWardId(const char* str); // ��鲡����

int IsOneDigitNumber(const char* str); // ����Ƿ�Ϊһλ��

bool IsInHospital(DiagnosisRecord* record); // �������Ƽ�¼�Ƿ�Ϊ����סԺ

bool IsTimedRecord(const DiagnosisRecord* record, // ����Ƿ��ڹ涨ʱ�� 
	int m1, int d1, int h1, int f1, int m2, int d2, int h2, int f2);

int IsCost(const char* str);					//Ԫ�Ƿ�

SingleCost StrToCost(const char* str);			//�ַ���ת��

int IsDrugKindNum(const char* str);				//�ж�ҩƷ������Ŀ�Ϸ���

int IsDrugId(const char* str);					//�ж�ҩƷ��ţ�Э�飺  1 - 30 

int IsDrugNum(const char* str);					//�ж�ĳ��ҩƷ��Ŀ��Э�飺���100��

void InitDiagosisRecord(DiagnosisRecord* res);  //��������ǰ��ʼ�����ĺ���