#include "global.h"
#include <malloc.h>

DiagnosisRecord* DiagnosisRecordHead;
DiagnosisRecord* InHospitalHead;
DiagnosisRecord* OthersHead;
DoctorNode* DoctorHead;
Ward* WardHead;

HospitalFund hospitalFund = { {0,0,0},{0,0,0},{0,0,0},{0,0,0},NULL,NULL,NULL,NULL };

int currentID = 1000;

TimeRecord currentTime;

char doctorType[4][15] = { "סԺҽ��","����ҽ��","������ҽ��","����ҽ��" };

char doctorSection[7][15] = { "��","����","�ڿ�","Ƥ����","�ۿ�","�ǿ�","��ͯ��" };

// �����
int drugPriceList[31] = { 100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400 };
int checkPriceList[31] = { 100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400 };
char nursingType[3][8] = { "0","����","��ͨ" };
char bedType[4][8] = { "0","������","˫����","������" };
int bedcost[4] = { 0,100,200,300 };
//

void FundPushUp() { // ����ȫ�ֵ�Fund
	SingleCost tmp = hospitalFund.allCost;
	double cache = tmp.yuan + tmp.jiao * 0.1 + tmp.fen * 0.01;
	sprintf(hospitalFund.stringOfAll, "%.2f", cache);
	tmp = hospitalFund.checkCost;
	cache = tmp.yuan + tmp.jiao * 0.1 + tmp.fen * 0.01;
	sprintf(hospitalFund.stringOfCheck, "%.2f", cache);
	tmp = hospitalFund.drugCost;
	cache = tmp.yuan + tmp.jiao * 0.1 + tmp.fen * 0.01;
	sprintf(hospitalFund.stringOfDrug, "%.2f", cache);
	tmp = hospitalFund.inHosipitalCost;
	cache = tmp.yuan + tmp.jiao * 0.1 + tmp.fen * 0.01;
	sprintf(hospitalFund.stringOfInHospital, "%.2f", cache);
}

void DoctorNodePushUp(int passDay) {
	DoctorNode* nowNode = DoctorHead->next;
	while (nowNode != NULL) { // �����continue
		if (nowNode->doctorInfo.doctorStatus != 1) {
			nowNode = nowNode->next;
			continue;
		}
		nowNode->doctorInfo.vacationLeft -= passDay;
		if (nowNode->doctorInfo.vacationLeft <= 0) {
			nowNode->doctorInfo.vacationLeft = 0;// ��֤�Ϸ�
			nowNode->doctorInfo.doctorStatus = 0;// �ָ���ְ
		}
		nowNode = nowNode->next;
	}
}

void ClearBusyDegree() {
	DoctorNode* nowNode = DoctorHead->next;
	while (nowNode != NULL) {
		nowNode->doctorInfo.busyDegree = 0;
		nowNode = nowNode->next;
	}
}

void AddBusyDegree(int docId, int val) {
	DoctorNode* nowNode = DoctorHead->next;
	while (nowNode != NULL) {
		if (nowNode->doctorInfo.id == docId) {
			nowNode->doctorInfo.busyDegree += val;
			break;
		}
		nowNode = nowNode->next;
	}
}