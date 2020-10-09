#pragma once
#include"DrawMunu.h"
#include"DiagnosisMessage.h"
#include "global.h"
//DrawAddLog.cpp

void drawAddLogRecord() { //�����ӽ���--��ӣ����룩һ�����Ƽ�¼

	DiagnosisRecord* res = initDiagnosisRecord();
	//��ʼ���ڵ�������Ϣ
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "����");//�������ִ�С ��ʽ 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextcolor(BLACK);
	outtextxy(30, 50, "�Һź��룺");
	outtextxy(30, 80, "����������");
	outtextxy(30, 110, "�������䣺");
	outtextxy(30, 140, "ҽ��������");
	outtextxy(30, 170, "ҽ������");
	outtextxy(30, 200, "ҽ�����ң�");
	outtextxy(30, 230, "ҽ�����ţ�");
	outtextxy(30, 260, "�������ڣ�");
	outtextxy(30, 290, "�������ͣ�");

	setfillcolor(RGB(210, 210, 210));  //��ť��ɫ��ɫ

	fillrectangle(300, 50, 380, 70);
	fillrectangle(300, 80, 380, 100);
	fillrectangle(300, 110, 380, 130);
	fillrectangle(300, 140, 380, 160);
	fillrectangle(300, 170, 380, 190);
	fillrectangle(300, 200, 380, 220);
	fillrectangle(300, 230, 380, 250);

	fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
	fillrectangle(300, 640, 375, 660);

	fillrectangle(150, 295, 165, 310);  //��������ѡ���־
	fillrectangle(240, 295, 255, 310);
	fillrectangle(330, 295, 345, 310);

	outtextxy(170, 290, "סԺ");  //��������text
	outtextxy(260, 290, "��ҩ");
	outtextxy(350, 290, "���");

	settextstyle(15, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	outtextxy(305, 53, "���/�޸�");
	outtextxy(305, 83, "���/�޸�");
	outtextxy(305, 113, "���/�޸�");
	outtextxy(305, 143, "���/�޸�");
	outtextxy(305, 173, "���/�޸�");
	outtextxy(305, 203, "���/�޸�");
	outtextxy(305, 233, "���/�޸�");
	outtextxy(305, 263, "���/�޸�");
	outtextxy(147, 642, "ȷ��");
	outtextxy(322, 642, "����");
	SingleCost now = constructSingleCost(0, 0, 0);
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 50 && m.y <= 70) {  //�Һź���
			clearrectangle(300, 50, 380, 70);
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 50, 380, 70);
			outtextxy(305, 53, "���/�޸�");

			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[8];
				InputBox(buf, 8, "������7λ�Һź���");
				if (LEGAL_DATA == IsRegisterId(buf)) {
					res->patientInfo.registerId = atoi(buf);  //�洢���ڴ�
					clearrectangle(150, 50, 290, 70);  //ˢ����ʾ����
					outtextxy(150, 50, buf);
				}
				else {
					continue;
				}
			}
		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 80 && m.y <= 100) {  //��������
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 80, 380, 100);
			outtextxy(305, 83, "���/�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[50];
				InputBox(buf, 41, "�����뻼������(20������)");
				if (LEGAL_DATA == IsName(buf)) {
					strcpy(res->patientInfo.name, buf);  // �洢���ڴ�
					clearrectangle(150, 80, 290, 100);  // ˢ����ʾ����
					outtextxy(150, 80, buf);  //��ʾ

				}
				else {
					continue;
				}

			}
		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 110 && m.y <= 130) {  //��������
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 110, 380, 130);
			outtextxy(305, 113, "���/�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[5];
				InputBox(buf, 4, "�����뻼������");
				if (LEGAL_DATA == IsAge(buf)) {
					res->patientInfo.age = atoi(buf);
					clearrectangle(150, 110, 290, 130);
					outtextxy(150, 110, buf);

				}
				else {
					continue;
				}

			}
		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 140 && m.y <= 160) {  //ҽ������
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 140, 380, 160);
			outtextxy(305, 143, "���/�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[50];
				InputBox(buf, 41, "������ҽ������(20������)");
				if (LEGAL_DATA == IsName(buf)) {
					strcpy(res->doctorInfo.name, buf);  // �洢���ڴ�
					clearrectangle(150, 140, 290, 160);  // ˢ����ʾ����
					outtextxy(150, 140, buf);  //��ʾ

				}
				else {
					continue;
				}

			}

		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 170 && m.y <= 190) {  //ҽ������
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 170, 380, 190);
			outtextxy(305, 173, "���/�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[2];
				InputBox(buf, 2, "������ҽ������");
				if (LEGAL_DATA == IsDoctorLevel(buf)) {
					res->doctorInfo.level = atoi(buf);
					clearrectangle(150, 170, 290, 190);
					outtextxy(150, 170, buf);  //��ʾ

				}
				else {
					continue;
				}

			}
		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 200 && m.y <= 220) {  //ҽ������
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 200, 380, 220);
			outtextxy(305, 203, "���/�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[4];
				InputBox(buf, 3, "������ҽ������");
				if (LEGAL_DATA == IsSection(buf)) {
					res->doctorInfo.sectionId = atoi(buf);
					clearrectangle(150, 200, 290, 220);
					outtextxy(150, 200, buf);

				}
				else {
					continue;
				}

			}


		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 230 && m.y <= 250) {  //ҽ������
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 230, 380, 250);
			outtextxy(305, 233, "���/�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[6];
				InputBox(buf, 5, "������ҽ������");
				if (LEGAL_DATA == IsDoctorId(buf)) {
					res->doctorInfo.id = atoi(buf);
					clearrectangle(150, 230, 290, 250);
					outtextxy(150, 230, buf);

				}
				else {
					continue;
				}

			}


		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 260 && m.y <= 280) {  //�������ڣ���ʼ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 260, 380, 280);
			outtextxy(305, 263, "���/�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[10];
				InputBox(buf, 9, "��������������");
				if (LEGAL_DATA == IsDate(buf)) {
					SetDate(buf, &(res->recordTime.month), &(res->recordTime.day),
						&(res->recordTime.hour), &(res->recordTime.minute));
					clearrectangle(150, 260, 290, 280);
					outtextxy(150, 260, buf);

				}
				else {
					continue;
				}

			}
		}
		else if (m.x >= 150 && m.x <= 165 && m.y >= 295 && m.y <= 310) {  //סԺ
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(152, 297, 163, 308);
			if (m.uMsg == WM_LBUTTONDOWN) {
				now.yuan = 0;
				res->diagnosisSituation.setFlag = 2;
				char buf_CDate[10];
				char buf_LDate[10];
				char buf_Cost[10];
				char buf_bed[5];
				InputBox(buf_CDate, 9, "��������Ժ����");
				InputBox(buf_LDate, 9, "�������Ժ����");
				InputBox(buf_bed, 5, "�����벡������");
				InputBox(buf_Cost, 9, "����������ܺ�");
				if (LEGAL_DATA == IsDate(buf_CDate) &&
					LEGAL_DATA == IsDate(buf_LDate) &&
					LEGAL_DATA == IsCost(buf_Cost)  &&
					LEGAL_DATA == IsSickBedNumber(buf_bed)) {
					InHospitalRecord*temp = &(res->diagnosisSituation.
						diagnosisSituationInfo.inHospitalRecord);
					temp->costByNow = StrToCost(buf_Cost);
					SetDate(buf_CDate, &(temp->hospitalizedDate.month)
						, &(temp->hospitalizedDate.day)
						, &(temp->hospitalizedDate.hour)
						, &(temp->hospitalizedDate.minute)
					);
					SetDate(buf_LDate, &(temp->leaveDate.month)
						, &(temp->leaveDate.day)
						, &(temp->leaveDate.hour)
						, &(temp->leaveDate.minute)
					);
					temp->sickBedNumber = atoi(buf_bed);
					//дһ���µ�SingleCost constructsinglecost(char * str);
					temp->costByNow = constructSingleCost(buf_Cost);				//���ٻ�ûд(����д��)
					now = temp->costByNow;
					clearrectangle(30, 320, 450, 600);
					settextstyle(20, 0, "����");
					outtextxy(30, 320, "��Ժ���ڣ�");
					outtextxy(30, 350, "��Ժ���ڣ�");
					outtextxy(30, 380, "�����ܺͣ�");
					settextstyle(15, 0, "����");
					outtextxy(150, 320, buf_CDate);
					outtextxy(150, 350, buf_LDate);
					outtextxy(150, 380, buf_Cost);
				}
			}

		}
		else if (m.x >= 240 && m.x <= 255 && m.y >= 295 && m.y <= 310) {  //��ҩ
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(242, 297, 253, 308);
			if (m.uMsg == WM_LBUTTONDOWN) {
				
				res->diagnosisSituation.setFlag = 1;
				char buf_num[3];
				InputBox(buf_num, 2, "������ҩƷ������");
				if (LEGAL_DATA == IsDrugKindNum(buf_num)) {
					now.yuan = 0;
					clearrectangle(30, 320, 450, 600);
					settextstyle(20, 0, "����");
					outtextxy(30, 320, "ҩƷ���");
					outtextxy(130, 320, "ҩƷ��Ŀ");
					outtextxy(230, 320, "ҩƷ����");
					outtextxy(330, 320, "ҩƷ����");
					int x = 30;
					int y = 350;

					int num = atoi(buf_num);
					PrescribeInfo* head = (PrescribeInfo*)malloc(sizeof(PrescribeInfo));
					PrescribeInfo* rear = head;
					head->next = NULL;
					for (int i = 0; i < num; i++) {
						char buf_DrugId[3];
						char buf_DrugNum[4];
						InputBox(buf_DrugId, 3, "������ҩƷ���");
						InputBox(buf_DrugNum, 4, "������ҩƷ����");
						if (LEGAL_DATA == IsDrugId(buf_DrugId) &&
							LEGAL_DATA == IsDrugNum(buf_DrugNum)) {
							outtextxy(x, y, buf_DrugId);
							outtextxy(x + 100, y, buf_DrugNum);

							char temp_p[10];
							itoa(drugPriceList[atoi(buf_DrugId)], temp_p, 10);
							outtextxy(x + 200, y, temp_p);

							char temp_t[10];
							itoa(drugPriceList[atoi(buf_DrugId)] * atoi(buf_DrugNum), temp_t, 10);
							outtextxy(x + 300, y, temp_t);

							y += 30;
							now.yuan += drugPriceList[atoi(buf_DrugId)] * atoi(buf_DrugNum);
							rear->next = (PrescribeInfo*)malloc(sizeof(PrescribeInfo));
							rear->next->next = NULL;
							rear->next->drugId = atoi(buf_DrugId);
							rear->next->drugNumber = atoi(buf_DrugNum);
							rear = rear->next;
						}
						else {
							i--;
						}
					}
					//temp->next = NULL;
					free(rear);
					res->diagnosisSituation.diagnosisSituationInfo
						.prescribeRecord.typeNumber = atoi(buf_num);
					res->diagnosisSituation.diagnosisSituationInfo
						.prescribeRecord.prescribeInfoHead = head;

				}


			}

		}
		else if (m.x >= 330 && m.x <= 345 && m.y >= 295 && m.y <= 310) {  //���
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(332, 297, 343, 308);
			if (m.uMsg == WM_LBUTTONDOWN) {
				res->diagnosisSituation.setFlag = 0;
				char buf_num[3];
				InputBox(buf_num, 3, "��������������");
				if (LEGAL_DATA == IsDrugKindNum(buf_num)) {
					now.yuan = 0;
					clearrectangle(30, 320, 450, 600);
					settextstyle(20, 0, "����");
					outtextxy(30, 320, "�����");
					outtextxy(230, 320, "������");

					int x = 30;
					int y = 350;
					int num = atoi(buf_num);
					CheckInfo* head = (CheckInfo*)malloc(sizeof(CheckInfo));
					head->next = NULL;
					CheckInfo* rear = head;
					//CheckInfo* temp = head;
					for (int i = 0; i < num; i++) {
						char buf_CheckId[3];
						InputBox(buf_CheckId, 3, "����������");
						if (LEGAL_DATA == IsDrugId(buf_CheckId)) {
							outtextxy(x, y, buf_CheckId);

							char temp_t[10];
							itoa(drugPriceList[atoi(buf_CheckId)], temp_t, 10);
							outtextxy(x + 200, y, temp_t);
							y += 30;
							//temp = rear;
							rear->next = (CheckInfo*)malloc(sizeof(CheckInfo));
							rear->next->next = NULL;
							rear->next->checkId = atoi(buf_CheckId);
							//rear->singleCost
							rear = rear->next;
						}
						else {
							i--;
						}

					}
					//temp->next = NULL;
					//free(rear);
					res->diagnosisSituation.diagnosisSituationInfo
						.checkRecord.typeNumber = atoi(buf_num);
					res->diagnosisSituation.diagnosisSituationInfo
						.checkRecord.checkInfoHead = head;

				}

			}

		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //ȷ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "ȷ��");
			if (m.uMsg == WM_LBUTTONDOWN) {
				pushBackDiagnosisList(DiagnosisRecordHead,res);
				switch (res->diagnosisSituation.setFlag) {
				case 0:
					hospitalFund.checkCost = costAdd(hospitalFund.checkCost, now);
					break;
				case 1:
					hospitalFund.drugCost = costAdd(hospitalFund.drugCost, now);
					break;
				case 2:
					hospitalFund.inHosipitalCost = costAdd(hospitalFund.inHosipitalCost, now);
					break;
				default:
					break;
				}
				hospitalFund.allCost = costAdd(hospitalFund.allCost, now);
				return;
			}

		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {  //����
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "����");
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}

		}
		else {
			setfillcolor(RGB(210, 210, 210));  //��ɫ
			settextstyle(15, 0, "����");

			fillrectangle(300, 50, 380, 70);
			fillrectangle(300, 80, 380, 100);
			fillrectangle(300, 110, 380, 130);
			fillrectangle(300, 140, 380, 160);
			fillrectangle(300, 170, 380, 190);
			fillrectangle(300, 200, 380, 220);
			fillrectangle(300, 230, 380, 250);
			fillrectangle(300, 260, 380, 280);
			fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
			fillrectangle(300, 640, 375, 660);

			outtextxy(305, 53, "���/�޸�");
			outtextxy(305, 83, "���/�޸�");
			outtextxy(305, 113, "���/�޸�");
			outtextxy(305, 143, "���/�޸�");
			outtextxy(305, 173, "���/�޸�");
			outtextxy(305, 203, "���/�޸�");
			outtextxy(305, 233, "���/�޸�");
			outtextxy(305, 263, "���/�޸�");
			outtextxy(147, 642, "ȷ��");
			outtextxy(322, 642, "����");



			if (2 == res->diagnosisSituation.setFlag) { //סԺ
				setfillcolor(RGB(10, 250, 10));
				fillrectangle(152, 297, 163, 308);
				setfillcolor(RGB(210, 210, 210));
			}
			else {
				fillrectangle(150, 295, 165, 310);
			}
			if (1 == res->diagnosisSituation.setFlag) { //��ҩ
				setfillcolor(RGB(10, 250, 10));
				fillrectangle(242, 297, 253, 308);
				setfillcolor(RGB(210, 210, 210));
			}
			else {
				fillrectangle(240, 295, 255, 310);
			}
			if (0 == res->diagnosisSituation.setFlag) { //���
				setfillcolor(RGB(10, 250, 10));
				fillrectangle(332, 297, 343, 308);
				setfillcolor(RGB(210, 210, 210));
			}
			else {
				fillrectangle(330, 295, 345, 310);
			}
		}

	}

	free(res);
}


