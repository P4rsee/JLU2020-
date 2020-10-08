#pragma once
#include <stdio.h>
#include <graphics.h>
#include"DiagnosisMessage.h"
#include"Checks.h"
#include "FileOperator.h"
#include"ListOperator.h"
#include<time.h>
void drawMenu();			//主菜单
void drawLogMenu();			//主菜单---->诊疗记录
void drawAddLogRecord();	//诊疗记录-->添加诊疗记录
void drawPatientToTreat();  //主菜单---->患者就诊
void drawDocSituation();	//主菜单---->医生情况
void drawTiming();			//主菜单---->时间流逝
//Made by CKH
void drawSearchMenu();		//诊疗记录-->查询诊疗记录
void printData(char* buf, DiagnosisRecord* res);
void drawUpdateMenu();		//诊疗记录-->修改诊疗记录

//
void drawOutHospital();		//患者就诊-->我要出院
void drawToHospital();		//患者就诊-->我要住院
void drawToCheck();			//患者就诊-->我要检查
void drawToRegister();		//患者就诊-->我要挂号
void drawToPrescribe();		//患者就诊-->我要开药
void drawToHandDeposit();	//主菜单---->住院缴费(押金)
void drawBedSituation();	//主菜单---->床位情况
void drawHospitalIncome();	//主菜单---->医院营业额
void drawInHospitalPatient(); //主菜单-->患者报表
//主菜单-->时间流逝-->修改时间-->自动弹出提醒需要缴费的住院患者名单
void drawPatientToDeposit(int cnt);
