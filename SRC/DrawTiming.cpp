#include"DrawMunu.h"
#include"DiagnosisMessage.h"
#include"global.h"
#include"TimePassing.h"
#include"ListOperator.h"

//���˵�--ʱ������--�ӽ���
void drawTiming(){
	int thirty_days = 0, day = 0, hour = 0, minute = 0;
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "����");//�������ִ�С ��ʽ 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextcolor(BLACK);

	outtextxy(80, 50, "��ǰʱ�䣺");
	outtextxy(80, 90, "����ʱ�䣺");

	outtextxy(80, 230, "+ 30�� :");
	outtextxy(80, 270, "+ 1 �� :");
	outtextxy(80, 310, "+ 1Сʱ:");
	outtextxy(80, 350, "+ 1����:");
	TimeRecord temp = currentTime;
	char buf_cur[30];
	char buf_aft[30];
	sprintf_s(buf_cur,"%d��%d�� %02d:%02d",currentTime.month,currentTime.day,currentTime.hour,currentTime.minute);
	sprintf_s(buf_aft, "%d��%d�� %02d:%02d", temp.month, temp.day, temp.hour, temp.minute);
	outtextxy(200, 50, buf_cur);
	outtextxy(200, 90, buf_aft);

	setfillcolor(RGB(210, 210, 210));
	fillrectangle(125, 640, 200, 660);
	fillrectangle(300, 640, 375, 660);

	fillrectangle(280, 230, 330, 250);		//�ĸ�ѡ��
	fillrectangle(280, 270, 330, 290);
	fillrectangle(280, 310, 330, 330);
	fillrectangle(280, 350, 330, 370);

	settextstyle(15, 0, "����");
	outtextxy(285, 232, "ѡ��");
	outtextxy(285, 272, "ѡ��");
	outtextxy(285, 312, "ѡ��");
	outtextxy(285, 352, "ѡ��");

	outtextxy(147, 642, "ȷ��");
	outtextxy(322, 642, "����");

	settextstyle(20, 0, "����");
	while (1)
	{
		
		clearrectangle(200, 30, 500, 120);
		outtextxy(200, 50, buf_cur);
		outtextxy(200, 90, buf_aft);
		m = GetMouseMsg();
		if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660)
		{
			//�����ȷ��
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (temp.month > currentTime.month){
					ClearBusyDegree();
				}
				timePass(InHospitalHead, thirty_days, day, hour, minute);	//����
				int cnt = sortInHospitalList(InHospitalHead);				//��Ҫ��Ѻ������
				drawPatientToDeposit(cnt);									//��ӡ�ý�Ѻ���סԺ����			
				break;
			}
			else {
				continue;
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660)
		{
			//����˷���
			if (m.uMsg == WM_LBUTTONDOWN) {

				break;
			}
			else {
				continue;
			}
		}
		else if (m.x >= 280 && m.x <= 330 && m.y >= 230 && m.y <= 250)
		{
			//��� +30��
			if (m.uMsg == WM_LBUTTONDOWN) {
				thirty_days++;
				clearrectangle(200, 230, 270, 250);
				char buf[10];
				itoa(thirty_days, buf, 10);
				outtextxy(200, 230, buf);
				continue;
			}
			else {
				continue;
			}

		}
		else if (m.x >= 280 && m.x <= 330 && m.y >= 270 && m.y <= 290)
		{
			//��� +1 ��
			if (m.uMsg == WM_LBUTTONDOWN) {
				day++;
				clearrectangle(200, 270, 270, 290);
				char buf[10];
				itoa(day, buf, 10);
				outtextxy(200, 270, buf);
				continue;
			}
		}
		else if (m.x >= 280 && m.x <= 330 && m.y >= 310 && m.y <= 330)
		{
			//��� + 1 Сʱ
			if (m.uMsg == WM_LBUTTONDOWN) {
				hour++;
				clearrectangle(200, 310, 270, 330);
				char buf[10];
				itoa(hour, buf, 10);
				outtextxy(200, 310, buf);
				continue;
			}
		}
		else if (m.x >= 280 && m.x <= 330 && m.y >= 350 && m.y <= 370)
		{
			//��� + 1����
			if (m.uMsg == WM_LBUTTONDOWN) {
				minute++;
				clearrectangle(200, 350, 270, 370);
				char buf[10];
				itoa(minute, buf, 10);
				outtextxy(200, 350, buf);
				continue;
			}
		}

	}

}
//���˵�-->ʱ������-->�޸�ʱ��-->�Զ�����������Ҫ�ɷѵ�סԺ��������
void drawPatientToDeposit(int cnt)
{
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "����");//�������ִ�С ��ʽ 
	setbkmode(TRANSPARENT);// ȥ�����ֱ���
	settextcolor(BLACK);
	outtextxy(30, 30, "����");
	outtextxy(200, 30, "�Һź���");
	outtextxy(400, 30, "��ǰѺ��");

	setfillcolor(RGB(210, 210, 210));
	fillrectangle(125, 640, 200, 660);
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "����");
	outtextxy(147, 642, "ȷ��");
	outtextxy(322, 642, "����");
	char buf_name[30];
	char buf_id[30];
	char buf_deposit[30];
	int y = 60;
	DiagnosisRecord * res = InHospitalHead->next;
	while (cnt--)
	{
		strcpy_s(buf_name, res->patientInfo.name);
		itoa(res->patientInfo.registerId, buf_id, 10);
		SingleCost * temp = &res->diagnosisSituation.diagnosisSituationInfo.inHospitalRecord.deposit;
		sprintf(buf_deposit, "%dԪ%d��%d��", temp->yuan, temp->jiao, temp->fen);
		outtextxy(30, y, buf_name);
		outtextxy(200, y, buf_id);
		outtextxy(380, y, buf_deposit);
		y += 30;
		res = res->next;
	}
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660)
		{
			//�����ȷ��
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}
			else {
				continue;
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660)
		{
			//����˷���
			if (m.uMsg == WM_LBUTTONDOWN) {

				break;
			}
			else {
				continue;
			}
		}
	}

}