//Made by CKH*******************************************************************

void drawPrintRecordRefresh() {
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 356 && m.x <= 431 && m.y >= 640 && m.y <= 660) {  //ȷ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(356, 640, 431, 660);
			outtextxy(378, 642, "ȷ��");
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawSearchMenu();
				//Ч��ͬ����
				break;
			}
		}
		else if (m.x >= 566 && m.x <= 641 && m.y >= 640 && m.y <= 660) {  //����
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(566, 640, 641, 660);
			outtextxy(588, 642, "����");
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawSearchMenu();
				break;
			}
		}
		else {
			setfillcolor(RGB(210, 210, 210));  //��ɫ
			settextstyle(15, 0, "����");

			fillrectangle(356, 640, 431, 660);  //���غ�ȷ��
			fillrectangle(566, 640, 641, 660);

			outtextxy(378, 642, "ȷ��");
			outtextxy(588, 642, "����");
		}
	}
}

void drawPrintRecordInit() {
	//��ʼ���ڵ�������Ϣ
	initgraph(1000, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "����");//�������ִ�С ��ʽ 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextcolor(BLACK);
	outtextxy(450, 15, "���Ƽ�¼");
	settextstyle(18, 0, "����");
	outtextxy(30, 70, "��¼����  �Һ�   ���� �������� ��������"
		" ҽ������ ���Һ� ҽ������ ҽ������          ��ϸ");

	setfillcolor(RGB(210, 210, 210));  //��ť��ɫ��ɫ

	fillrectangle(356, 640, 431, 660);  //���غ�ȷ��
	fillrectangle(566, 640, 641, 660);

	settextstyle(16, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	outtextxy(378, 642, "ȷ��");
	outtextxy(588, 642, "����");
}

void printBySetFlagToUi(int x, int y, int setFlag) {
	if (setFlag == 0)outtextxy(x, y, "���");
	if (setFlag == 1)outtextxy(x, y, "��ҩ");
	if (setFlag == 2)outtextxy(x, y, "סԺ");
}

void printByLevelId(int x, int y, int index) {
	if (index == 2)x = x - 7;
	outtextxy(x, y, doctorType[index]);
}



// ����������͵������¼������
void printSituationInfoToUi(int x, int y, DiagnosisRecord* record) {
	DiagnosisSituationUnion* tempInfo =
		&record->diagnosisSituation.diagnosisSituationInfo;
	int setFlag = record->diagnosisSituation.setFlag;
	char buf[1000];
	if (setFlag == 0) { // ���
		sprintf(buf, "      �ܷ���:%.2f", tempInfo->checkRecord.totalCost.yuan
			+ tempInfo->checkRecord.totalCost.jiao * 0.1
			+ tempInfo->checkRecord.totalCost.fen * 0.01);
		outtextxy(x, y, buf);
	}
	else if (setFlag == 1) { // ��ҩ
		sprintf(buf, "      �ܷ���:%.2f", tempInfo->prescribeRecord.totalCost.yuan
			+ tempInfo->prescribeRecord.totalCost.jiao * 0.1
			+ tempInfo->prescribeRecord.totalCost.fen * 0.01);
		outtextxy(x, y, buf);
	}
	else if (setFlag == 2) { // סԺ
		settextstyle(16, 0, "����");
		outtextxy(x, y, "��:");
		settextstyle(14, 0, "����");
		x = x + 20;
		sprintf(buf, "%02d-%02d",
			tempInfo->inHospitalRecord.hospitalizedDate.month,
			tempInfo->inHospitalRecord.hospitalizedDate.day);
		outtextxy(x, y + 2, buf);
		settextstyle(16, 0, "����");
		x = x + 38;
		outtextxy(x, y, "��:");
		settextstyle(14, 0, "����");
		x = x + 20;
		sprintf(buf, "%02d-%02d",
			tempInfo->inHospitalRecord.predictedLeaveDate.month,
			tempInfo->inHospitalRecord.predictedLeaveDate.day);
		outtextxy(x, y + 2, buf);
		settextstyle(16, 0, "����");
		x = x + 40;
		sprintf(buf, "����:%.2f",
			tempInfo->inHospitalRecord.costByNow.yuan
			+ tempInfo->inHospitalRecord.costByNow.jiao * 0.1
			+ tempInfo->inHospitalRecord.costByNow.fen * 0.01);
		outtextxy(x, y, buf);
	}
	//printf("%s\n",buf);
}

// ����������Ƽ�¼������
void printSingleRecordToUi(int x, int y, DiagnosisRecord* record) {
	settextstyle(14, 0, "����");
	char buf[200];
	//outtextxy(30, 70, "��¼���� �Һ� ���� �������� ��������"
	//" ҽ������ ���Һ� ҽ������ ҽ������             ��ϸ");
	sprintf(buf, "2020-%02d-%02d",
		record->recordTime.month, record->recordTime.day);
	outtextxy(x, y, buf);
	x = x + 85;
	sprintf(buf, "%07d", record->patientInfo.registerId);
	outtextxy(x, y, buf);
	settextstyle(15, 0, "����");
	x = x + 70;
	printBySetFlagToUi(x, y, record->diagnosisSituation.setFlag);
	x = x + 55;
	outtextxy(x, y, record->patientInfo.name); // �����������
	x = x + 98;
	sprintf(buf, "%d", record->patientInfo.age);
	outtextxy(x, y, buf); // ��������
	x = x + 75;
	sprintf(buf, "%04d", record->doctorInfo.id);
	outtextxy(x, y, buf); // ҽ������
	x = x + 80;
	sprintf(buf, "%02d", record->doctorInfo.sectionId);
	outtextxy(x, y, buf); // ���Һ�
	x = x + 53;
	outtextxy(x, y, record->doctorInfo.name); // ҽ������
	x = x + 74;
	printByLevelId(x, y, record->doctorInfo.level); // ҽ������
	x = x + 80;
	printSituationInfoToUi(x, y, record);
}

// ���ݿ��Ҵ�ӡ
void printBySectionId(const char* sectionId) {
	drawPrintRecordInit();
	int id = atoi(sectionId);
	DiagnosisRecord* nowRecord = DiagnosisRecordHead;
	int x = 30, y = 95;
	while (nowRecord != NULL) {
		nowRecord = nowRecord->next;
		if (nowRecord == NULL ||
			nowRecord->doctorInfo.sectionId != id)continue;
		printSingleRecordToUi(x, y, nowRecord);
		y += 25;
	}
	drawPrintRecordRefresh();
}

// ����ҽ�����Ŵ�ӡ
void printByDoctorId(const char* doctorId) {
	drawPrintRecordInit();
	int id = atoi(doctorId);
	DiagnosisRecord* nowRecord = DiagnosisRecordHead;
	int x = 30, y = 95;
	while (nowRecord != NULL) {
		nowRecord = nowRecord->next;
		if (nowRecord == NULL ||
			nowRecord->doctorInfo.id != id)continue;
		printSingleRecordToUi(x, y, nowRecord);
		y += 25;
	}
	drawPrintRecordRefresh();
}

// ���ݻ�����Ϣ��ӡ
void printByPatient(const char* patientName, const char* patientAge) {
	drawPrintRecordInit();
	int age = atoi(patientAge);
	DiagnosisRecord* nowRecord = DiagnosisRecordHead;
	int x = 30, y = 95;
	while (nowRecord != NULL) {
		nowRecord = nowRecord->next;
		if (nowRecord == NULL || nowRecord->patientInfo.age != age ||
			strcmp(nowRecord->patientInfo.name, patientName) != 0)
			continue;
		printSingleRecordToUi(x, y, nowRecord);
		y += 25;
	}
	drawPrintRecordRefresh();
}

// ����ʱ�䷶Χ��ӡ
void printByTime(TimeRecord st, TimeRecord ed) {
	drawPrintRecordInit();
	DiagnosisRecord* nowRecord = DiagnosisRecordHead;
	int x = 30, y = 95;
	while (nowRecord != NULL) {
		nowRecord = nowRecord->next;
		if (nowRecord == NULL || !IsTimedRecord(nowRecord,
			st.month, st.day, st.hour, st.minute,
			ed.month, ed.day, ed.hour, ed.minute))
			continue;
		printSingleRecordToUi(x, y, nowRecord);
		y += 25;
	}
	drawPrintRecordRefresh();
}

void drawSearchMenu() { //�����ӽ��� -- ��ѯ�ض����Ƽ�¼

//��ʼ���ڵ�������Ϣ
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "����");//�������ִ�С ��ʽ 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextcolor(BLACK);

	setfillcolor(RGB(210, 210, 210));  //��ť��ɫ��ɫ

	fillrectangle(90, 88, 410, 118);
	fillrectangle(90, 148, 410, 178);
	fillrectangle(90, 208, 410, 238);
	fillrectangle(90, 268, 410, 298);

	fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
	fillrectangle(300, 640, 375, 660);

	settextstyle(15, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	outtextxy(190, 96, "��ѯ�������Ƽ�¼");
	outtextxy(190, 156, "��ѯҽ�����Ƽ�¼");
	outtextxy(190, 216, "��ѯ�������Ƽ�¼");
	outtextxy(175, 276, "��ѯĳ��ʱ�����Ƽ�¼");
	outtextxy(147, 642, "ȷ��");
	outtextxy(322, 642, "����");

	while (1) {
		m = GetMouseMsg();
		if (m.x >= 90 && m.x <= 410 && m.y >= 88 && m.y <= 118) { //����
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(90, 88, 410, 118);
			outtextxy(190, 96, "��ѯ�������Ƽ�¼");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[4];
				InputBox(buf, 3, "��������Һ���");
				if (LEGAL_DATA == IsSection(buf)) {
					//drawPrintRecord();
					printBySectionId(buf);
					clearrectangle(210, 40, 290, 60);
				}
				else {
					continue;
				}
			}
		}
		else if (m.x >= 90 && m.x <= 410 && m.y >= 148 && m.y <= 178) { //ҽ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(90, 148, 410, 178);
			outtextxy(190, 156, "��ѯҽ�����Ƽ�¼");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[6];
				InputBox(buf, 5, "������ҽ������");
				if (LEGAL_DATA == IsDoctorId(buf)) {
					printByDoctorId(buf);
					clearrectangle(210, 40, 290, 60);
				}
				else {
					continue;
				}
			}
		}
		else if (m.x >= 90 && m.x <= 410 && m.y >= 208 && m.y <= 238) { //����
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(90, 208, 410, 238);
			outtextxy(190, 216, "��ѯ�������Ƽ�¼");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf_Name[50];
				char buf_Age[5];
				InputBox(buf_Name, 41, "�����뻼������(20������)");
				InputBox(buf_Age, 4, "�����뻼������");
				if (LEGAL_DATA == IsName(buf_Name) && LEGAL_DATA == IsAge(buf_Age)) {
					printByPatient(buf_Name, buf_Age);
					clearrectangle(210, 40, 290, 60);
				}
				else {
					continue;
				}
			}
		}//fillrectangle(90, 268, 410, 298);
		else if (m.x >= 90 && m.x <= 410 && m.y >= 268 && m.y <= 298) { // ĳ��ʱ���¼
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(90, 268, 410, 298);
			outtextxy(175, 276, "��ѯĳ��ʱ�����Ƽ�¼");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf_stTime[50], buf_edTime[50];
				InputBox(buf_stTime, 9, "����������ʱ��,��ʽΪ����ʱ��,��Ϊ��λ��");
				InputBox(buf_edTime, 9, "����������ʱ��,��ʽΪ����ʱ��,��Ϊ��λ��");
				if (!IsDate(buf_stTime) || !IsDate(buf_edTime))continue;
				TimeRecord stTime, edTime;
				SetDate(buf_stTime, &stTime.month, &stTime.day, &stTime.hour, &stTime.minute);
				SetDate(buf_edTime, &edTime.month, &edTime.day, &edTime.hour, &edTime.minute);
				printByTime(stTime, edTime);
			}
		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //ȷ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "ȷ��");
			if (m.uMsg == WM_LBUTTONDOWN) {
				//Ч��ͬ����
				break;
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {  //����
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "����");
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}
		}
		else {
			setfillcolor(RGB(210, 210, 210));  //��ɫ
			settextstyle(15, 0, "����");

			fillrectangle(90, 88, 410, 118);
			fillrectangle(90, 148, 410, 178);
			fillrectangle(90, 208, 410, 238);
			fillrectangle(90, 268, 410, 298);

			fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
			fillrectangle(300, 640, 375, 660);

			outtextxy(190, 96, "��ѯ�������Ƽ�¼");
			outtextxy(190, 156, "��ѯҽ�����Ƽ�¼");
			outtextxy(190, 216, "��ѯ�������Ƽ�¼");
			outtextxy(175, 276, "��ѯĳ��ʱ�����Ƽ�¼");
			outtextxy(147, 642, "ȷ��");
			outtextxy(322, 642, "����");
		}
	}
}

