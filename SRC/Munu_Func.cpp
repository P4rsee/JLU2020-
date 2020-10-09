#pragma once
#include"DrawMunu.h"
#include"DiagnosisMessage.h"
#include"ListOperator.h"
#include"DoctorInfoProcessor.h"
#include"global.h"

//���˵�---->סԺ����
void drawInHospitalPatient() {
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "����");//�������ִ�С ��ʽ 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextcolor(BLACK);

	outtextxy(210, 15, "סԺ����");
	outtextxy(40, 50, "�Һ�");
	outtextxy(100, 50, "��������");
	outtextxy(200, 50, "����");
	outtextxy(265, 50, "Ԥ��Ժʱ��");
	outtextxy(390, 50, "Ѻ��");

	setfillcolor(RGB(210, 210, 210));  //��ť��ɫ��ɫ
	fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
	fillrectangle(300, 640, 375, 660);

	settextstyle(15, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	outtextxy(147, 642, "ȷ��");
	outtextxy(322, 642, "����");

	DiagnosisRecord* nowRecord = DiagnosisRecordHead->next;
	int sx = 30, y = 80;
	while (nowRecord != NULL) {
		if (!IsInHospital(nowRecord)) {
			nowRecord = nowRecord->next; continue;
		}
		char buf[100]; int x = sx;
		settextstyle(15, 0, "����");
		sprintf(buf, "%07d", nowRecord->patientInfo.registerId);
		outtextxy(x, y, buf);

		settextstyle(18, 0, "����");
		x = x + 85;
		outtextxy(x, y, nowRecord->patientInfo.name);
		x = x + 95;
		sprintf(buf, "%d", nowRecord->patientInfo.age);
		outtextxy(x, y, buf);
		x = x + 60;
		TimeRecord p_time = nowRecord->diagnosisSituation.
			diagnosisSituationInfo.inHospitalRecord.predictedLeaveDate;
		sprintf(buf, "%02d-%02d %02d:%02d",
			p_time.month, p_time.day, p_time.hour, p_time.hour);
		settextstyle(15, 0, "����");
		outtextxy(x, y, buf);
		x = x + 110;
		sprintf(buf, "%d.00", nowRecord->diagnosisSituation.
			diagnosisSituationInfo.inHospitalRecord.deposit.yuan);
		outtextxy(x, y, buf);

		y += 25;
		nowRecord = nowRecord->next;
	}

	while (1) {
		m = GetMouseMsg();
		if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //ȷ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "ȷ��");
			if (m.uMsg == WM_LBUTTONDOWN) {

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

			fillrectangle(125, 640, 200, 660);  //���غ��޸�
			fillrectangle(300, 640, 375, 660);

			outtextxy(147, 642, "ȷ��");
			outtextxy(322, 642, "����");

		}
	}
}
//���˵�---->ҽԺӪҵ��
void drawHospitalIncome() {
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "����");//�������ִ�С ��ʽ 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextcolor(BLACK);
	//outtextxy(40, 40, "�������");
	//outtextxy(200, 40, "ҩƷ����");
	//outtextxy(360, 40, "סԺ����");
	outtextxy(65, 60, "�������:");
	outtextxy(65, 110, "ҩƷ����:");
	outtextxy(65, 160, "סԺ����:");
	outtextxy(65, 210, "ȫ������:");

	FundPushUp();
	outtextxy(200, 60, hospitalFund.stringOfCheck);
	outtextxy(200, 110, hospitalFund.stringOfDrug);
	outtextxy(200, 160, hospitalFund.stringOfInHospital);
	outtextxy(200, 210, hospitalFund.stringOfAll);

	setfillcolor(RGB(210, 210, 210));  //��ť��ɫ��ɫ
	fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
	fillrectangle(300, 640, 375, 660);

	settextstyle(15, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	outtextxy(147, 642, "ȷ��");
	outtextxy(322, 642, "����");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //ȷ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "ȷ��");
			if (m.uMsg == WM_LBUTTONDOWN) {

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

			fillrectangle(125, 640, 200, 660);  //���غ��޸�
			fillrectangle(300, 640, 375, 660);

			outtextxy(147, 642, "ȷ��");
			outtextxy(322, 642, "����");

		}
	}

}
//���˵�---->��λ���
void drawBedSituation() {
abcd:;
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "����");//�������ִ�С ��ʽ 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextcolor(BLACK);
	outtextxy(40, 40, "��������");
	outtextxy(200, 40, "��������");
	outtextxy(360, 40, "ռ�����");

	setfillcolor(RGB(210, 210, 210));  //��ť��ɫ��ɫ
	fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
	fillrectangle(300, 640, 375, 660);

	settextstyle(15, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	outtextxy(147, 642, "�޸�");
	outtextxy(322, 642, "����");
	int y = 70;
	int x = 40;
	Ward* temp = WardHead->next;
	char buf_wid[6];
	char buf_occu[3];
	char buf_total[3];
	while (temp) {
		itoa(temp->wardId, buf_wid, 10);
		outtextxy(x+30, y, buf_wid);
		outtextxy(x + 160, y, nursingType[temp->nursingType]);
		outtextxy(x + 190, y, bedType[temp->bedType]);
		itoa(temp->occupiedBedNum, buf_occu, 10);
		itoa(temp->totalBedNum, buf_total, 10);
		outtextxy(x + 330, y, buf_occu);
		outtextxy(x + 345, y, "/");
		outtextxy(x + 360, y, buf_total);
		temp = temp->next;
		y += 30;
	}
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //�޸�
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "�޸�");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf_wid[8];
				char buf_ntype[8];
				char buf_btype[8];
				char buf_bed[3];
				InputBox(buf_wid,3,"�����벡������(��λ����,����)");
				InputBox(buf_ntype, 2, "�����뻤������(���⣺1  ��ͨ��2)");
				InputBox(buf_btype, 2, "�����벡��λ��(1,2,3)");
				InputBox(buf_bed, 2, "���������Ӵ�λ��");
				if (LEGAL_DATA == IsWardId(buf_wid)
					&& LEGAL_DATA == IsOneDigitNumber(buf_ntype)
					&& LEGAL_DATA == IsOneDigitNumber(buf_btype)
					&& LEGAL_DATA == IsOneDigitNumber(buf_bed)) {
					Ward * res = modifyWard(WardHead,atoi(buf_wid));
					if (res){
						res->nursingType = atoi(buf_ntype);
						res->bedType = atoi(buf_btype);
						int pos = res->totalBedNum;
						res->totalBedNum += atoi(buf_bed);
						for (int i = pos; i < res->totalBedNum; i++){
							res->bedSituation[i] = 0;
						}
						InputBox(buf_bed, 2, "�޸ĳɹ���");
					}
					else {
						InputBox(buf_bed, 2, "δ�鵽�˲�����");
					}
					
				}
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

			fillrectangle(125, 640, 200, 660);  //���غ��޸�
			fillrectangle(300, 640, 375, 660);

			
			outtextxy(147, 642, "�޸�");
			outtextxy(322, 642, "����");

		}
	}

}
//���˵�---->���߾���
void drawPatientToTreat() {
abcd:;
	MOUSEMSG m;
	initgraph(800, 600);
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(LIGHTBLUE);
	fillrectangle(200, 140, 600, 160);
	fillrectangle(200, 200, 600, 220);
	fillrectangle(200, 260, 600, 280);
	fillrectangle(200, 320, 600, 340);
	fillrectangle(200, 380, 600, 400);
	fillrectangle(200, 440, 600, 460);

	settextstyle(15, 0, "����");//�������ִ�С ��ʽ 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	outtextxy(250, 142, "��Ҫ�Һ�");
	outtextxy(250, 202, "��Ҫ��ҩ");
	outtextxy(250, 262, "��Ҫ���");
	outtextxy(250, 322, "��ҪסԺ");
	outtextxy(250, 382, "��Ҫ��Ժ");
	outtextxy(250, 442, "�������˵�");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 200 && m.x <= 600 && m.y >= 140 && m.y <= 160) {
			setlinecolor(RED);//����� �����µı߿�Ϊ��ɫ
			rectangle(190, 135, 610, 165);//���µı߿�
			//�������� ��Ҫ�Һ�
			if (m.uMsg == WM_LBUTTONDOWN) {
				//���ɹҺŽ��棬��д�������䣬����ʲô���ң� �Һź����Զ����ɲ�������ʾ����
				drawToRegister();
				goto abcd;//����ʵ�ֺ� ��ת�� �ͷ
			}
		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 200 && m.y <= 220) {
			setlinecolor(RED);
			rectangle(190, 195, 610, 225);
			//�������� ��Ҫ��ҩ
			if (m.uMsg == WM_LBUTTONDOWN) {
				//���ɿ�ҩ���棬���û��������Լ��ĹҺź��룬������Ϸ���¼��ҩ��
				drawToPrescribe();
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 260 && m.y <= 280) {
			setlinecolor(RED);
			rectangle(190, 255, 610, 285);
			//����� ��Ҫ���
			if (m.uMsg == WM_LBUTTONDOWN) {
				//���ɼ����棬���û��������Լ��ĹҺź��룬������Ϸ�����д��鱨��
				drawToCheck();
				goto abcd;
			}


		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 320 && m.y <= 340) {
			setlinecolor(RED);
			rectangle(190, 315, 610, 345);
			//����� ��ҪסԺ
			if (m.uMsg == WM_LBUTTONDOWN) {
				//����סԺ���棬���û��������Լ��ĹҺź��룬������Ϸ�����д��Ժ/������Ժ����/Ѻ��
				drawToHospital();
				goto abcd;
			}

		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 380 && m.y <= 400) {
			setlinecolor(RED);
			rectangle(190, 375, 610, 405);
			//����� ��Ҫ��Ժ
			if (m.uMsg == WM_LBUTTONDOWN) {
				//���ɳ�Ժ���棬���û��������Լ��ĹҺź��룬������Ϸ��󣬣����Ժ���ڣ���¼ת����ʷtxt���˻�Ѻ��
				drawOutHospital();
				goto abcd;
			}

		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 440 && m.y <= 460) {
			setlinecolor(RED);
			rectangle(190, 435, 610, 465);
			//����� �������˵�
			if (m.uMsg == WM_LBUTTONDOWN) {


				break;
			}

		}
		else {
			setlinecolor(WHITE);
			rectangle(190, 135, 610, 165);
			rectangle(190, 195, 610, 225);
			rectangle(190, 255, 610, 285);
			rectangle(190, 315, 610, 345);
			rectangle(190, 375, 610, 405);
			rectangle(190, 435, 610, 465);
		}
	}

}
//���˵�---->סԺ�ɷ�(Ѻ��)
void drawToHandDeposit() 
{
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	char buf[8];
	DiagnosisRecord* res = NULL;
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
	outtextxy(30, 260, "���ٽɷѣ�");
	setfillcolor(RGB(210, 210, 210));  //��ť��ɫ��ɫ

	fillrectangle(300, 50, 380, 70);
	fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(305, 53, "���/�޸�");
	outtextxy(147, 642, "ȷ��");
	outtextxy(322, 642, "����");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 50 && m.y <= 70) {  //�Һź���
			clearrectangle(300, 50, 380, 70);
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 50, 380, 70);
			settextstyle(15, 0, "����");
			outtextxy(305, 53, "���/�޸�");

			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[8];
				InputBox(buf, 8, "������7λ�Һź���");
				res = findModifiedNode(DiagnosisRecordHead, atoi(buf));
				if (res) {
					clearrectangle(150, 50, 290, 280);				//ˢ����ʾ����
					outtextxy(150, 50, buf);
					outtextxy(150, 80, res->patientInfo.name);		//��������
					char buf_age[4];
					itoa(res->patientInfo.age, buf_age, 10);
					outtextxy(150, 110, buf_age);					//��������
					outtextxy(150, 140, res->doctorInfo.name);		//ҽ������
					char buf_leval[2];
					itoa(res->doctorInfo.level, buf_leval, 10);
					outtextxy(150, 170, doctorType[res->doctorInfo.level]);					//ҽ������
					char buf_section[3];
					itoa(res->doctorInfo.sectionId, buf_section, 10);
					outtextxy(150, 200, buf_section);				//ҽ������
					char buf_Doctorid[6];
					itoa(res->doctorInfo.id, buf_Doctorid, 10);
					outtextxy(150, 230, buf_Doctorid);				//ҽ������
					char buf_CDate[20];
					char buf_PLDate[21];
					char buf_Deposit[20];
					InHospitalRecord*temp = &(res->diagnosisSituation.
						diagnosisSituationInfo.inHospitalRecord);
					sprintf(buf_PLDate, "%d��%d��%d��%d��"
							, temp->predictedLeaveDate.month
							, temp->predictedLeaveDate.day
							, temp->predictedLeaveDate.hour
							, temp->predictedLeaveDate.minute
						);
						//��Ժ����
						sprintf(buf_CDate, "%d��%d��%d��%d��"
							, temp->hospitalizedDate.month
							, temp->hospitalizedDate.day
							, temp->hospitalizedDate.hour
							, temp->hospitalizedDate.minute
						);
					
					sprintf(buf_Deposit, "%dԪ%d��%d��"
							, temp->deposit.yuan
							, temp->deposit.jiao
							, temp->deposit.fen
						);
						clearrectangle(30, 320, 450, 600);
						settextstyle(20, 0, "����");
						outtextxy(30, 320, "��Ժ���ڣ�");
						outtextxy(10, 350, "Ԥ�Ƴ�Ժ���ڣ�");
						outtextxy(30, 380, "��ǰѺ��");
						settextstyle(15, 0, "����");
						outtextxy(150, 320, buf_CDate);
						outtextxy(150, 350, buf_PLDate);
						outtextxy(150, 380, buf_Deposit);
						InputBox(buf_Deposit, 10, "���������Ѻ����");
					if (LEGAL_DATA == IsDeposit(buf_Deposit)) {
						temp->deposit = costAdd(temp->deposit,constructSingleCost(buf_Deposit));
						clearrectangle(150, 380, 500, 400);
						sprintf(buf_Deposit, "%dԪ%d��%d��"
							, temp->deposit.yuan
							, temp->deposit.jiao
							, temp->deposit.fen
						);
						outtextxy(150, 380, buf_Deposit);
						continue;
					}
					
				}
			}
		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //ȷ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "ȷ��");
			if (m.uMsg == WM_LBUTTONDOWN) {
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

			fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
			fillrectangle(300, 640, 375, 660);

			outtextxy(305, 53, "���/�޸�");

			outtextxy(147, 642, "ȷ��");
			outtextxy(322, 642, "����");

		}

	}
}
//���߾���-->��Ҫ��Ժ
void drawOutHospital() {
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	//
	char buf[8];
	//DiagnosisRecord* res = NULL;
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
	setfillcolor(RGB(210, 210, 210));  //��ť��ɫ��ɫ

	fillrectangle(300, 50, 380, 70);
	fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(305, 53, "���/�޸�");
	outtextxy(147, 642, "ȷ��");
	outtextxy(322, 642, "����");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 50 && m.y <= 70) {  //�Һź���
			clearrectangle(300, 50, 380, 70);
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 50, 380, 70);
			settextstyle(15, 0, "����");
			outtextxy(305, 53, "���/�޸�");

			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[8];
				InputBox(buf, 8, "������7λ�Һź���");
				if (IsRegisterId(buf)) { //����					
					DiagnosisRecord* res =
						findModifiedNode(DiagnosisRecordHead, atoi(buf));
					clearrectangle(150, 50, 290, 280);				//ˢ����ʾ����
					outtextxy(150, 50, buf);
					outtextxy(150, 80, res->patientInfo.name);	//��������
					char buf_age[4];
					itoa(res->patientInfo.age, buf_age, 10);
					outtextxy(150, 110, buf_age);					//��������
					outtextxy(150, 140, res->doctorInfo.name);	//ҽ������
					char buf_leval[2];
					itoa(res->doctorInfo.level, buf_leval, 10);
					outtextxy(150, 170, doctorType[res->doctorInfo.level]);		//ҽ������
					char buf_section[3];
					itoa(res->doctorInfo.sectionId, buf_section, 10);
					outtextxy(150, 200, buf_section);				//ҽ������
					char buf_Doctorid[6];
					itoa(res->doctorInfo.id, buf_Doctorid, 10);
					outtextxy(150, 230, buf_Doctorid);			//ҽ������
					//��������
					char buf_date[30];
					sprintf(buf_date, "%d��%d�� %02d ��%02d",
						currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
					outtextxy(150, 260, buf_date);
					if (res->diagnosisSituation.setFlag == 2) {
						char buf_CDate[30];
						char buf_LDate[31];
						char buf_Deposit[30];
						//����ϲ��� ��Ϊ��ȡ��ǰʱ��
						InputBox(buf_LDate, 2, "ȷ��Ҫ��Ժ�𣿣��� 1��");
						if (1 == atoi(buf_LDate)) {
							//InputBox(buf_LDate, 9, "�������Ժ����:");
							//if (!IsDate(buf_LDate))continue;
							TimeRecord* timeRecord = &(res->diagnosisSituation.
								diagnosisSituationInfo.inHospitalRecord.predictedLeaveDate);
							timeRecord->month = timeRecord->day =
								timeRecord->hour = timeRecord->minute = -1;
							//if (LEGAL_DATA == IsDate(buf_LDate)) {
							InHospitalRecord*temp = &(res->diagnosisSituation.
								diagnosisSituationInfo.inHospitalRecord);
							temp->leaveDate = currentTime;
							
							sprintf(buf_CDate, "%d��%d��%d��%d��"
								, temp->hospitalizedDate.month
								, temp->hospitalizedDate.day
								, temp->hospitalizedDate.hour
								, temp->hospitalizedDate.minute
							);
							sprintf(buf_Deposit, "%dԪ%d��%d��"
								, temp->deposit.yuan
								, temp->deposit.jiao
								, temp->deposit.fen
							);
							sprintf(buf_LDate, "%d��%d��%d��%d��"
								, currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
							clearrectangle(30, 320, 450, 600);
							settextstyle(20, 0, "����");
							outtextxy(30, 320, "��Ժ���ڣ�");
							outtextxy(30, 350, "��Ժ���ڣ�");
							outtextxy(30, 380, "�˻�Ѻ��");
							settextstyle(15, 0, "����");
							outtextxy(150, 320, buf_CDate);
							outtextxy(150, 350, buf_LDate);
							outtextxy(150, 380, buf_Deposit);
							temp->deposit.yuan = temp->deposit.jiao
								= temp->deposit.fen = 0;
							int WardId = temp->sickBedNumber;
							int BedId = WardId % 100;
							WardId /= 100;
							//��Ժ���ˣ���λ�ÿ�
							freeWardBed(WardId,BedId);

						}
					}
				}
			}
		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //ȷ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "ȷ��");
			if (m.uMsg == WM_LBUTTONDOWN) {
				//ɾ��ԭ���������Ľ��
				//�ύ������㣬��������
				//return;
				break;  //����������free��res
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

			fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
			fillrectangle(300, 640, 375, 660);

			outtextxy(305, 53, "���/�޸�");

			outtextxy(147, 642, "ȷ��");
			outtextxy(322, 642, "����");

		}

	}
	//free(res);

}
//���߾���-->��ҪסԺ
void drawToHospital() {
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	//
	char buf[8];
	DiagnosisRecord* res = NULL;
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
	setfillcolor(RGB(210, 210, 210));  //��ť��ɫ��ɫ

	fillrectangle(300, 50, 380, 70);
	fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(305, 53, "���/�޸�");
	outtextxy(147, 642, "ȷ��");
	outtextxy(322, 642, "����");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 50 && m.y <= 70) {  //�Һź���
			clearrectangle(300, 50, 380, 70);
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 50, 380, 70);
			settextstyle(15, 0, "����");
			outtextxy(305, 53, "���/�޸�");

			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[8];
				InputBox(buf, 8, "������7λ�Һź���");
				
				if (IsRegisterId(buf)) { //����
					res = findModifiedNode(DiagnosisRecordHead, atoi(buf));		//����

					res->diagnosisSituation.setFlag = 2;
					clearrectangle(150, 50, 290, 280);					//ˢ����ʾ����
					outtextxy(150, 50, buf);
					outtextxy(150, 80, res->patientInfo.name);			//��������
					char buf_age[4];
					itoa(res->patientInfo.age, buf_age, 10);
					outtextxy(150, 110, buf_age);						//��������
					outtextxy(150, 140, res->doctorInfo.name);			//ҽ������
					char buf_leval[2];
					itoa(res->doctorInfo.level, buf_leval, 10);
					outtextxy(150, 170, doctorType[res->doctorInfo.level]);	//ҽ������
					char buf_section[3];
					itoa(res->doctorInfo.sectionId, buf_section, 10);
					outtextxy(150, 200, buf_section);					//ҽ������
					char buf_Doctorid[6];
					itoa(res->doctorInfo.id, buf_Doctorid, 10);
					outtextxy(150, 230, buf_Doctorid);					//ҽ������
					//��������
					char buf_date[30];
					sprintf(buf_date, "%d��%d�� %02d ��%02d",
						currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
					outtextxy(150, 260, buf_date);
					res->diagnosisSituation.setFlag = 2;
					char buf_CDate[30];
					char buf_PLDate[30];
					char buf_Deposit[30];
					//InputBox(buf_CDate, 9, "��������Ժ����");
					InputBox(buf_PLDate, 9, "������Ԥ�Ƴ�Ժ����");
					InputBox(buf_Deposit, 9, "��������ԺѺ��");
					if (LEGAL_DATA == IsDate(buf_PLDate) &&
						LEGAL_DATA == IsDeposit(buf_Deposit)) {
						InHospitalRecord*temp = &(res->diagnosisSituation.
							diagnosisSituationInfo.inHospitalRecord);
						temp->costByNow = StrToCost("0");			//����Ժ����ʼ������Ϊ 0
						temp->hospitalizedDate = currentTime;
						temp->deposit = StrToCost(buf_Deposit);
						SetDate(buf_PLDate, &(temp->predictedLeaveDate.month)
							, &(temp->predictedLeaveDate.day)
							, &(temp->predictedLeaveDate.hour)
							, &(temp->predictedLeaveDate.minute)
						);
						sprintf(buf_CDate, "%d��%d�� %02d : %02d"
							, currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
						sprintf(buf_PLDate, "%d��%d�� %02d : %02d"
							, temp->predictedLeaveDate.month
							, temp->predictedLeaveDate.day
							, temp->predictedLeaveDate.hour
							, temp->predictedLeaveDate.minute
						);
						getSickBedNum(res);
						
						clearrectangle(30, 320, 450, 600);
						settextstyle(20, 0, "����");
						outtextxy(30, 320, "��Ժ���ڣ�");
						outtextxy(30, 350, "Ԥ�Ƴ�Ժ��");
						outtextxy(30, 380, "����Ѻ��");
						outtextxy(30, 410, "��������:");
						settextstyle(15, 0, "����");
						outtextxy(150, 320, buf_CDate);
						outtextxy(150, 350, buf_PLDate);
						outtextxy(150, 380, buf_Deposit);
						char buf_bedNum[30];
						int WardId = res->diagnosisSituation.diagnosisSituationInfo.inHospitalRecord.sickBedNumber;
						int BedId = WardId % 100;
						WardId /= 100;
						sprintf(buf_bedNum, "%d�Ų��� %d�Ų���", WardId, BedId);
						outtextxy(150, 410, buf_bedNum);

					}
				}

			}
		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //ȷ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "ȷ��");
			if (m.uMsg == WM_LBUTTONDOWN) {
				//ɾ��ԭ���������Ľ��
				//�ύ������㣬��������
				//return;
				break;  //����������free��res
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

			fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
			fillrectangle(300, 640, 375, 660);

			outtextxy(305, 53, "���/�޸�");

			outtextxy(147, 642, "ȷ��");
			outtextxy(322, 642, "����");

		}

	}
	//free(res);

}
//���߾���-->��Ҫ���
void drawToCheck() {
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	//
	char buf[8];
	DiagnosisRecord* res = NULL;
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
	setfillcolor(RGB(210, 210, 210));  //��ť��ɫ��ɫ

	fillrectangle(300, 50, 380, 70);
	fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(305, 53, "���/�޸�");
	outtextxy(147, 642, "ȷ��");
	outtextxy(322, 642, "����");
	SingleCost temp;
	temp.yuan = 0;
	temp.jiao = 0;
	temp.fen = 0;
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 50 && m.y <= 70) {  //�Һź���
			clearrectangle(300, 50, 380, 70);
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 50, 380, 70);
			settextstyle(15, 0, "����");
			outtextxy(305, 53, "���/�޸�");

			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[8];
				InputBox(buf, 8, "������7λ�Һź���");
				if (IsRegisterId(buf)) {
					res = findModifiedNode(DiagnosisRecordHead, atoi(buf));
					if (res) {
						res->diagnosisSituation.setFlag = 1;
						clearrectangle(150, 50, 290, 280);				//ˢ����ʾ����
						outtextxy(150, 50, buf);
						outtextxy(150, 80, res->patientInfo.name);	//��������
						char buf_age[4];
						itoa(res->patientInfo.age, buf_age, 10);
						outtextxy(150, 110, buf_age);					//��������
						outtextxy(150, 140, res->doctorInfo.name);	//ҽ������
						char buf_leval[2];
						itoa(res->doctorInfo.level, buf_leval, 10);
						outtextxy(150, 170, doctorType[res->doctorInfo.level]);	//ҽ������
						char buf_section[3];
						itoa(res->doctorInfo.sectionId, buf_section, 10);
						outtextxy(150, 200, buf_section);				//ҽ������
						char buf_Doctorid[6];
						itoa(res->doctorInfo.id, buf_Doctorid, 10);
						outtextxy(150, 230, buf_Doctorid);			//ҽ������
						res->diagnosisSituation.setFlag = 0;
						char buf_date[30];
						sprintf(buf_date, "%d��%d�� %02d ��%02d", 
							currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
						outtextxy(150, 260, buf_date);
						res->recordTime = currentTime;
						char buf_num[3];
						InputBox(buf_num, 3, "��������������");
						if (LEGAL_DATA == IsDrugKindNum(buf_num)) {

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
							for (int i = 0; i < num; i++) {
								char buf_CheckId[3];
								InputBox(buf_CheckId, 3, "����������");
								if (LEGAL_DATA == IsDrugId(buf_CheckId)) {
									outtextxy(x, y, buf_CheckId);
									
									char temp_t[10];
									itoa(checkPriceList[atoi(buf_CheckId)], temp_t, 10);
									temp.yuan += checkPriceList[atoi(buf_CheckId)];
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
			}
		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //ȷ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "ȷ��");
			if (m.uMsg == WM_LBUTTONDOWN) {
				hospitalFund.checkCost.yuan += temp.yuan;
				hospitalFund.allCost.yuan += temp.yuan;
				res->diagnosisSituation.diagnosisSituationInfo.checkRecord.totalCost = temp;
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

			fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
			fillrectangle(300, 640, 375, 660);

			outtextxy(305, 53, "���/�޸�");

			outtextxy(147, 642, "ȷ��");
			outtextxy(322, 642, "����");

		}
		
	}

}
//���߾���-->��Ҫ��ҩ
void drawToPrescribe() {
	//DiagnosisRecord* queryDiagnosisByRegisterId(DiagnosisRecord* head,*int* registerId)
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	//
	char buf[8];
	DiagnosisRecord* res = NULL;
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
	setfillcolor(RGB(210, 210, 210));  //��ť��ɫ��ɫ

	fillrectangle(300, 50, 380, 70);
	fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(305, 53, "���/�޸�");
	outtextxy(147, 642, "ȷ��");
	outtextxy(322, 642, "����");
	SingleCost temp;
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 50 && m.y <= 70) {  //�Һź���
			clearrectangle(300, 50, 380, 70);
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 50, 380, 70);
			settextstyle(15, 0, "����");
			outtextxy(305, 53, "���/�޸�");

			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[8];
				InputBox(buf, 8, "������7λ�Һź���");
				

				if (IsRegisterId(buf)) { //����
					res = findModifiedNode(DiagnosisRecordHead, atoi(buf));
					if (res == NULL)continue;
					res->diagnosisSituation.setFlag = 1;
					clearrectangle(150, 50, 290, 280);				//ˢ����ʾ����
					outtextxy(150, 50, buf);
					outtextxy(150, 80, res->patientInfo.name);	//��������
					char buf_age[4];
					itoa(res->patientInfo.age, buf_age, 10);
					outtextxy(150, 110, buf_age);					//��������
					outtextxy(150, 140, res->doctorInfo.name);	//ҽ������
					char buf_leval[2];
					itoa(res->doctorInfo.level, buf_leval, 10);
					outtextxy(150, 170, doctorType[res->doctorInfo.level]);	//ҽ������
					char buf_section[3];
					itoa(res->doctorInfo.sectionId, buf_section, 10);
					outtextxy(150, 200, buf_section);				//ҽ������
					char buf_Doctorid[6];
					itoa(res->doctorInfo.id, buf_Doctorid, 10);
					outtextxy(150, 230, buf_Doctorid);			//ҽ������
					//��������
					char buf_date[30];
					sprintf(buf_date, "%d��%d�� %02d ��%02d",
						currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
					res->recordTime = currentTime;
					outtextxy(150, 260, buf_date);
					char buf_num[3];
					InputBox(buf_num, 2, "������ҩƷ������");
					if (LEGAL_DATA == IsDrugKindNum(buf_num)) {

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
						
						temp.yuan = 0;
						temp.jiao = 0;
						temp.fen = 0;
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
								temp.yuan += drugPriceList[atoi(buf_DrugId)] * atoi(buf_DrugNum);
								y += 30;
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

						//free(rear);
						res->diagnosisSituation.diagnosisSituationInfo
							.prescribeRecord.typeNumber = atoi(buf_num);
						res->diagnosisSituation.diagnosisSituationInfo
							.prescribeRecord.prescribeInfoHead = head;

					}
					else {
						continue;
					}
				}
			}

		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //ȷ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "ȷ��");
			if (m.uMsg == WM_LBUTTONDOWN) {
				hospitalFund.drugCost.yuan += temp.yuan;
				hospitalFund.allCost.yuan += temp.yuan;
				res->diagnosisSituation.diagnosisSituationInfo.prescribeRecord.totalCost = temp;
				break;  //����������free��res
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
			fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
			fillrectangle(300, 640, 375, 660);

			outtextxy(305, 53, "���/�޸�");
			outtextxy(147, 642, "ȷ��");
			outtextxy(322, 642, "����");
		}
	}
	//free(res);
}
//���߾���-->��Ҫ�Һ�--���뵽DiagnogsisRecordHead����
void drawToRegister() {
	DiagnosisRecord* res = initDiagnosisRecord();
	//��ʼ���ڵ�������Ϣ
	int flag = 0;
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "����");//�������ִ�С ��ʽ 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextcolor(BLACK);
	
	outtextxy(30, 80, "����������");
	outtextxy(30, 110, "�������䣺");
	outtextxy(30, 140, "ѡ����ң�");
	//settextstyle(15, 0, "����");//�������ִ�С ��ʽ 
	outtextxy(50, 200, "���� 01 -- �ڿ� 02 --Ƥ���� 03");
	outtextxy(50, 230, "�ۿ� 04 -- �ǿ� 05 --��ͯ�� 06");
	setfillcolor(RGB(210, 210, 210));  //��ť��ɫ��ɫ
	//settextstyle(20, 0, "����");//�������ִ�С ��ʽ 
	fillrectangle(300, 80, 380, 100);
	fillrectangle(300, 110, 380, 130);
	fillrectangle(300, 140, 380, 160);

	fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
	fillrectangle(300, 640, 375, 660);

	settextstyle(15, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(305, 83, "���/�޸�");
	outtextxy(305, 113, "���/�޸�");
	outtextxy(305, 143, "���/�޸�");
	outtextxy(147, 642, "ȷ��");
	outtextxy(322, 642, "����");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 80 && m.y <= 100) {  //��������
		setfillcolor(RGB(220, 140, 140));
		fillrectangle(300, 80, 380, 100);
		outtextxy(305, 83, "���/�޸�");
		if (m.uMsg == WM_LBUTTONDOWN) {
			char buf[50];
			InputBox(buf, 41, "�����뻼������(20������)");
			if (LEGAL_DATA == IsName(buf)) {
				strcpy(res->patientInfo.name, buf);		// �洢���ڴ�
				clearrectangle(150, 80, 290, 100);		// ˢ����ʾ����
				outtextxy(150, 80, buf);				//��ʾ

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
				char buf[4];
				InputBox(buf, 3, "���������");
				if (LEGAL_DATA == IsSection(buf)) {
					res->doctorInfo.sectionId = atoi(buf);
					clearrectangle(150, 140, 290, 160);
					outtextxy(150, 140, buf);

				}
				else {
					continue;
				}

			}


		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //ȷ��
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "ȷ��");
			if (m.uMsg == WM_LBUTTONDOWN) {
				settextstyle(20, 0, "����");
				clearrectangle(50, 390, 500, 430);
				//���ɹҺ�ID����
				generateRegisterID(res);
				//�Ƽ�ҽ������
				DoctorNode * List = getRecommendedDoctors(DoctorHead, res->doctorInfo.sectionId);
				char buf_doc[70];
				char buf_id[30];
				sprintf(buf_id,"���ĹҺ�IDΪ : %d",res->patientInfo.registerId);
				outtextxy(50, 400, buf_id);
				DoctorNode * temp = List->next;
				int cnt = 1;
				int y = 440;
				while(temp)
				{
					sprintf(buf_doc, "Ϊ���Ƽ��ĵ�%dλҽ��: %d ���� %s ҽʦ",cnt, temp->doctorInfo.id, temp->doctorInfo.name);
					outtextxy(50, y,buf_doc);
					y += 30;
					flag = 1;
					cnt++;
					temp = temp->next;
				}
				//ѡ����ҽ�����node��ҽ����Ϣ����
				InputBox(buf_doc, 2, "��Ҫѡ��ڼ�λҽ����");
				if (IsOneDigitNumber(buf_doc)) {
					temp = List;
					int cct = atoi(buf_doc);
					while (cct--){
						temp = temp->next;
					}
					combineDoctorIntoDiagnosisRecord(DiagnosisRecordHead, res, temp);
					sprintf(buf_doc,"��Ǻ����ĹҺţ�%s���Լ�ҽʦ��%s",
						buf_id, res->doctorInfo.name);
					InputBox(buf_doc, 2, buf_doc);
					//����res���ڿ���Ҫfree ����Ҫ��pushBack��ǳ����
					break;
				}
				else {
					InputBox(buf_doc, 2, "������������");
					break;
				}
				//�ύ��㺯��
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {  //����
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "����");
			if (m.uMsg == WM_LBUTTONDOWN) {
				if(!flag)
					free(res);
				break;
			}
		}
		else {
			setfillcolor(RGB(210, 210, 210));  //��ɫ
			settextstyle(15, 0, "����");
			fillrectangle(300, 80, 380, 100);
			fillrectangle(300, 110, 380, 130);
			fillrectangle(300, 140, 380, 160);
			fillrectangle(125, 640, 200, 660);  //���غ�ȷ��
			fillrectangle(300, 640, 375, 660);
			outtextxy(305, 83, "���/�޸�");
			outtextxy(305, 113, "���/�޸�");
			outtextxy(305, 143, "���/�޸�");
			outtextxy(147, 642, "ȷ��");
			outtextxy(322, 642, "����");
		}
	}

}
//���˵�-- ҽ����� -- �ӽ���
void drawDocSituation()
{
refresh:;
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "����");//�������ִ�С ��ʽ 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextcolor(BLACK);

	outtextxy(80, 50, "��ǰʱ��");
	outtextxy(35, 90, "ҽ������");
	outtextxy(155, 90, "ҽ������");
	outtextxy(275, 90, "��æ�̶�");
	outtextxy(395, 90, "״̬");

	//��ӡҽ����Ϣ��� ���� ���� ��æ�̶�����
	settextstyle(17, 0, "����");//�������ִ�С ��ʽ 
	DoctorNode* nowNode = DoctorHead->next;
	int y = 113;
	char _buf[200];
	while (nowNode != NULL) {
		outtextxy(45, y, nowNode->doctorInfo.name);
		sprintf(_buf, "%04d          %d",
			nowNode->doctorInfo.id,
			nowNode->doctorInfo.busyDegree);
		outtextxy(175, y, _buf);
		if (nowNode->doctorInfo.doctorStatus == 0)
			outtextxy(397, y, "��ְ");
		else if (nowNode->doctorInfo.doctorStatus == 1)
			outtextxy(397, y, "���");
		else if (nowNode->doctorInfo.doctorStatus == 2)
			outtextxy(397, y, "��ְ");
		nowNode = nowNode->next;
		y += 23;
	}

	setfillcolor(RGB(210, 210, 210));
	fillrectangle(125, 600, 200, 620);
	fillrectangle(300, 600, 375, 620);
	fillrectangle(125, 640, 200, 660);
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "����");
	outtextxy(147, 602, "���");
	outtextxy(322, 602, "��ְ");
	outtextxy(147, 642, "��Ƹ");
	outtextxy(322, 642, "����");

	
	char buf_cur[30];
	sprintf_s(buf_cur, "%d��%d�� %02d:%02d", currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
	outtextxy(200, 50, buf_cur);
	while (1)
	{
		//��ȡ��ǰʱ��(����)
		setfillcolor(RGB(255, 255, 255));
		fillrectangle(200, 50, 390, 70);
		outtextxy(200, 50, buf_cur);
		m = GetMouseMsg();
		if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "��Ƹ");
			//�������Ƹ
			if (m.uMsg == WM_LBUTTONDOWN) {
				//������Ƹ����	
				char buf_name[50], buf_sectionId[10];
				char buf_level[5], buf_workTime[8];
				InputBox(buf_name, 41, "����������");
				InputBox(buf_sectionId, 3, "���������");
				InputBox(buf_level, 2, "������ҽ������");
				InputBox(buf_workTime, 8, "���������ʱ��");
				if (!IsName(buf_name))continue;
				if (!IsSection(buf_sectionId))continue;
				if (!IsDoctorLevel(buf_level))continue;
				if (strlen(buf_workTime) != 7)continue;
				int flag = 0;
				for (int i = 0; i < 7; i++)
					if (buf_workTime[i] < '0' || buf_workTime[i]>'1') {
						flag = 1; break;
					}
				if (flag)continue;
				int secId = atoi(buf_sectionId);
				DoctorNode* newNode = (DoctorNode*)malloc(sizeof(DoctorNode));
				strcpy(newNode->doctorInfo.name, buf_name);
				newNode->doctorInfo.busyDegree = 0;
				newNode->doctorInfo.doctorStatus = 0;
				newNode->doctorInfo.sectionId = secId;
				for (int i = 0; i < 7; i++)
					newNode->doctorInfo.consultTime[i] =
					buf_workTime[i] == '1' ? true : false;
				newNode->doctorInfo.level = buf_level[0] - '0';
				newNode->doctorInfo.vacationLeft = 0;
				newNode->next = NULL;
				// �ڱ����
				DoctorNode* tempHead = queryDoctorBySectionId(DoctorHead, secId);
				int doctorIdOfLastTwo = 0;
				while (1) {
					doctorIdOfLastTwo++;
					if (tempHead == NULL)break;
					DoctorNode* t_Node = tempHead->next;
					int flag = 0;
					while (t_Node != NULL) {
						if (t_Node->doctorInfo.id % 100 == doctorIdOfLastTwo) {
							flag = 1; break;
						}
						t_Node = t_Node->next;
					}
					if (!flag)break;
				}
				newNode->doctorInfo.id = secId * 100 + doctorIdOfLastTwo;
				pushBackDoctorList(DoctorHead, newNode);
				goto refresh;
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "����");
			//����˷���
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}
		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 600 && m.y <= 620) {
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 600, 200, 620);
			outtextxy(147, 602, "���");
			//��������
			if (m.uMsg == WM_LBUTTONDOWN) {
				//�������
				char buf_id[10], buf_day[10];
				InputBox(buf_id, 5, "������ҽ������");
				InputBox(buf_day, 3, "�������������");
				if (!IsDoctorId(buf_id))continue;
				if (!IsNumber(buf_day))continue;
				DoctorNode* nowNode = queryDoctorByDoctorId(DoctorHead, atoi(buf_id));
				nowNode->doctorInfo.doctorStatus = 1;
				nowNode->doctorInfo.vacationLeft = atoi(buf_day);
				goto refresh;
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 600 && m.y <= 620) {
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 600, 375, 620);
			outtextxy(322, 602, "��ְ");
			//�������ְ
			if (m.uMsg == WM_LBUTTONDOWN) {
				//�������
				char buf_id[10];
				InputBox(buf_id, 5, "������ҽ������");
				if (!IsDoctorId(buf_id))continue;
				int id = atoi(buf_id);
				DoctorNode* nowNode = DoctorHead->next;
				while (nowNode != NULL) {
					if (nowNode->doctorInfo.id == id) {
						nowNode->doctorInfo.doctorStatus = 2;
						break;
					}
					nowNode = nowNode->next;
				}
				goto refresh;
			}
		}
		else {
			setfillcolor(RGB(210, 210, 210));  //��ɫ
			settextstyle(15, 0, "����");

			fillrectangle(125, 600, 200, 620);
			fillrectangle(300, 600, 375, 620);
			fillrectangle(125, 640, 200, 660);
			fillrectangle(300, 640, 375, 660);

			outtextxy(147, 602, "���");
			outtextxy(322, 602, "��ְ");
			outtextxy(147, 642, "��Ƹ");
			outtextxy(322, 642, "����");
		}

	}


}

