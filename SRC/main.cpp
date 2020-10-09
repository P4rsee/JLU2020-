#include <stdio.h>
#include <graphics.h>
#include"DrawMunu.h"
#include"global.h"

int main() {
	//���ļ��ж�������
	DiagnosisRecordHead = ReadFromDiagnosisFile("DiagnosisMessage.txt");
	DoctorHead = ReadFromDoctorFile("DoctorNode.txt");
	WardHead = ReadFromWardFile("Ward.txt");
	InHospitalHead = initDiagnosisRecord();		//�ڱ�
	OthersHead = initDiagnosisRecord();			//�ڱ�
	initCurrentFromFile("Current.txt");
	//�������ͷ���
	splitByInHospital(DiagnosisRecordHead,InHospitalHead,OthersHead);
	
	//���ɽ���
	drawMenu();	
	
	//�ϵ籣��
	saveCurrentToFile("Current.txt");
	PrintToDiagnosisFile(DiagnosisRecordHead, "DiagnosisMessage.txt");
	PrintToDoctorFile(DoctorHead, "DoctorNode.txt");
	PrintToWardFile(WardHead, "Ward.txt");
	//�ͷ��ڴ�
	freeAllList(DiagnosisRecordHead,DoctorHead,WardHead);
	return 0;
}