void printData(char* buf, DiagnosisRecord* res) {
	//�ȴ��������ҵ���Ӧ�Ľڵ㸳ֵ��res,Ȼ���ٴ�ӡ

	char cache[100];
	clearrectangle(150, 80, 290, 100);  // ��������
	outtextxy(150, 80, res->patientInfo.name);
	sprintf(cache, "%d", res->patientInfo.age);
	clearrectangle(150, 110, 290, 130); // ��������
	outtextxy(150, 110, cache);
	clearrectangle(150, 140, 290, 160); // ҽ������
	outtextxy(150, 140, res->doctorInfo.name);
	sprintf(cache, "%s", doctorType[res->doctorInfo.level]);
	clearrectangle(150, 170, 290, 190); // ҽ������
	outtextxy(150, 170, cache);
	sprintf(cache, "%d", res->doctorInfo.sectionId);
	clearrectangle(150, 200, 290, 220); // ҽ������
	outtextxy(150, 200, cache);
	sprintf(cache, "%d", res->doctorInfo.id);
	clearrectangle(150, 230, 290, 250); // ҽ������
	outtextxy(150, 230, cache);
	sprintf(cache, "%02d%02d%02d%02d", res->recordTime.month, res->recordTime.day,
		res->recordTime.hour, res->recordTime.minute);
	clearrectangle(150, 260, 290, 280); //��������
	outtextxy(150, 260, cache);
	if (res->diagnosisSituation.setFlag == 2) {
		char buf_CDate[10];
		char buf_LDate[10];
		char buf_Cost[10];
		InHospitalRecord* temp = &(res->diagnosisSituation.
			diagnosisSituationInfo.inHospitalRecord);
		sprintf(buf_Cost, "%d", temp->deposit);
		sprintf(buf_CDate, "%02d%02d%02d%02d",
			temp->hospitalizedDate.month, temp->hospitalizedDate.day,
			temp->hospitalizedDate.hour, temp->hospitalizedDate.minute);
		sprintf(buf_LDate, "%02d%02d%02d%02d",
			temp->leaveDate.month, temp->leaveDate.day,
			temp->leaveDate.hour, temp->leaveDate.minute);
		clearrectangle(30, 320, 450, 600);
		settextstyle(20, 0, "����");
		outtextxy(30, 320, "��Ժ���ڣ�");
		outtextxy(30, 350, "��Ժ���ڣ�");
		outtextxy(30, 380, "�����ܺͣ�");
		settextstyle(15, 0, "����");
		outtextxy(150, 320, buf_CDate);
		outtextxy(150, 350, buf_LDate);
		outtextxy(150, 380, buf_Cost);
		setfillcolor(RGB(10, 250, 10));
		fillrectangle(152, 297, 163, 308);
		setfillcolor(RGB(210, 210, 210));
	}
	else if (res->diagnosisSituation.setFlag == 1) {
		//���ҩƷ�д�����
		setfillcolor(RGB(10, 250, 10));
		fillrectangle(242, 297, 253, 308);
		setfillcolor(RGB(210, 210, 210));
		PrescribeRecord * temp = &res->diagnosisSituation.diagnosisSituationInfo.prescribeRecord;
		SingleCost sum = temp->totalCost;
		int cnt = temp->typeNumber;

		PrescribeInfo * res = temp->prescribeInfoHead->next;
		int x = 30;
		int y = 350;
		while (cnt--)
		{
			char buf_id[10];
			itoa(res->drugId, buf_id, 10);
			outtextxy(x, y, buf_id);
			char buf_num[20];
			itoa(res->drugNumber, buf_num, 10);
			outtextxy(x + 200, y, buf_num);

			char temp_t[10];
			itoa(drugPriceList[res->drugId] * res->drugNumber, temp_t, 10);
			outtextxy(x + 300, y, temp_t);

			y += 30;
			res = res->next;
		}
		char buf_cost[20];
		strcpy_s(buf_cost, convertSingleCostToString(sum));
		outtextxy(x + 100, y + 30, "�ϼƣ�");
		outtextxy(x + 200, y + 30, buf_cost);
	}
	else if (res->diagnosisSituation.setFlag == 0) {
		//�������д�����
		setfillcolor(RGB(10, 250, 10));
		fillrectangle(332, 297, 343, 308);
		setfillcolor(RGB(210, 210, 210));
		CheckRecord * temp = &res->diagnosisSituation.diagnosisSituationInfo.checkRecord;
		int cnt = temp->typeNumber;
		SingleCost sum = temp->totalCost;
		CheckInfo * res = temp->checkInfoHead->next;
		int x = 30;
		int y = 350;
		while (cnt--)
		{
			char buf_id[10];
			itoa(res->checkId, buf_id, 10);
			outtextxy(x, y, buf_id);
			char buf_cost[20];
			strcpy_s(buf_cost, convertSingleCostToString(res->singleCost));
			outtextxy(x + 200, y, buf_cost);
			y += 30;
			res = res->next;
		}
		char buf_cost[20];
		strcpy_s(buf_cost, convertSingleCostToString(sum));
		outtextxy(x + 100, y + 30, "�ϼƣ�");
		outtextxy(x + 200, y + 30, buf_cost);

	}
	else {
		fillrectangle(330, 295, 345, 310);
	}
}

