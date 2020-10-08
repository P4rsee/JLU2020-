#include <stdio.h>
#include <graphics.h>
#include"DrawMunu.h"
#include"global.h"

int main() {
	//从文件中读入数据
	DiagnosisRecordHead = ReadFromDiagnosisFile("DiagnosisMessage.txt");
	DoctorHead = ReadFromDoctorFile("DoctorNode.txt");
	WardHead = ReadFromWardFile("Ward.txt");
	InHospitalHead = initDiagnosisRecord();		//哨兵
	OthersHead = initDiagnosisRecord();			//哨兵
	initCurrentFromFile("Current.txt");
	//链表类型分离
	splitByInHospital(DiagnosisRecordHead,InHospitalHead,OthersHead);
	
	//生成界面
	drawMenu();	
	
	//断电保存
	saveCurrentToFile("Current.txt");
	PrintToDiagnosisFile(DiagnosisRecordHead, "DiagnosisMessage.txt");
	PrintToDoctorFile(DoctorHead, "DoctorNode.txt");
	PrintToWardFile(WardHead, "Ward.txt");
	//释放内存
	freeAllList(DiagnosisRecordHead,DoctorHead,WardHead);
	return 0;
}

