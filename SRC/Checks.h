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