void drawUpdateMenu() { //�����ӽ���--�޸� һ�����Ƽ�¼

	DiagnosisRecord* res = initDiagnosisRecord();
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "����");//�������ִ�С ��ʽ 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextcolor(BLACK);
	outtextxy(30, 50, "�Һź��룺");
	outtextxy(30, 80, "����������");
	outtextxy(30, 110, "�������䣺");
	outtextxy(30, 140, "ҽ��������");
	outtextxy(30, 170, "ҽ������");
	outtextxy(30, 200, "ҽ�����ң�");
	outtextxy(30, 230, "ҽ�����ţ�");
	outtextxy(30, 260, "�������ڣ�");
	outtextxy(30, 290, "�������ͣ�");

	setfillcolor(RGB(210, 210, 210));  //��ť��ɫ��ɫ

	fillrectangle(300, 50, 380, 70);
	fillrectangle(300, 80, 380, 100);
	fillrectangle(300, 110, 380, 130);
	fillrectangle(300, 140, 380, 160);
	fillrectangle(300, 170, 380, 190);
	fillrectangle(300, 200, 380, 220);
	fillrectangle(300, 230, 380, 250);

	fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
	fillrectangle(300, 640, 375, 660);

	fillrectangle(150, 295, 165, 310);  //��������ѡ���־
	fillrectangle(240, 295, 255, 310);
	fillrectangle(330, 295, 345, 310);



	outtextxy(170, 290, "סԺ");  //��������text
	outtextxy(260, 290, "��ҩ");
	outtextxy(350, 290, "���");

	settextstyle(15, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	outtextxy(325, 53, "��ѯ");
	outtextxy(325, 83, "�޸�");
	outtextxy(325, 113, "�޸�");
	outtextxy(325, 143, "�޸�");
	outtextxy(325, 173, "�޸�");
	outtextxy(325, 203, "�޸�");
	outtextxy(325, 233, "�޸�");
	outtextxy(325, 263, "�޸�");
	outtextxy(147, 642, "ȷ��");
	outtextxy(322, 642, "����");
	int flag = -1;
	SingleCost past = constructSingleCost(0, 0, 0);
	SingleCost now = constructSingleCost(0, 0, 0);
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 50 && m.y <= 70) {  //�Һź���
			clearrectangle(300, 50, 380, 70);
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 50, 380, 70);
			outtextxy(325, 53, "��ѯ");

			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[8];
				InputBox(buf, 8, "������7λ�Һź���");
				if (LEGAL_DATA == IsRegisterId(buf)) {
					clearrectangle(150, 50, 290, 70);  //ˢ����ʾ����
					outtextxy(150, 50, buf);
					if (res) freeDiagnosisRecord(res);
					res = findModifiedNode(DiagnosisRecordHead, atoi(buf));
					if (res) {
						printData(buf, res);//��Ҫ�޸ĵ����Ƽ�¼��ʾȫ������
						switch (res->diagnosisSituation.setFlag) {
						case 0:
							past = res->diagnosisSituation.diagnosisSituationInfo.checkRecord.totalCost;
							flag = 0;
							break;
						case 1:
							past = res->diagnosisSituation.diagnosisSituationInfo.prescribeRecord.totalCost;
							flag = 1;
							break;
						case 2:
							past = res->diagnosisSituation.diagnosisSituationInfo.inHospitalRecord.costByNow;
							flag = 2;
							break;
						default:
							break;
						}
					}
				}
				else {
					continue;
				}
			}
		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 80 && m.y <= 100) {  //��������
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 80, 380, 100);
			outtextxy(325, 83, "�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[50];
				InputBox(buf, 41, "�����뻼������(20������)");
				if (LEGAL_DATA == IsName(buf)) {
					strcpy(res->patientInfo.name, buf);  // �洢���ڴ�
					clearrectangle(150, 80, 290, 100);  // ˢ����ʾ����
					outtextxy(150, 80, buf);  //��ʾ

				}
				else {
					continue;
				}

			}
		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 110 && m.y <= 130) {  //��������
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 110, 380, 130);
			outtextxy(325, 113, "�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[5];
				InputBox(buf, 4, "�����뻼������");
				if (LEGAL_DATA == IsAge(buf)) {
					res->patientInfo.age = atoi(buf);
					clearrectangle(150, 110, 290, 130);
					outtextxy(150, 110, buf);

				}
				else {
					continue;
				}

			}
		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 140 && m.y <= 160) {  //ҽ������
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 140, 380, 160);
			outtextxy(325, 143, "�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[50];
				InputBox(buf, 41, "������ҽ������(20������)");
				if (LEGAL_DATA == IsName(buf)) {
					strcpy(res->doctorInfo.name, buf);  // �洢���ڴ�
					clearrectangle(150, 140, 290, 160);  // ˢ����ʾ����
					outtextxy(150, 140, buf);  //��ʾ

				}
				else {
					continue;
				}

			}

		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 170 && m.y <= 190) {  //ҽ������
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 170, 380, 190);
			outtextxy(325, 173, "�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[2];
				InputBox(buf, 2, "������ҽ������");
				if (LEGAL_DATA == IsDoctorLevel(buf)) {
					res->doctorInfo.level = atoi(buf);
					clearrectangle(150, 170, 290, 190);
					outtextxy(150, 170, buf);  //��ʾ

				}
				else {
					continue;
				}

			}
		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 200 && m.y <= 220) {  //ҽ������
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 200, 380, 220);
			outtextxy(325, 203, "�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[4];
				InputBox(buf, 3, "������ҽ������");
				if (LEGAL_DATA == IsSection(buf)) {
					res->doctorInfo.sectionId = atoi(buf);
					clearrectangle(150, 200, 290, 220);
					outtextxy(150, 200, buf);

				}
				else {
					continue;
				}

			}


		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 230 && m.y <= 250) {  //ҽ������
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 230, 380, 250);
			outtextxy(325, 233, "�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[6];
				InputBox(buf, 5, "������ҽ������");
				if (LEGAL_DATA == IsDoctorId(buf)) {
					res->doctorInfo.id = atoi(buf);
					clearrectangle(150, 230, 290, 250);
					outtextxy(150, 230, buf);

				}
				else {
					continue;
				}

			}


		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 260 && m.y <= 280) {  //�������ڣ���ʼ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 260, 380, 280);
			outtextxy(325, 263, "�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[10];
				InputBox(buf, 9, "��������������");
				if (LEGAL_DATA == IsDate(buf)) {
					SetDate(buf, &(res->recordTime.month), &(res->recordTime.day),
						&(res->recordTime.hour), &(res->recordTime.minute));
					clearrectangle(150, 260, 290, 280);
					outtextxy(150, 260, buf);

				}
				else {
					continue;
				}

			}
		}
		else if (m.x >= 150 && m.x <= 165 && m.y >= 295 && m.y <= 310) {  //סԺ
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(152, 297, 163, 308);
			if (m.uMsg == WM_LBUTTONDOWN) {
				freeDiagnosisSituation(res);
				res->diagnosisSituation.setFlag = 2;
				char buf_CDate[10];
				char buf_LDate[10];
				char buf_Cost[10];
				InputBox(buf_CDate, 9, "��������Ժ����");
				InputBox(buf_LDate, 9, "�������Ժ����");
				InputBox(buf_Cost, 9, "����������ܺ�");
				if (LEGAL_DATA == IsDate(buf_CDate) &&
					LEGAL_DATA == IsDate(buf_LDate) &&
					LEGAL_DATA == IsCost(buf_Cost)) {
					InHospitalRecord* temp = &(res->diagnosisSituation.
						diagnosisSituationInfo.inHospitalRecord);
					temp->costByNow = StrToCost(buf_Cost);
					SetDate(buf_CDate, &(temp->hospitalizedDate.month)
						, &(temp->hospitalizedDate.day)
						, &(temp->hospitalizedDate.hour)
						, &(temp->hospitalizedDate.minute)
					);
					SetDate(buf_LDate, &(temp->leaveDate.month)
						, &(temp->leaveDate.day)
						, &(temp->leaveDate.hour)
						, &(temp->leaveDate.minute)
					);
					clearrectangle(30, 320, 450, 600);
					settextstyle(20, 0, "����");
					outtextxy(30, 320, "��Ժ���ڣ�");
					outtextxy(30, 350, "��Ժ���ڣ�");
					outtextxy(30, 380, "�����ܺͣ�");
					settextstyle(15, 0, "����");
					outtextxy(150, 320, buf_CDate);
					outtextxy(150, 350, buf_LDate);
					outtextxy(150, 380, buf_Cost);
				}
			}

		}
		else if (m.x >= 240 && m.x <= 255 && m.y >= 295 && m.y <= 310) {  //��ҩ
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(242, 297, 253, 308);
			if (m.uMsg == WM_LBUTTONDOWN) {
				freeDiagnosisSituation(res);
				res->diagnosisSituation.setFlag = 1;
				char buf_num[3];
				InputBox(buf_num, 2, "������ҩƷ������");
				if (LEGAL_DATA == IsDrugKindNum(buf_num)) {
					now.yuan = 0;
					clearrectangle(30, 320, 450, 600);
					settextstyle(20, 0, "����");
					outtextxy(30, 320, "ҩƷ���");
					outtextxy(130, 320, "ҩƷ��Ŀ");
					outtextxy(230, 320, "ҩƷ����");
					outtextxy(330, 320, "ҩƷ����");
					int x = 30;
					int y = 350;

					int num = atoi(buf_num);
					PrescribeInfo* head = (PrescribeInfo*)malloc(sizeof(PrescribeInfo));
					head->next = NULL;
					PrescribeInfo* rear = head;
					//PrescribeInfo* temp = head;
					for (int i = 0; i < num; i++) {
						char buf_DrugId[3];
						char buf_DrugNum[4];
						InputBox(buf_DrugId, 3, "������ҩƷ���");
						InputBox(buf_DrugNum, 4, "������ҩƷ����");
						if (LEGAL_DATA == IsDrugId(buf_DrugId) &&
							LEGAL_DATA == IsDrugNum(buf_DrugNum)) {
							outtextxy(x, y, buf_DrugId);
							outtextxy(x + 100, y, buf_DrugNum);

							char temp_p[10];
							itoa(drugPriceList[atoi(buf_DrugId)], temp_p, 10);
							outtextxy(x + 200, y, temp_p);

							char temp_t[10];
							itoa(drugPriceList[atoi(buf_DrugId)] * atoi(buf_DrugNum), temp_t, 10);
							outtextxy(x + 300, y, temp_t);

							y += 30;
							now.yuan += drugPriceList[atoi(buf_DrugId)] * atoi(buf_DrugNum);

							rear->next = (PrescribeInfo*)malloc(sizeof(PrescribeInfo));
							rear->next->next = NULL;
							rear->next->drugId = atoi(buf_DrugId);
							rear->next->drugNumber = atoi(buf_DrugNum);
							rear = rear->next;
						}
						else {
							i--;
						}
					}
					
					res->diagnosisSituation.diagnosisSituationInfo
						.prescribeRecord.typeNumber = atoi(buf_num);
					res->diagnosisSituation.diagnosisSituationInfo
						.prescribeRecord.prescribeInfoHead = head;


				}


			}

		}
		else if (m.x >= 330 && m.x <= 345 && m.y >= 295 && m.y <= 310) {  //���
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(332, 297, 343, 308);
			if (m.uMsg == WM_LBUTTONDOWN) {
				freeDiagnosisSituation(res);
				res->diagnosisSituation.setFlag = 0;
				char buf_num[3];
				InputBox(buf_num, 3, "��������������");
				if (LEGAL_DATA == IsDrugKindNum(buf_num)) {
					now.yuan = 0;
					clearrectangle(30, 320, 450, 600);
					settextstyle(20, 0, "����");
					outtextxy(30, 320, "�����");
					outtextxy(230, 320, "������");

					int x = 30;
					int y = 350;
					int num = atoi(buf_num);
					CheckInfo* head = (CheckInfo*)malloc(sizeof(CheckInfo));
					CheckInfo* rear = head;
					head->next = NULL;
					for (int i = 0; i < num; i++) {
						char buf_CheckId[3];
						InputBox(buf_CheckId, 3, "����������");
						if (LEGAL_DATA == IsDrugId(buf_CheckId)) {
							outtextxy(x, y, buf_CheckId);

							char temp_t[10];
							itoa(drugPriceList[atoi(buf_CheckId)], temp_t, 10);
							now.yuan += drugPriceList[atoi(buf_CheckId)];
							outtextxy(x + 200, y, temp_t);
							y += 30;
							rear->next = (CheckInfo*)malloc(sizeof(CheckInfo));
							rear->next->next = NULL;
							rear->next->checkId = atoi(buf_CheckId);
							rear->next->singleCost = constructSingleCost(temp_t);
							rear = rear->next;
						}
						else {
							i--;
						}

					}

					res->diagnosisSituation.diagnosisSituationInfo
						.checkRecord.typeNumber = atoi(buf_num);
					res->diagnosisSituation.diagnosisSituationInfo
						.checkRecord.checkInfoHead = head;

				}

			}

		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //ȷ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "ȷ��");
			if (m.uMsg == WM_LBUTTONDOWN) {
				switch (flag) {
				case 0:
					hospitalFund.checkCost.yuan -= past.yuan;
					hospitalFund.checkCost.jiao -= past.jiao;
					hospitalFund.checkCost.fen -= past.fen;
				case 1:
					hospitalFund.drugCost.yuan -= past.yuan;
					hospitalFund.drugCost.jiao -= past.jiao;
					hospitalFund.drugCost.fen -= past.fen;
					break;
				case 2:
					hospitalFund.inHosipitalCost.yuan -= past.yuan;
					hospitalFund.inHosipitalCost.jiao -= past.jiao;
					hospitalFund.inHosipitalCost.fen -= past.fen;
					break;
				default:
					break;
				}
				hospitalFund.allCost.yuan -= past.yuan;
				hospitalFund.allCost.jiao -= past.jiao;
				hospitalFund.allCost.fen -= past.fen;
				switch (res->diagnosisSituation.setFlag){
				case 0:
					hospitalFund.checkCost.yuan += now.yuan;
					hospitalFund.checkCost.jiao += now.jiao;
					hospitalFund.checkCost.fen += now.fen;
				case 1:
					hospitalFund.drugCost.yuan += now.yuan;
					hospitalFund.drugCost.jiao += now.jiao;
					hospitalFund.drugCost.fen += now.fen;
					break;
				case 2:
					hospitalFund.inHosipitalCost.yuan += now.yuan;
					hospitalFund.inHosipitalCost.jiao += now.jiao;
					hospitalFund.inHosipitalCost.fen += now.fen;
					break;
				default:
					break;
				}
				hospitalFund.allCost.yuan += now.yuan;
				hospitalFund.allCost.jiao += now.jiao;
				hospitalFund.allCost.fen += now.fen;
				break;
			}

		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {  //����
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "����");
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}

		}
		else {
			setfillcolor(RGB(210, 210, 210));  //��ɫ
			settextstyle(15, 0, "����");

			fillrectangle(300, 50, 380, 70);
			fillrectangle(300, 80, 380, 100);
			fillrectangle(300, 110, 380, 130);
			fillrectangle(300, 140, 380, 160);
			fillrectangle(300, 170, 380, 190);
			fillrectangle(300, 200, 380, 220);
			fillrectangle(300, 230, 380, 250);
			fillrectangle(300, 260, 380, 280);
			fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
			fillrectangle(300, 640, 375, 660);

			outtextxy(325, 53, "��ѯ");
			outtextxy(325, 83, "�޸�");
			outtextxy(325, 113, "�޸�");
			outtextxy(325, 143, "�޸�");
			outtextxy(325, 173, "�޸�");
			outtextxy(325, 203, "�޸�");
			outtextxy(325, 233, "�޸�");
			outtextxy(325, 263, "�޸�");
			outtextxy(147, 642, "ȷ��");
			outtextxy(322, 642, "����");


			if (res) {
				if (2 == res->diagnosisSituation.setFlag) { //סԺ
					setfillcolor(RGB(10, 250, 10));
					fillrectangle(152, 297, 163, 308);
					setfillcolor(RGB(210, 210, 210));
				}
				else {
					fillrectangle(150, 295, 165, 310);
				}
				if (1 == res->diagnosisSituation.setFlag) { //��ҩ
					setfillcolor(RGB(10, 250, 10));
					fillrectangle(242, 297, 253, 308);
					setfillcolor(RGB(210, 210, 210));
				}
				else {
					fillrectangle(240, 295, 255, 310);
				}
				if (0 == res->diagnosisSituation.setFlag) { //���
					setfillcolor(RGB(10, 250, 10));
					fillrectangle(332, 297, 343, 308);
					setfillcolor(RGB(210, 210, 210));
				}
				else {
					fillrectangle(330, 295, 345, 310);
				}
			}
		}

	}
}