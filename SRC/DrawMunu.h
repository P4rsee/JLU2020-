#pragma once
#include <stdio.h>
#include <graphics.h>
#include"DiagnosisMessage.h"
#include"Checks.h"
#include "FileOperator.h"
#include"ListOperator.h"
#include<time.h>
void drawMenu();			//���˵�
void drawLogMenu();			//���˵�---->���Ƽ�¼
void drawAddLogRecord();	//���Ƽ�¼-->������Ƽ�¼
void drawPatientToTreat();  //���˵�---->���߾���
void drawDocSituation();	//���˵�---->ҽ�����
void drawTiming();			//���˵�---->ʱ������
//Made by CKH
void drawSearchMenu();		//���Ƽ�¼-->��ѯ���Ƽ�¼
void printData(char* buf, DiagnosisRecord* res);
void drawUpdateMenu();		//���Ƽ�¼-->�޸����Ƽ�¼

//
void drawOutHospital();		//���߾���-->��Ҫ��Ժ
void drawToHospital();		//���߾���-->��ҪסԺ
void drawToCheck();			//���߾���-->��Ҫ���
void drawToRegister();		//���߾���-->��Ҫ�Һ�
void drawToPrescribe();		//���߾���-->��Ҫ��ҩ
void drawToHandDeposit();	//���˵�---->סԺ�ɷ�(Ѻ��)
void drawBedSituation();	//���˵�---->��λ���
void drawHospitalIncome();	//���˵�---->ҽԺӪҵ��
void drawInHospitalPatient(); //���˵�-->���߱���
//���˵�-->ʱ������-->�޸�ʱ��-->�Զ�����������Ҫ�ɷѵ�סԺ��������
void drawPatientToDeposit(int cnt);
